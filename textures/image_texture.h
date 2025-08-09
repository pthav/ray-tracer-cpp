#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"
#include "../utility/rtw_stb_image.h"
#include "../utility/interval.h"

class ImageTexture : public Texture
{
public:
    explicit ImageTexture(const char* filename) : m_image{filename}
    {
        assert(m_image.height() > 0);
    }

    [[nodiscard]] color value(double u, double v, const point3 &p) const override
    {
        u = Interval(0,1).clamp(u);
        v = 1.0 - Interval(0,1).clamp(v);

        auto i = static_cast<int>(u * m_image.width());
        auto j = static_cast<int>(v * m_image.height());
        auto pixel = m_image.pixel_data(i,j);
        auto scale {1.0 / 255.0};
        return color{scale * pixel[0],scale * pixel[1],scale * pixel[2]};
    }

private:
    rtw_image m_image;
};

#endif //IMAGE_TEXTURE_H
