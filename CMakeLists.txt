cmake_minimum_required(VERSION 3.31)
project(ray_tracer_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(ray_tracer_cpp main.cpp
        vector/vector.cpp
        vector/vector.h
        vector/color.h
        vector/ray.h
        hittable/hittable.h
        hittable/sphere.h
        hittable/sphere.cpp
        hittable/hittable_list.h
        hittable/hittable_list.cpp
        render/camera.h
        render/camera.cpp
        materials/material.h
        materials/diffuse.h
        materials/metal.h
        materials/diffuse.cpp
        materials/metal.cpp
        materials/dielectric.h
        materials/dielectric.cpp
        materials/material.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/35b75a2cba6ef72b7ce2b6b94b05c54ca07df866.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        my_tests
        tests/vector_test.cpp
        vector/vector.cpp
)
target_link_libraries(
        my_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(my_tests)
