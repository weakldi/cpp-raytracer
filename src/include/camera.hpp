#ifndef CAMERA_H
#define CAMERA_H

#include "util.hpp"
#include "world.hpp"
#include "image.hpp"


struct camera{
    public:
        camera(){
            origin = {0,0,0};
            sampels = 100;
        }

        ray get_ray(double u, double v) const;
        void render(const world& world, image& img) const;

    public:
        glm::dvec3 origin;
        glm::dvec3 eye;
        glm::dvec3 up;
        uint32_t sampels;
};

#endif