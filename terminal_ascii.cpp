#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <string>

// Extended ASCII characters used for different intensity levels
const unsigned char EXTENDED_ASCII_CHARS[] = {0x20, 0xFF, 0xB0, 0xB1, 0xB2, 0xDB, 0xFE};

// Ensure the number of ASCII characters matches the array size
const int NUM_ASCII_CHARS = sizeof(EXTENDED_ASCII_CHARS) / sizeof(EXTENDED_ASCII_CHARS[0]);

// Function to map brightness (grayscale) to an extended ASCII character
char getAsciiChar(int intensity) {
    int index = (intensity * (NUM_ASCII_CHARS - 1)) / 255;
    return EXTENDED_ASCII_CHARS[index];
}

// Function to convert grayscale value to an ANSI color code
std::string getAnsiColorCode(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

// Function to load an image and convert it to ASCII art stored in a matrix
std::vector<std::vector<std::pair<std::string, char>>> convertImageToAsciiMatrix(const std::string& imagePath, int width, int height) {
    // Load the image (returns pixel data, width, height, and number of channels)
    int imgWidth, imgHeight, channels;
    unsigned char* imgData = stbi_load(imagePath.c_str(), &imgWidth, &imgHeight, &channels, 0);
    if (!imgData) {
        std::cerr << "Error: Could not load image: " << imagePath << std::endl;
        exit(-1);
    }

    // Resize the image to fit within the terminal
    int newWidth = width;
    int newHeight = (height * imgHeight) / imgWidth;  // Preserve aspect ratio

    // Create a 2D matrix to store the ASCII characters and their color codes
    std::vector<std::vector<std::pair<std::string, char>>> asciiMatrix(newHeight, std::vector<std::pair<std::string, char>>(newWidth));

    // Iterate through the resized image and populate the matrix with ASCII characters and colors
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate the corresponding pixel in the original image
            int origX = (x * imgWidth) / newWidth;
            int origY = (y * imgHeight) / newHeight;
            int pixelIndex = (origY * imgWidth + origX) * channels;

            // Calculate the RGB values
            int r = imgData[pixelIndex];
            int g = imgData[pixelIndex + 1];
            int b = imgData[pixelIndex + 2];
            int grayscale = (r + g + b) / 3;

            // Map the grayscale value to an extended ASCII character
            char asciiChar = getAsciiChar(grayscale);

            // Generate the ANSI color code for the current pixel
            std::string colorCode = getAnsiColorCode(r, g, b);

            // Store the color code and ASCII character in the matrix
            asciiMatrix[y][x] = {colorCode, asciiChar};
        }
    }

    // Free the image data loaded by stb_image
    stbi_image_free(imgData);

    return asciiMatrix;
}

// Function to display the ASCII matrix in the terminal with colors
void displayAsciiMatrix(const std::vector<std::vector<std::pair<std::string, char>>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& pixel : row) {
            // Print the color code and ASCII character
            std::cout << pixel.first << pixel.second;
        }
        std::cout << "\033[0m" << std::endl; // Reset color at the end of the line
    }
}

int main() {
    // Path to the image file
    std::string imagePath = "./ascii.png";

    // Define the terminal width and height for ASCII art (adjust as needed)
    int terminalWidth = 50;
    int terminalHeight = 25;

    // Convert the image to an ASCII matrix
    std::vector<std::vector<std::pair<std::string, char>>> asciiMatrix = convertImageToAsciiMatrix(imagePath, terminalWidth, terminalHeight);

    // Display the ASCII art in the terminal with colors
    displayAsciiMatrix(asciiMatrix);

    return 0;
}
