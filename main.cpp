#include <chrono>
#include <iostream>

#include "hittable/bvh.h"
#include "render/camera.h"
#include "hittable/hittable_list.h"
#include "render/scene.h"

int main()
{
    HittableList objects{};
    Camera camera{};

    // Choose scene
    switch (6)
    {
        case 1: randomScene(objects, camera); break;
        case 2: earth(objects, camera); break;
        case 3: perlin(objects, camera); break;
        case 4: quads(objects, camera); break;
        case 5: lights(objects, camera); break;
        case 6: cornellBox(objects, camera); break;
    }

    // Time BVH construction
    auto before{std::chrono::high_resolution_clock::now()};
    HittableList bvhList{};
    bvhList.add(std::make_shared<BVH>(objects));
    auto after{std::chrono::high_resolution_clock::now()};
    auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(after - before)};
    std::cerr << "BVH construction took " << duration.count() << " ms\n";

    // Time Render
    std::cerr << "Render started\n";
    before = std::chrono::high_resolution_clock::now();
    camera.render(bvhList);
    after = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
    std::cerr << "Render took " << duration.count() << " ms";
}
