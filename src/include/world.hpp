#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "camera.hpp"
#include "hittable.hpp"

struct world : public hittable{
    public:
        world() {}

        virtual bool hit(const ray& ray, hit_record& hit_record);
};
#endif