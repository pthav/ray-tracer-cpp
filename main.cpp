#include <fstream>
#include "vector.h"
#include "color.h"


int main()
{
    std::ofstream out{"image.ppm"};
    constexpr int imageWidth{256};
    constexpr int imageHeight{256};
    out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int row = 0; row < imageHeight; row++)
    {
        for (int col = 0; col < imageWidth; col++)
        {
            color pixel{
                static_cast<double>(row) / (imageWidth - 1),
                static_cast<double>(col) / (imageHeight - 1),
                0.0
            };

            write_color(out,pixel);
        }
    }
    return 0;
}
