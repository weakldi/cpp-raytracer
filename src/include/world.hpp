#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "util.hpp"
#include "hittable.hpp"
#include "bvh.hpp"

class world : public hittable{
    public:
        world() {}
        
        void clear() {objects.clear();}
        void add(shared_ptr<hittable> obj){ objects.push_back(obj);}


        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const override;
        virtual aabb bounding_box() const override {return m_bvh.bounding_box();}
    private:
        std::vector<shared_ptr<hittable>> objects;
        bvh m_bvh;
};

#endif /* WORLD */
