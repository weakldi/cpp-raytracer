#include "bvh.hpp"


void add(const hittable& obj){

}

bool bvh:: hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const {
    return  (left  == nullptr ? false : left->hit(ray, t_min,t_max,hit_record)) ||
            (right == nullptr ? false : right->hit(ray, t_min,t_max,hit_record));
}
aabb bvh::bounding_box() const  {
    return {{-infinity,-infinity,-infinity}, {infinity,infinity,infinity}};
};


bool bvh_node::hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const {
    if(leaf){
        return value.obj->hit(ray, t_min,t_max,hit_record);
    }else {
        return  (value.p.left  == nullptr ? false : value.p.left->hit(ray, t_min,t_max,hit_record)) ||
                (value.p.right == nullptr ? false : value.p.right->hit(ray, t_min,t_max,hit_record));
    }
}
aabb bvh_node::bounding_box() const {

}