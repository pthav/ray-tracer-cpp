#ifndef SCENE_H
#define SCENE_H

#include "../Hittable/Hittable_list.h"
#include "../Hittable/quadrilateral.h"
#include "camera.h"
#include "../hittable/constant_medium.h"
#include "../Hittable/instance.h"
#include "../materials/dielectric.h"
#include "../materials/diffuse.h"
#include "../materials/metal.h"
#include "../utility/random.h"
#include "../Hittable/sphere.h"
#include "../materials/diffuse_light.h"
#include "../textures/image_texture.h"
#include "../textures/noise_texture.h"

inline void earth(HittableList &objects, Camera &camera)
{
    auto earthTexture{std::make_shared<ImageTexture>("earthmap.jpg")};
    auto earthSurface{std::make_shared<DiffuseMaterial>(earthTexture)};
    auto earthSphere{std::make_shared<Sphere>(point3{0, 0, -1}, 2, earthSurface)};
    objects.add(earthSphere);

    camera.m_aspectRatio = 16.0 / 9.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 10;
    camera.m_maxDepth = 10;
    camera.m_vfov = 20;
    camera.m_lookFrom = point3(0, 0, 12);
    camera.m_lookAt = point3(0, 0, 0);
    camera.m_up = Vec3(0, 1, 0);
}

inline void perlin(HittableList &objects, Camera &camera)
{
    auto perlinTexture = std::make_shared<NoiseTexture>(8);
    objects.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, std::make_shared<DiffuseMaterial>(perlinTexture)));
    objects.add(std::make_shared<Sphere>(point3(0, 2, 0), 2, std::make_shared<DiffuseMaterial>(perlinTexture)));

    camera.m_aspectRatio = 16.0 / 9.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 10;
    camera.m_maxDepth = 10;
    camera.m_vfov = 20;
    camera.m_lookFrom = point3(13, 2, 3);
    camera.m_lookAt = point3(0, 0, 0);
    camera.m_up = Vec3(0, 1, 0);
}

inline void randomScene(HittableList &objects, Camera &camera)
{
    // Create Materials
    auto material_ground = std::make_shared<DiffuseMaterial>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<DiffuseMaterial>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<DielectricMaterial>(1.50);
    auto material_bubble = std::make_shared<DielectricMaterial>(1.0 / 1.5);
    auto material_right = std::make_shared<MetalMaterial>(color(0.8, 0.6, 0.2), 1.0);

    // Create scene of objects
    objects.add(std::make_shared<Sphere>(point3{0, -100.5, -1.0}, 100, material_ground));
    objects.add(std::make_shared<Sphere>(point3{0, 0, -1.2}, 0.5, material_center));
    objects.add(std::make_shared<Sphere>(point3{-1.0, 0.0, -1.0}, 0.5, material_left));
    objects.add(std::make_shared<Sphere>(point3{-1.0, 0.0, -1.0}, 0.4, material_bubble));
    objects.add(std::make_shared<Sphere>(point3{1.0, 0.0, -1.0}, 0.5, material_right));

    for (int i{0}; i < 500; i++)
    {
        std::shared_ptr<Material> randomMaterial{};
        auto randomMaterialR{Random::randomDouble()};
        if (randomMaterialR < 0.2)
        {
            randomMaterial = std::make_shared<DielectricMaterial>(Random::randomDouble() / Random::randomDouble());
        } else if (randomMaterialR < 0.5)
        {
            randomMaterial = std::make_shared<MetalMaterial>(
                color{Random::randomDouble(), Random::randomDouble(), Random::randomDouble()}, Random::randomDouble());
        } else
        {
            randomMaterial = std::make_shared<DiffuseMaterial>(color{
                Random::randomDouble(), Random::randomDouble(), Random::randomDouble()
            });
        }
        point3 center{Random::randomDouble() * 60 - 30, Random::randomDouble() * 5, Random::randomDouble() * 60 - 30};
        objects.add(std::make_shared<Sphere>(center, Random::randomDouble() * 0.3 + 0.1, randomMaterial));

        camera.m_aspectRatio = 16.0 / 9.0;
        camera.m_imageWidth = 400;
        camera.m_samples = 10;
        camera.m_maxDepth = 10;
        camera.m_vfov = 90;
        camera.m_lookFrom = point3(-2, 2, 1);
        camera.m_lookAt = point3(0, 0, -1);
        camera.m_up = Vec3(0, 1, 0);
    }
}

inline void quads(HittableList &objects, Camera &camera)
{
    // Materials
    auto left_red = std::make_shared<DiffuseMaterial>(color(1.0, 0.2, 0.2));
    auto back_green = std::make_shared<DiffuseMaterial>(color(0.2, 1.0, 0.2));
    auto right_blue = std::make_shared<DiffuseMaterial>(color(0.2, 0.2, 1.0));
    auto upper_orange = std::make_shared<DiffuseMaterial>(color(1.0, 0.5, 0.0));
    auto lower_teal = std::make_shared<DiffuseMaterial>(color(0.2, 0.8, 0.8));

    // Quads
    objects.add(std::make_shared<Quadrilateral>(point3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0), left_red));
    objects.add(std::make_shared<Quadrilateral>(point3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    objects.add(std::make_shared<Quadrilateral>(point3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    objects.add(std::make_shared<Quadrilateral>(point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_orange));
    objects.add(std::make_shared<Quadrilateral>(point3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4), lower_teal));

    camera.m_aspectRatio = 1.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 100;
    camera.m_maxDepth = 50;
    camera.m_vfov = 80;
    camera.m_lookFrom = point3(0, 0, 9);
    camera.m_lookAt = point3(0, 0, 0);
    camera.m_up = Vec3(0, 1, 0);
}

inline void lights(HittableList &objects, Camera &camera)
{
    // Materials
    auto left_red = std::make_shared<DiffuseMaterial>(color(1.0, 0.2, 0.2));
    auto back_green = std::make_shared<DiffuseMaterial>(color(0.2, 1.0, 0.2));
    auto right_blue = std::make_shared<DiffuseMaterial>(color(0.2, 0.2, 1.0));
    auto upper_light = std::make_shared<DiffuseLight>(color(4, 4, 4));
    auto lower_teal = std::make_shared<DiffuseMaterial>(color(0.2, 0.8, 0.8));

    // Quads
    objects.add(std::make_shared<Quadrilateral>(point3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0), left_red));
    objects.add(std::make_shared<Quadrilateral>(point3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    objects.add(std::make_shared<Quadrilateral>(point3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    objects.add(std::make_shared<Quadrilateral>(point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_light));
    objects.add(std::make_shared<Quadrilateral>(point3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4), lower_teal));

    camera.m_aspectRatio = 1.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 100;
    camera.m_maxDepth = 50;
    camera.m_vfov = 80;
    camera.m_lookFrom = point3(0, 0, 9);
    camera.m_lookAt = point3(0, 0, 0);
    camera.m_up = Vec3(0, 1, 0);
    camera.m_background = color(0, 0, 0);
}

inline void cornellBox(HittableList &objects, Camera &camera)
{
    auto red = std::make_shared<DiffuseMaterial>(color(.65, .05, .05));
    auto white = std::make_shared<DiffuseMaterial>(color(.73, .73, .73));
    auto green = std::make_shared<DiffuseMaterial>(color(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(color(15, 15, 15));

    objects.add(std::make_shared<Quadrilateral>(point3(555, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), green));
    objects.add(std::make_shared<Quadrilateral>(point3(0, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), red));
    objects.add(std::make_shared<Quadrilateral>(point3(343, 554, 332), Vec3(-130, 0, 0), Vec3(0, 0, -105), light));
    objects.add(std::make_shared<Quadrilateral>(point3(0, 0, 0), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    objects.add(std::make_shared<Quadrilateral>(point3(555, 555, 555), Vec3(-555, 0, 0), Vec3(0, 0, -555), white));
    objects.add(std::make_shared<Quadrilateral>(point3(0, 0, 555), Vec3(555, 0, 0), Vec3(0, 555, 0), white));

    std::shared_ptr<Hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = std::make_shared<Instance>(box1, Vec3(265, 0, 295), Vec3(0, 15, 0));
    objects.add(box1);

    std::shared_ptr<Hittable> box2 = box(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = std::make_shared<Instance>(box2, Vec3(130, 0, 65), Vec3(0, -18, 0), Vec3(0.5, 1.0, 0.5));
    objects.add(box2);

    camera.m_aspectRatio = 1.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 50;
    camera.m_maxDepth = 10;
    camera.m_background = color(0, 0, 0);
    camera.m_vfov = 40;
    camera.m_lookFrom = point3(278, 278, -800);
    camera.m_lookAt = point3(278, 278, 0);
    camera.m_up = Vec3(0, 1, 0);
}

inline void cornellSmoke(HittableList &objects, Camera &camera)
{
    auto red = std::make_shared<DiffuseMaterial>(color(.65, .05, .05));
    auto white = std::make_shared<DiffuseMaterial>(color(.73, .73, .73));
    auto green = std::make_shared<DiffuseMaterial>(color(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(color(7, 7, 7));

    objects.add(std::make_shared<Quadrilateral>(point3(555, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), green));
    objects.add(std::make_shared<Quadrilateral>(point3(0, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, 555), red));
    objects.add(std::make_shared<Quadrilateral>(point3(113, 554, 127), Vec3(330, 0, 0), Vec3(0, 0, 305), light));
    objects.add(std::make_shared<Quadrilateral>(point3(0, 0, 0), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    objects.add(std::make_shared<Quadrilateral>(point3(555, 555, 555), Vec3(-555, 0, 0), Vec3(0, 0, -555), white));
    objects.add(std::make_shared<Quadrilateral>(point3(0, 0, 555), Vec3(555, 0, 0), Vec3(0, 555, 0), white));

    std::shared_ptr<Hittable> box1 = box(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = std::make_shared<Instance>(box1, Vec3(265, 0, 295), Vec3(0, 15, 0));

    std::shared_ptr<Hittable> box2 = box(point3(0, 0, 0), point3(165, 165, 165), white);
    box2 = std::make_shared<Instance>(box2, Vec3(130, 0, 65), Vec3(0, -18, 0));

    objects.add(std::make_shared<ConstantMedium>(box1, 0.01, color(0, 0, 0)));
    objects.add(std::make_shared<ConstantMedium>(box2, 0.01, color(1, 1, 1)));

    camera.m_aspectRatio = 1.0;
    camera.m_imageWidth = 600;
    camera.m_samples = 200;
    camera.m_maxDepth = 50;
    camera.m_background = color(0, 0, 0);
    camera.m_vfov = 40;
    camera.m_lookFrom = point3(278, 278, -800);
    camera.m_lookAt = point3(278, 278, 0);
    camera.m_up = Vec3(0, 1, 0);
}

inline void finalScene(HittableList &objects, Camera &camera)
{
    HittableList boxes1;
    auto ground = std::make_shared<DiffuseMaterial>(color(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++)
    {
        for (int j = 0; j < boxes_per_side; j++)
        {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = Random::randomDouble() * 100 + 1;
            auto z1 = z0 + w;

            boxes1.add(box(point3(x0, y0, z0), point3(x1, y1, z1), ground));
        }
    }

    objects.add(std::make_shared<BVH>(boxes1));

    auto light = std::make_shared<DiffuseLight>(color(7, 7, 7));
    objects.add(std::make_shared<Quadrilateral>(point3(123, 554, 147), Vec3(300, 0, 0), Vec3(0, 0, 265), light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + Vec3(30, 0, 0);
    auto sphere_material = std::make_shared<DiffuseMaterial>(color(0.7, 0.3, 0.1));
    objects.add(std::make_shared<Sphere>(center1, center2, 50, sphere_material));

    objects.add(std::make_shared<Sphere>(point3(260, 150, 45), 50, std::make_shared<DielectricMaterial>(1.5)));
    objects.add(std::make_shared<Sphere>(
        point3(0, 150, 145), 50, std::make_shared<MetalMaterial>(color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = std::make_shared<Sphere>(point3(360, 150, 145), 70, std::make_shared<DielectricMaterial>(1.5));
    objects.add(boundary);
    objects.add(std::make_shared<ConstantMedium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = std::make_shared<Sphere>(point3(0, 0, 0), 5000, std::make_shared<DielectricMaterial>(1.5));
    objects.add(std::make_shared<ConstantMedium>(boundary, .0001, color(1, 1, 1)));

    auto emat = std::make_shared<DiffuseMaterial>(std::make_shared<ImageTexture>("earthmap.jpg"));
    objects.add(std::make_shared<Sphere>(point3(400, 200, 400), 100, emat));
    auto pertext = std::make_shared<NoiseTexture>(0.2);
    objects.add(std::make_shared<Sphere>(point3(220, 280, 300), 80, std::make_shared<DiffuseMaterial>(pertext)));

    HittableList boxes2;
    auto white = std::make_shared<DiffuseMaterial>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++)
    {
        boxes2.add(std::make_shared<Sphere>(point3{Random::randomDouble() * 165, Random::randomDouble() * 165, Random::randomDouble() * 165}, 10, white));
    }

    objects.add(std::make_shared<Instance>(std::make_shared<BVH>(boxes2), Vec3{-100,270,395}, Vec3{0,15,0}));

    camera.m_aspectRatio = 1.0;
    camera.m_imageWidth = 200;
    camera.m_samples = 1000;
    camera.m_maxDepth = 40;
    camera.m_background = color(0, 0, 0);
    camera.m_vfov = 40;
    camera.m_lookFrom = point3(478, 278, -600);
    camera.m_lookAt = point3(278, 278, 0);
    camera.m_up = Vec3(0, 1, 0);
}

#endif //SCENE_H
