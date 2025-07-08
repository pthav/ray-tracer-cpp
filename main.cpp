#include "render/camera.h"
#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "materials/diffuse.h"
#include "materials/metal.h"

int main()
{
    // Create Camera
    Camera camera{};

    // Create Materials
    auto material_ground = std::make_shared<DiffuseMaterial>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<DiffuseMaterial>(color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<MetalMaterial>(color(0.8, 0.8, 0.8),0.5);
    auto material_right  = std::make_shared<MetalMaterial>(color(0.8, 0.6, 0.2),1.0);

    // Create scene of objects
    HittableList objects{};
    objects.add(std::make_shared<Sphere>(Sphere{0, 0, -1, 0.5,material_center}));
    objects.add(std::make_shared<Sphere>(Sphere{0, -100.5, -1, 100, material_ground}));
    objects.add(make_shared<Sphere>(-1.0,    0.0, -1.0,   0.5, material_left));
    objects.add(make_shared<Sphere>(1.0,    0.0, -1.0,   0.5, material_right));

    camera.render(objects);
}
