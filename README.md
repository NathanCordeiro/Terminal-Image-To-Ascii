---

# Terminal-Image-To-Ascii

---
This project converts an image into ASCII art, displayed in the terminal with color. The program maps grayscale intensity levels of the image to specific extended ASCII characters and uses ANSI color 
codes to represent the original RGB colors of the image.

## Features
- Convert an image to ASCII characters based on pixel intensity.
- Preserve the original image colors using ANSI color codes.
- Adjust the ASCII art size to fit within a terminal window.

## How It Works
1. **Image Loading**: The program uses `stb_image.h` to load an image in memory.
2. **Pixel Intensity to ASCII**: The grayscale intensity of each pixel is mapped to an extended ASCII character.
3. **Color Conversion**: The RGB color of each pixel is converted to an ANSI escape code.
4. **Display in Terminal**: The ASCII art is displayed in the terminal using the correct colors and characters.

