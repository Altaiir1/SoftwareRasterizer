#include <iostream>

#include "Framebuffer.h"

int main()
{
    std::cout << "Creating framebuffer..." << '\n';

    // Create 800x600 framebuffer
    Framebuffer buffer(800, 600);

    // Clear to dark blue background
    buffer.Clear({20, 20, 40, 255});

    Color white = {255, 255, 255, 255};

    // Line testing
    buffer.DrawLine(400, 300, 600, 200, white); // Up-right
    buffer.DrawLine(400, 300, 600, 400, white); // Down-right
    buffer.DrawLine(400, 300, 200, 200, white); // Up-left
    buffer.DrawLine(400, 300, 200, 400, white); // Down-left
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
    if (buffer.SaveToPNG("output.png"))
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