#include <iostream>

#include "Framebuffer.h"

int main()
{
    std::cout << "Creating framebuffer..." << '\n';

    // Create 800x600 framebuffer
    Framebuffer buffer(800, 600);
    buffer.Clear({20, 20, 40, 255});

    Color white = {255, 255, 255, 255};
    Color red = {255, 0, 0, 255};
    Color green = {0, 255, 0, 255};
    Color blue = {0, 100, 255, 255};

    int centerX = 400;
    int centerY = 300;

    // Draw a start pattern - lines in all 8 directions
    buffer.DrawLine(centerX, centerY, centerX + 200, centerY, white);       // Right
    buffer.DrawLine(centerX, centerY, centerX - 200, centerY, white);       // Left
    buffer.DrawLine(centerX, centerY, centerX, centerY + 200, white);       // Down
    buffer.DrawLine(centerX, centerY, centerX, centerY - 200, white);       // Up
    buffer.DrawLine(centerX, centerY, centerX + 150, centerY + 150, red);   // Down-right diagonal
    buffer.DrawLine(centerX, centerY, centerX - 150, centerY - 150, red);   // Up-left diagonal
    buffer.DrawLine(centerX, centerY, centerX + 150, centerY - 150, green); // Up-right diagonal
    buffer.DrawLine(centerX, centerY, centerX - 150, centerY + 150, green); // Down-left diagonal

    // Draw a box
    buffer.DrawLine(100, 100, 300, 100, blue); // Top
    buffer.DrawLine(300, 100, 300, 250, blue); // Right
    buffer.DrawLine(300, 250, 100, 250, blue); // Bottom
    buffer.DrawLine(100, 250, 100, 100, blue); // Left

    // Draw some gentle slopes
    buffer.DrawLine(500, 400, 700, 450, {255, 255, 0, 255}); // Yellow gentle
    buffer.DrawLine(500, 200, 550, 400, {255, 0, 255, 255}); // Magenta steep

    // Draw a red square
    /*
    for (int y = 200; y < 300; ++y)
    {
        for (int x = 400; x < 500; ++x)
        {
            // Set each x and y pixel with red color
            buffer.SetPixel(x, y, {255, 0, 0, 255});
        }
    }
    */

    // Save to file
    if (buffer.SaveToPNG("output/output.png"))
    {
        std::cout << "Image saved to output.png..." << '\n';
    }
    else
    {
        std::cerr << "Failed to save image!" << '\n';
        return 1;
    }

    return 0;
}