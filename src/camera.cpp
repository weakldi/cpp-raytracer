#include "camera.hpp"

#include <iostream>
#include "util.hpp"
#include "sphere.hpp"

camera::camera(double aspect_ratio, double vfov){
    //auto aspect_ratio = 16.0/9.0;
    origin = {0,0,0};
    look_at = {0,0,-1};
    up = {0,1,0};
    focus_dist = 1;
    lens_radius = 0;
    recalculate_viewport(aspect_ratio, vfov);
}

camera::camera(point3 origin, point3 look_at, point3 up,double aspect_ratio, double vfov,double aperture, double focus_dist)
    :origin(origin), look_at(look_at), up(up), focus_dist(focus_dist) , lens_radius(aperture/2.0)
{
    recalculate_viewport(aspect_ratio, vfov);
}

void camera::recalculate_viewport(double aspect_ratio, double vfov){
    auto theta = (double(vfov) / 180.0)*pi;

    auto h = tan(theta/2);

    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    

    w = glm::normalize(origin - look_at);
    u = glm::normalize(glm::cross(up, w));
    v = glm::normalize(glm::cross(w, u));
    std::cout << u << " v: " << v << " w:" << w <<  " focus_dist: " << focus_dist << " lens_radius: " << lens_radius << std::endl;
    horizontal = focus_dist * viewport_width * u;
    vertical   = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - focus_dist*w;

}


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
        return {0,0,0};
        
    }
    auto unit_direction = glm::normalize(r.m_dir);
    //if(unit_direction.y > 0 && unit_direction.x > 0)return {1,0,0};
    //if(unit_direction.y < 0 && unit_direction.x > 0)return {0,1,0};
    //if(unit_direction.y > 0 && unit_direction.x < 0)return {0,0,1};
    //if(unit_direction.y < 0 && unit_direction.x < 0)return {1,0,1};
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*glm::dvec3(1.0, 1.0, 1.0) + t*glm::dvec3(0.5, 0.7, 1.0);
}

ray camera::get_ray(double s, double t) const {
    auto rd = lens_radius * random_point_in_uint_disc();
    //std::cout << rd << std::endl;
    auto offset = u* rd.x + v* rd.y;
    return ray(origin+offset,
            (lower_left_corner + s*horizontal + t*vertical - origin - offset));
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

                ray r = get_ray(u,v);
                
                color += ray_color(r,world,50);
            }
            
            img.write_rgb(i,j,color,sampels);
        }
    }
}