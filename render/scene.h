#ifndef SCENE_H
#define SCENE_H

#include "../hittable/hittable_list.h"
#include "camera.h"
#include "../materials/dielectric.h"
#include "../materials/diffuse.h"
#include "../materials/metal.h"
#include "../utility/random.h"
#include "../hittable/sphere.h"
#include "../textures/image_texture.h"
#include "../textures/noise_texture.h"

inline void earth(HittableList &objects, Camera &camera)
{
    auto earthTexture {std::make_shared<ImageTexture>("earthmap.jpg")};
    auto earthSurface {std::make_shared<DiffuseMaterial>(earthTexture)};
    auto earthSphere {std::make_shared<Sphere>(point3{0,0,-1},2,earthSurface)};
    objects.add(earthSphere);

    camera.m_aspectRatio = 16.0 / 9.0;
    camera.m_imageWidth = 400;
    camera.m_samples = 100;
    camera.m_maxDepth = 50;
    camera.m_vfov = 20;
    camera.m_lookFrom = point3(0, 0, 12);
    camera.m_lookAt = point3(0, 0, 0);
    camera.m_up = Vec3(0, 1, 0);
}

inline void perlin(HittableList &objects, Camera &camera)
{
    auto perlinTexture = std::make_shared<NoiseTexture>(8);
    objects.add(std::make_shared<Sphere>(point3(0,-1000,0), 1000, std::make_shared<DiffuseMaterial>(perlinTexture)));
    objects.add(std::make_shared<Sphere>(point3(0,2,0), 2, std::make_shared<DiffuseMaterial>(perlinTexture)));

    camera.m_aspectRatio      = 16.0 / 9.0;
    camera.m_imageWidth       = 400;
    camera.m_samples = 100;
    camera.m_maxDepth         = 50;
    camera.m_vfov     = 20;
    camera.m_lookFrom = point3(13,2,3);
    camera.m_lookAt   = point3(0,0,0);
    camera.m_up      = Vec3(0,1,0);
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

#endif //SCENE_H
