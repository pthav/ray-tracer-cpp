#ifndef CAMERA_H
#define CAMERA_H

#include "../hittable/hittable_list.h"
#include "../ray/color.h"

class Camera
{
private:
    double m_imageHeight{};
    point3 m_cameraCenter{};
    Vec3 m_pixelU{};
    Vec3 m_pixelV{};
    point3 m_pixel00Loc{};

    void initialize();

    static color rayColor(const ray &r, const HittableList &objects);

public:
    int m_imageWidth{400};
    double m_aspectRatio{16.0 / 9.0};

    Camera() = default;

    void render(const HittableList &objects);
};

#endif //CAMERA_H
