#include "aabb.hpp"
#include "cstdio"
#include "gtc/type_ptr.hpp"
#include "gtx/string_cast.hpp"

void inline min_max(double a, double b, double& out_min, double& out_max) {
    if(a < b){
        out_min = a;
        out_max = b;
    }else{
        out_min = b;
        out_max = a;
    }
}

double dmin(double a, double b)
{
    return a < b ? a : b;
}
double dmax(double a, double b)
{
    return a > b ? a : b;
}


aabb::aabb(const glm::dvec3& pos1, const glm::dvec3& pos2) {
    min_max(pos1.x, pos2.x, min.x, max.x);
    min_max(pos1.y, pos2.y, min.y, max.y);
    min_max(pos1.z, pos2.z, min.z, max.z);
} 


bool aabb::hit(const ray& ray) const{
    /**
     * @brief https://raytracing.github.io/books/RayTracingTheNextWeek.html#boundingvolumehierarchies/axis-alignedboundingboxes(aabbs)
     * 
     */
    /*
    float x1 = min.x;
    float x2 = max.x;
    float y1 = min.y;
    float y2 = max.y;
    float z1 = min.z;
    float z2 = max.z;

    float dy_dx = ray.m_dir.y/ray.m_dir.x;
    float dx_dz = ray.m_dir.y/ray.m_dir.z;
    float dz_dy = ray.m_dir.y/ray.m_dir.z;
    
    float hitX1 = (dy_dx)*(y1 - ray.m_orig.y);
    float hitX2 = (dy_dx)*(y2 - ray.m_orig.y);

    float hitY1 = (dz_dy)*(z1 - ray.m_orig.z);
    float hitY2 = (dz_dy)*(z2 - ray.m_orig.z);
    
    float hitZ1 = (dx_dz)*(x1 - ray.m_orig.x);
    float hitZ2 = (dx_dz)*(x2 - ray.m_orig.x);

    //search first hit
    */
    for(int i = 0; i < 3; i ++){
        auto invese_m = 1.0/ glm::value_ptr(ray.m_dir)[i];
        double t0; 
        double t1;
        min_max((glm::value_ptr(min)[i] - glm::value_ptr(ray.m_orig)[i]), 
                (glm::value_ptr(max)[i] - glm::value_ptr(ray.m_orig)[i]), t0,t1);

        if(invese_m < 0)std::swap(t0,t1);
        auto t_min = dmax(t0, glm::value_ptr(min)[i]);
        auto t_max = dmin(t1, glm::value_ptr(max)[i]);
        /*
        printf("t0=%f, t1=%f,\n origin=%s\n dir=%s\n min=%s\n max=%s\n", t0,t1, glm::to_string(ray.m_orig).c_str()
                                                                    ,   glm::to_string(ray.m_dir) .c_str()
                                                                    ,   glm::to_string(min)      .c_str()  
                                                                    ,   glm::to_string(max).c_str()
                                                                    );
        */


        if(t_min >= t_max)return false;
    }
    

    //printf("hit: {%f, %f}\n", hitX1, hitX2);
    return true;
}