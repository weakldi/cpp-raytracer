#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "util.hpp"
#include "hittable.hpp"


class world : public hittable{
    public:
        world() {}
        
        void clear() {objects.clear();}
        void add(shared_ptr<hittable> obj){ objects.push_back(obj);}


        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const override; 
    private:
        std::vector<shared_ptr<hittable>> objects;
};
#endif /* WORLD */
