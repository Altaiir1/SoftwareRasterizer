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