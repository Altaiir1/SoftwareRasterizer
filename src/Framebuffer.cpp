#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : m_width(width), m_height(height)
{
    // Allocate memory for width*height pixels
    // Without this, m_pixels would be empty (size=0) and accessing any index would crash
    m_pixels.resize(width * height, {0, 0, 0, 255});
}

Framebuffer::SetPixel(int x, int y, const Color &color)
{
    // Check if x, y is within bounds
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;

    int index = y * m_width + x;
    m_pixels[index] = color;
}