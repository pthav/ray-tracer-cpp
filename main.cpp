#include "camera/camera.h"
#include "hittable/hittable_list.h"
#include "hittable/sphere.h"

int main()
{
    // Create Camera
    Camera camera{};

    // Create scene of objects
    HittableList objects{};
    objects.add(std::make_shared<Sphere>(Sphere{0, 0, -1, 0.5}));

    camera.render(objects);
}
