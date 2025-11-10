#include <iostream>

#include "Framebuffer.h"

int main()
{
    std::cout << "Creating framebuffer..." << '\n';

    // Create 800x600 framebuffer
    Framebuffer buffer(800, 600);

    // Clear to dark blue background
    buffer.Clear({30, 30, 80, 255});

    // Draw a white diagonal line
    for (int i = 0; i < 400; ++i)
        buffer.SetPixel(i, i, {255, 255, 255, 255});

    // Draw a red square
    for (int y = 200; y < 300; ++y)
    {
        for (int x = 400; x < 500; ++x)
        {
            // Set each x and y pixel with red color
            buffer.SetPixel(x, y, {255, 0, 0, 255});
        }
    }

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