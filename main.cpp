#include <chrono>

#include "hittable/bvh.h"
#include "render/camera.h"
#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "materials/dielectric.h"
#include "materials/diffuse.h"
#include "materials/metal.h"
#include "utility/random.h"

int main()
{
    // Create Materials
    auto material_ground = std::make_shared<DiffuseMaterial>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<DiffuseMaterial>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<DielectricMaterial>(1.50);
    auto material_bubble = std::make_shared<DielectricMaterial>(1.0 / 1.5);
    auto material_right = std::make_shared<MetalMaterial>(color(0.8, 0.6, 0.2), 1.0);

    // Create scene of objects
    HittableList objects{};
    objects.add(std::make_shared<Sphere>(point3{0, -100.5, -1.0},point3{0, -100.5, -1.0}, 100, material_ground));
    objects.add(std::make_shared<Sphere>(point3{0, 0, -1.2},point3{0,0,-1.7},0.5, material_center));
    objects.add(std::make_shared<Sphere>(point3{-1.0, 0.0, -1.0}, point3{-1.0,0.2,-1.2}, 0.5, material_left));
    objects.add(std::make_shared<Sphere>(point3{-1.0, 0.0, -1.0}, point3{-1.0,0.2,-1.2}, 0.4, material_bubble));
    objects.add(std::make_shared<Sphere>(point3{1.0, 0.0, -1.0}, point3{1.3,0.0,-1.1}, 0.5, material_right));

    for (int i {0}; i < 50; i++)
    {
        point3 center {Random::randomDouble() * 6 - 3,Random::randomDouble() * 5,Random::randomDouble() * 6 - 3};
        objects.add(std::make_shared<Sphere>(center, Random::randomDouble() * 0.3 + 0.1, material_center));
    }

    auto before {std::chrono::high_resolution_clock::now()};
    HittableList bvhList{};
    bvhList.add(std::make_shared<BVH>(objects));
    auto after {std::chrono::high_resolution_clock::now()};
    auto duration {std::chrono::duration_cast<std::chrono::milliseconds>(after - before)};
    std::cerr << "BVH construction took " << duration.count() << " ms\n";

    // Create Camera
    Camera camera{};
    camera.m_aspectRatio = 16.0 / 9.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 10;
    camera.m_maxDepth = 10;
    camera.m_vfov = 90;
    camera.m_lookFrom = point3(-2, 2, 1);
    camera.m_lookAt = point3(0, 0, -1);
    camera.m_up = Vec3(0, 1, 0);

    std::cerr << "Program started\n";
    before = std::chrono::high_resolution_clock::now();
    camera.render(bvhList);
    after = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
    std::cerr << "Render took " << duration.count() << " ms";
}
