#include "world.hpp"



bool world::hit(const ray& ray,double t_min, double t_max, hit_record& hit_rec) const{
    hit_record tmp_hit;
    bool hit = false;
    double closest = t_max;
    for(const auto& obj : objects)
    {
        if(obj->hit(ray, t_min, t_max, tmp_hit))
        {
            hit = true;
            closest = tmp_hit.time;
            hit_rec = tmp_hit;
        }
    }

    return hit;
}