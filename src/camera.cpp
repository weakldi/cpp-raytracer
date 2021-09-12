#include "camera.hpp"

#include <iostream>
#include "util.hpp"
#include "sphere.hpp"

glm::dvec3 ray_color(const ray& r, const world& world) {
    glm::dvec3 unit_direction = glm::normalize(r.m_dir);

    
    hit_record record;
    if(world.hit(r,-0, infinity, record))
    {
        //return {1,0,0};
        return 0.5*(record.normal+glm::dvec3(1,1,1));
    }

    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

void camera::render(const world& world, image& img) const{
    const auto aspect_ratio = (double)img.width() / (double)img.height();
    auto viewport_h = 2.0;
    auto viewport_w = aspect_ratio * viewport_h;
    auto focal_len = 1.0;

    
    auto horizontal = glm::dvec3(viewport_w,0,0);
    auto vertical   = glm::dvec3(0,viewport_h,0);
    auto lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - glm::dvec3(0,0, focal_len);

    for(int j = img.height()-1; j >= 0; --j){
        std::cout << "\rScanlines remaining: " << j << ' ' << std::endl;
        for(int i = 0; i < img.width(); i++){
            auto u = double(i) / (img.width()-1);
            auto v = double(j) / (img.height()-1);

            ray r(origin,(lower_left_corner + u*horizontal + v*vertical - origin));

            img.write_rgb(i,j,ray_color(r, world));
        }
    }
}