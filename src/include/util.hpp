#ifndef UTIL
#define UTIL
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>
#include <cstdint>
#include <cmath>

//includes
#include "ray.hpp"
#include "glm.hpp"
#include "vector_util.hpp"



//using
using std::shared_ptr;
using std::make_shared;
using point3 = glm::dvec3;
using color = glm::dvec3;
//Constants

const double infinity   = std::numeric_limits<double>::infinity();
const double pi         = 3.14159265358979323846;

//functions
bool near_zero(glm::dvec3 in);
glm::dvec3 random_point_in_hemisphere(glm::dvec3 normal);
std::ostream& operator<<(std::ostream& os, const glm::dvec3 vec) ;
//functions inline

inline double random_double(){
    return rand() / (RAND_MAX+1.0);
}

inline double random_double(double min, double max){
    return min + (max-min)*random_double();
}

inline glm::dvec3 random_point_on_unit_sphere(){
    //r = 1
    double phi = random_double()*2*pi;
    double theta = acos((2*random_double()) - 1);
    double sin_phi = sin(phi);
    double x = sin_phi*cos(theta);
    double y = sin_phi*sin(theta);
    double z = cos(phi);
    return glm::dvec3{x,y,z};
}

inline glm::dvec3 random_point_in_unit_sphere(){
    //r = 1
    double phi = random_double()*2*pi;
    double theta = acos((2*random_double()) - 1);
    double r = random_double();
    r = pow(r,1.0/3.0);
    double sin_phi = sin(phi);
    double x = sin_phi*cos(theta);
    double y = sin_phi*sin(theta);
    double z = cos(phi);
    return glm::dvec3{x,y,z};
}


inline glm::dvec3 random_point_in_unit_sphere_2(){
    while(true){
        double x = random_double(-1,1);
        double y = random_double(-1,1);
        double z = random_double(-1,1);
        glm::vec3 vec{x,y,z};
        //std::cout << vec.length() << std::endl;
        if(glm::length(vec)>1.0)continue;
        else return vec;
    }
}

inline glm::dvec3 random_point_in_uint_disc(){
    double r = random_double();
    double theta = random_double() * 2.0 *pi;
   // std::cout << theta << " " << r << " " <<  r*cos(theta) << "  " << r*sin(theta) << " " <<std::endl;
    return glm::dvec3{r*cos(theta), r*sin(theta),0};
}

inline glm::dvec3 random_vec3(){
    return {random_double(),random_double(),random_double()};
}

inline glm::dvec3 random_vec3(double min, double max){
    return {random_double(min, max),random_double(min, max),random_double(min, max)};
}

inline double clamp(double in, double min, double max){
    if(in < min) return min;
    if(in > max) return max;
    return in;
}
#endif /* UTIL */
