#ifndef CAMERA
#define CAMERA

#include "util.hpp"
#include "world.hpp"
#include "image.hpp"


struct camera{
    public:
        camera() = delete;
        camera(double aspect_ratio, double vfov);
        camera(point3 origin, point3 look_at, point3 up,double aspect_ratio, double vfov, double aperture, double focus_dist);
        
        ray get_ray(double u, double v) const;
        void render(const world& world, image& img) const;
        
       
        void recalculate_viewport(double aspect_ratio, double vfov);

        void set_aperture(double aperture){
            lens_radius = aperture / 2.0;
        }
    private:
        void render_scann_line(const world& world, image& img, int32_t j);
    public:
        point3 origin;
        point3 look_at;
        glm::dvec3 up;
        uint32_t sampels = 10;
        glm::dvec3 horizontal;
        glm::dvec3 vertical;
        glm::dvec3 lower_left_corner;
        double vfov;
        double focus_dist;
        double lens_radius;
    private:
        glm::dvec3 u,v,w;

};

#endif /* CAMERA */
