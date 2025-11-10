#pragma once

#include <vector>
#include <cstdint>

struct Color
{
    uint8_t r, g, b, a; // 0-255 per channel, alpha for transparency
};

class Framebuffer
{
public:
    Framebuffer(int width, int height);

    void SetPixel(int x, int y, const Color &color);

    void Clear(const Color &color);

    bool SaveToPNG(const char *filename);

    int GetWidth() const;
    int GetHeight() const;

private:
    int m_width;
    int m_height;
    std::vector<Color> m_pixels;
};