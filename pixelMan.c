#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>

void encrypt_image(const char* input, const char* output) {
    FILE* fp = fopen(input, "rb");
    FILE* out_fp = fopen(output, "wb");

    if (!fp || !out_fp) {
        perror("File error");
        return;
    }

    // PNG variables
    png_byte bit_depth, color_type;
    png_bytep* row_pointers;
    int width, height;

    // Initialize PNG read structure
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png, fp);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);

    // Read image data into row_pointers
    png_read_update_info(png, info);
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png, info));
    }
    png_read_image(png, row_pointers);

    // Encryption parameters
    uint8_t key = 0xAA;  // Change key for more noticeable encryption
    int modulus = 256;   // Modulus for arithmetic

    // Pixel manipulation (XOR, color inversion, brightness change)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * 4; x++) { // *4 for RGBA
            // XOR with the key
            row_pointers[y][x] ^= key;

            // Invert color
            row_pointers[y][x] = modulus - row_pointers[y][x];

            // Increase brightness (with a limit to avoid overflow)
            row_pointers[y][x] = (row_pointers[y][x] + 50) % modulus; 
        }
    }

    // Write encrypted image
    png_structp png_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_write = png_create_info_struct(png_write);
    png_init_io(png_write, out_fp);
    png_set_IHDR(png_write, info_write, width, height, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_write, info_write);
    png_write_image(png_write, row_pointers);
    png_write_end(png_write, NULL);

    // Clean up memory
    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    // Close files
    fclose(fp);
    fclose(out_fp);
}

int main() {
    encrypt_image("superman.png", "encrypted.png");
    return 0;
}
