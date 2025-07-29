#ifndef CAMERA_H
#define CAMERA_H

#include "../materials/material.h"
#include "../hittable/hittable_list.h"
#include "../vector/color.h"

class Camera
{
private:
    double m_imageHeight{};
    point3 m_cameraCenter{};
    Vec3 m_pixelU{};
    Vec3 m_pixelV{};
    point3 m_pixel00Loc{};
    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;

    void initialize();

    [[nodiscard]] ray generateRay(const point3 &pixel) const ;

    color rayColor(const ray &r, const HittableList &objects, int depth);

public:
    int m_imageWidth{400};
    int m_samples{100};
    double m_aspectRatio{16.0 / 9.0};
    double m_vfov{90};
    int m_maxDepth{1};
    Vec3 m_lookAt{0,0,-1};
    Vec3 m_lookFrom{0,0,0};
    Vec3 m_up{0,1,0};
    color m_background{0.5,0.7,1.0};

    Camera() = default;

    void render(const HittableList &objects);
};

#endif //CAMERA_H
