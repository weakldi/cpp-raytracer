#include "camera.hpp"

#include <iostream>

#include "ray.hpp"

glm::dvec3 ray_color(const ray& r) {
    glm::dvec3 unit_direction = glm::normalize(r.m_dir);
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

void camera::render(image& img){
    auto viewport_w = 2.0;
    auto viewport_h = 16.0/9.0 * viewport_w;
    auto focal_len = 1.0;

    origin = glm::dvec3(0,0,0);
    auto horizontal = glm::dvec3(viewport_w,0,0);
    auto vertical   = glm::dvec3(0,viewport_h,0);
    auto lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - glm::dvec3(0,0, focal_len);

    for(int j = img.height()-1; j >= 0; --j){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < img.width(); i++){
            auto u = double(i) / img.width();
            auto v = double(j) / img.height();

            ray r(origin,(lower_left_corner + u*horizontal + v*vertical - origin));

            img.write_rgb(i,j,ray_color(r));
        }
    }
}