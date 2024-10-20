# SCT_CS_2

# Image Encryption Tool

## 🔒 Overview
This powerful C program encrypts PNG images through advanced pixel manipulation techniques, providing a unique way to safeguard your visual data. By employing methods such as XOR encryption, color inversion, and brightness adjustment, this tool transforms images into cryptic representations.

## ✨ Features
- **PNG Support:** Seamlessly works with PNG images.
- **Customizable Encryption Key:** Modify the XOR key for varied encryption.
- **Color Inversion:** Dramatically alters pixel colors for enhanced encryption.
- **Brightness Adjustment:** Ensures images remain visually interesting while avoiding overflow.

## 📦 Requirements
- C Compiler (GCC recommended)
- `libpng` library

## ⚙️ Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/image-encryption.git
   cd image-encryption

2.	Install libpng:

        brew install libpng


3.	Compile the program:

        gcc pixelman.c -I/opt/homebrew/include -L/opt/homebrew/lib -lpng -o pixelman



🚀 Usage

1.	Place your input image (input.png) in the same directory as the executable.
2.	Run the program:

		./pixelman


3.	Check the output file (encrypted.png) for your encrypted image.

