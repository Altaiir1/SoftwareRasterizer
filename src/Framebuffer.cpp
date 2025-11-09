#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : m_width(width), m_height(height)
{
    // Allocate memory for width*height pixels
    // Without this, m_pixels would be empty (size=0) and accessing any index would crash
    m_pixels.resize(width * height, {0, 0, 0, 255});
}