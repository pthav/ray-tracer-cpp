#include "camera.h"

#include <fstream>
#include <limits>

#include "../utility/random.h"

void Camera::initialize()
{
    // Image settings
    m_imageHeight = static_cast<int>(m_imageWidth / m_aspectRatio);
    m_imageHeight = (m_imageHeight < 1) ? 1 : m_imageHeight;

    // Camera settings
    auto focalLength{(m_lookFrom - m_lookAt).length()};
    auto theta {(M_PI / 180.0) * m_vfov};
    auto h {std::tan(theta/2)};
    auto viewportHeight{2.0 * h * focalLength};
    auto viewportWidth{viewportHeight * (static_cast<double>(m_imageWidth) / m_imageHeight)};
    auto cameraCenter {m_lookFrom};

    // Camera orthonormal basis
    m_w = normalize(m_lookFrom - m_lookAt);
    m_u = normalize(cross(m_up, m_w));
    m_v = cross(m_w, m_u);

    // Viewport vectors
    auto viewportU{viewportWidth * m_u};
    auto viewportV{viewportHeight * -m_v};

    // Pixel delta vectors
    m_pixelU = viewportU / m_imageWidth;
    m_pixelV = viewportV / m_imageHeight;

    // Upper left
    auto viewportUpperLeft{cameraCenter - focalLength * m_w - 0.5 * viewportU - 0.5 * viewportV};
    m_pixel00Loc = viewportUpperLeft + 0.5 * m_pixelU + 0.5 * m_pixelV;
}

// Randomly generate a random ray pointing within a given pixel
ray Camera::generateRay(const point3 &pixel) const
{
    double randomU{Random::randomDouble() - (1.0 / 2.0)};
    double randomV{Random::randomDouble() - (1.0 / 2.0)};
    Vec3 du{m_pixelU * randomU};
    Vec3 dv{m_pixelV * randomV};

    Vec3 origin{m_lookFrom};
    Vec3 direction{(pixel + du + dv) - origin};
    double time{Random::randomDouble()};
    ray randomRay{origin, normalize(direction), time};

    return randomRay;
}

color Camera::rayColor(const ray &r, const HittableList &objects, int depth)
{
    if (depth <= 0)
    {
        return color{0, 0, 0}; // No more light accumulation
    }

    hitRecord record{};
    if (objects.hit(r, Interval{0.001, std::numeric_limits<double>::infinity()}, record))
    {
        ray scattered {};
        color attenuation {};
        auto emissionColor {record.m_material->emit(record.m_u, record.m_v, record.m_intersection)};
        if (!record.m_material->scatter(r, record, attenuation, scattered))
        {
            return emissionColor;
        }
        auto scatterColor {attenuation * rayColor(scattered, objects, depth -1)};
        return emissionColor + scatterColor;
    }

    return m_background; // No hit so background
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
                accumulated += rayColor(pixelRay, objects, m_maxDepth);
            }
            writeColor(out, accumulated / m_samples);
        }
    }
}
