#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "camera.hpp"
#include "hittable.hpp"

struct world : public hittable{
    public:
        world() {}

        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record);
};
#endif