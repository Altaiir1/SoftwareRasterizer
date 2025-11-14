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

    buffer.DrawTriangle(400, 100, 300, 300, 500, 300, white);
    buffer.DrawTriangle(200, 400, 250, 500, 150, 500, red);
    buffer.DrawTriangle(600, 200, 700, 400, 550, 350, green);

    // Save to file
    if (buffer.SaveToPNG("../output/output.png"))
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