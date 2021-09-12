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



//using
using std::shared_ptr;
using std::make_shared;

//Constants

const double infinity   = std::numeric_limits<double>::infinity();
const double pi         = 3.14159265358979323846;

//functions
glm::dvec3 random_point_in_hemisphere(glm::dvec3 normal);
//functions inline

inline double random_double(){
    return rand() / (RAND_MAX+1.0);
}

inline double random_double(double min, double max){
    return min + (max-min)*random_double();
}

inline glm::dvec3 random_point_on_unit_sphere(){
    //r = 1
    double theta = random_double(0,2*pi);
    double phi = random_double(0,pi);

    double sin_phi  = std::sin(phi);
    double cos_theta        = std::sin(theta); 

    double x = cos_theta * sin_phi;
    double y = sin_phi * std::sin(theta);
    double z = cos_theta;
    return glm::dvec3{x,y,z};
}

inline glm::dvec3 random_point_in_unit_sphere(){
    double r = random_double();
    r = r/((1-r)*(1-r));
    double theta = random_double(0,2*pi);
    double phi = random_double(0,pi);

    double r_sin_phi  = r*std::sin(phi);
    double cos_theta        = std::sin(theta); 

    double x = cos_theta * r_sin_phi;
    double y = r_sin_phi * std::sin(theta);
    double z = r*cos_theta;
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


inline double clamp(double in, double min, double max){
    if(in < min) return min;
    if(in > max) return max;
    return in;
}
#endif /* UTIL */
