#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : m_width(width), m_height(height)
{
    // Allocate memory for width*height pixels
    // Without this, m_pixels would be empty (size=0) and accessing any index would crash
    m_pixels.resize(width * height, {0, 0, 0, 255});
}

void Framebuffer::SetPixel(int x, int y, const Color &color)
{
    // Check if x, y is within bounds
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;

    // Map 2D in 1D Vector
    int index = y * m_width + x;
    m_pixels[index] = color;
}

void Framebuffer::DrawLine(int x0, int y0, int x1, int y1, const Color &color)
{
    // Calculate deltas
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // Determine step direction for x and y
    int sx = (x0 < x1) ? 1 : -1; // 1 if going right, -1 if going left
    int sy = (y0 < y1) ? 1 : -1; // 1 if going down, -1 if going up

    // Initialize error term
    int error = dx - dy;

    // Current position
    int x = x0;
    int y = y0;

    // Draw line
    while (true)
    {
        SetPixel(x, y, color);

        // Check if we've reached the end
        if (x == x1 && y == y1)
            break;

        // Calculate error for next step
        int error2 = error * 2;

        // Step in x direction if needed
        if (error2 > -dy)
        {
            error -= dy;
            x += sx;
        }

        // Step in y direction if needed
        if (error2 < dx)
        {
            error += dx;
            y += sy;
        }
    }
}

void Framebuffer::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const Color &color)
{
    // Just draw the 3 edges for now
    DrawLine(x0, y0, x1, y1, color);
    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x0, y0, color);
}

void Framebuffer::Clear(const Color &color)
{
    // Loop through each pixel and clear it by setting it to a certain color
    for (auto &pixel : m_pixels)
    {
        pixel = color;
    }
}

int Framebuffer::GetHeight() const
{
    return m_height;
}

int Framebuffer::GetWidth() const
{
    return m_width;
}

bool Framebuffer::SaveToPNG(const char *filename)
{
    // Call library function with needed parameters
    // data() converts vector to C-Style pointer to the array, since it is a C Library
    int result = stbi_write_png(filename, m_width, m_height, 4, m_pixels.data(), m_width * 4);

    // Return true if successful, false otherwise
    return result != 0;
}