#ifndef BVH_HPP
#define BVH_HPP

#include "hittable.hpp"
#include "aabb.hpp"

struct bvh_node : hittable{
    public:
        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const override;
        virtual aabb bounding_box() const override;
    public:
        struct pointer{
            std::unique_ptr<bvh_node> left;
            std::unique_ptr<bvh_node> right;
        };
    
    public:
        union {
            pointer p;
            std::shared_ptr<hittable> obj;
        } value;
        bool leaf = true;
        aabb m_aabb;

};
struct bvh : public hittable{
    public:
        bvh();
        void add(const hittable& obj);
        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const override;
        virtual aabb bounding_box() const override;
    private:
        std::unique_ptr<bvh_node> left = nullptr;
        std::unique_ptr<bvh_node> right = nullptr;
};


#endif /*end bvh.hpp */