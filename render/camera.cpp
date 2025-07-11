#include "camera.h"

#include <fstream>
#include <limits>

void Camera::initialize()
{
    // Image settings
    m_imageHeight = static_cast<int>(m_imageWidth / m_aspectRatio);
    m_imageHeight = (m_imageHeight < 1) ? 1 : m_imageHeight;

    // Camera settings
    auto focalLength{1.0};
    auto viewportHeight{2.0};
    auto viewportWidth{viewportHeight * (static_cast<double>(m_imageWidth) / m_imageHeight)};
    m_cameraCenter = point3{0, 0, 0};

    // Viewport vectors
    Vec3 viewportU{viewportWidth, 0, 0};
    Vec3 viewportV{0, -viewportHeight, 0};

    // Pixel delta vectors
    m_pixelU = viewportU / m_imageWidth;
    m_pixelV = viewportV / m_imageHeight;

    // Upper left
    auto viewportUpperLeft{m_cameraCenter - Vec3{0, 0, focalLength} - 0.5 * viewportU - 0.5 * viewportV};
    m_pixel00Loc = viewportUpperLeft + 0.5 * m_pixelU + 0.5 * m_pixelV;

    // Random
    std::random_device rd{};
    m_gen.seed(rd());
    m_distribution = std::uniform_real_distribution<>(-1.0 / 2.0, 1.0 / 2.0);
}

// Randomly generate a random ray pointing within a given pixel
ray Camera::generateRay(const point3 &pixel)
{
    double randomU{m_distribution(m_gen)};
    double randomV{m_distribution(m_gen)};
    Vec3 du{m_pixelU * randomU};
    Vec3 dv{m_pixelV * randomV};

    Vec3 origin{m_cameraCenter};
    Vec3 direction{(pixel + du + dv) - origin};
    ray randomRay{origin, normalize(direction)};

    return randomRay;
}

color Camera::rayColor(const ray &r, const HittableList &objects, int depth)
{
    if (depth <= 0)
    {
        return color{0, 0, 0};
    }

    hitRecord record{};
    if (objects.hit(r, 0.001, std::numeric_limits<double>::infinity(), record))
    {
        ray scattered {};
        color attenuation {};
        if (record.m_material->scatter(r, record, attenuation, scattered))
        {
            return attenuation * rayColor(scattered, objects, depth - 1);
        }
        return color{0,0,0};
    }

    Vec3 unit_direction = normalize(r.getDirection());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
}


void Camera::render(const HittableList &objects)
{
    initialize();

    std::ofstream out{"image.ppm"};
    out << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";
    for (int row = 0; row < m_imageHeight; row++)
    {
        for (int col = 0; col < m_imageWidth; col++)
        {
            auto pixelCenter{m_pixel00Loc + (col * m_pixelU) + (row * m_pixelV)};
            color accumulated{0, 0, 0};
            for (int s = 0; s < m_samples; s++)
            {
                ray pixelRay{generateRay(pixelCenter)};
                accumulated += rayColor(pixelRay, objects, 10);
            }
            write_color(out, accumulated / m_samples);
        }
    }
}
