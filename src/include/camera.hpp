#ifndef CAMERA_H
#define CAMERA_H
#include <glm.hpp>

#include "image.hpp"


struct camera{
    public:
        camera(){
            origin = {0,0,0};
        }


        void render(image& img);

    public:
        glm::dvec3 origin;
        glm::dvec3 eye;
        glm::dvec3 up;
};

#endif