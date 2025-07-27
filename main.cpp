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
    randomScene(objects, camera);

    auto before{std::chrono::high_resolution_clock::now()};
    HittableList bvhList{};
    bvhList.add(std::make_shared<BVH>(objects));
    auto after{std::chrono::high_resolution_clock::now()};
    auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(after - before)};
    std::cerr << "BVH construction took " << duration.count() << " ms\n";

    std::cerr << "Program started\n";
    before = std::chrono::high_resolution_clock::now();
    camera.render(bvhList);
    after = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(after - before);
    std::cerr << "Render took " << duration.count() << " ms";
}
