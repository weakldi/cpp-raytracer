#include "camera.hpp"

#include <iostream>
#include "util.hpp"
#include "sphere.hpp"

glm::dvec3 ray_color(const ray& r, const world& world, int32_t depth) {
    
    
    if(depth <= 0)
        return glm::dvec3(1.0, 1.0, 1.0);
    
    hit_record record;
    if(world.hit(r,0.001, infinity, record))
    {
        //glm::dvec3 target = record.point+record.normal+random_point_in_hemisphere(record.normal);
        
        //return 0.5*ray_color(ray(record.point, target - record.point), world, --depth);

        ray scattered;
        glm::dvec3 color;
        if(record.mat_ptr->scatter(r,record,color,scattered)){
            return color * ray_color(scattered, world, --depth);
        }
        
    }
    auto unit_direction = glm::normalize(r.m_dir);
    
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

ray camera::get_ray(double u, double v) const {
    return ray({0,0,0},{0,0,0});
}

void camera::render(const world& world, image& img) const{
    const auto aspect_ratio = (double)img.width() / (double)img.height();
    auto viewport_h = 2.0;
    auto viewport_w = aspect_ratio * viewport_h;
    auto focal_len = 1.0;

    
    auto horizontal = glm::dvec3(viewport_w,0,0);
    auto vertical   = glm::dvec3(0,viewport_h,0);
    auto lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - glm::dvec3(0,0, focal_len);

    for(int j = img.height()-1; j >= 0; --j)
    {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::endl;
        for(int i = 0; i < img.width(); i++)
        {
            glm::dvec3 color{0,0,0};
            for(int32_t sampel = 0; sampel < sampels; sampel++)
            {
                
                auto u = (i + random_double()) / (img.width()-1);
                auto v = (j + random_double()) / (img.height()-1);

                ray r(origin,(lower_left_corner + u*horizontal + v*vertical - origin));
                
                color += ray_color(r,world,50);
            }
            
            img.write_rgb(i,j,color,sampels);
        }
    }
}