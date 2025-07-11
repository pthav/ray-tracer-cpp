#include "render/camera.h"
#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "materials/dielectric.h"
#include "materials/diffuse.h"
#include "materials/metal.h"

int main()
{
    // Create Camera
    Camera camera{};

    // Create Materials
    auto material_ground = std::make_shared<DiffuseMaterial>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<DiffuseMaterial>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<DielectricMaterial>(1.50);
    auto material_bubble = std::make_shared<DielectricMaterial>(1.0 / 1.5);
    auto material_right = std::make_shared<MetalMaterial>(color(0.8, 0.6, 0.2), 1.0);

    // Create scene of objects
    HittableList objects{};
    objects.add(std::make_shared<Sphere>(0, -100.5, -1.0, 100, material_ground));
    objects.add(std::make_shared<Sphere>(0, 0, -1.2, 0.5, material_center));
    objects.add(std::make_shared<Sphere>(-1.0, 0.0, -1.0, 0.5, material_left));
    objects.add(std::make_shared<Sphere>(-1.0, 0.0, -1.0, 0.4, material_bubble));
    objects.add(std::make_shared<Sphere>(1.0, 0.0, -1.0, 0.5, material_right));
    // objects.add(std::make_shared<Sphere>(0, 0.0, -0.4, 0.2, material_left));

    camera.render(objects);
}
