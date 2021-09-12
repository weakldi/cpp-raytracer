#include <iostream>

#include "glm.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "world.hpp"

int main(int, char**) {
    image img(static_cast<int32_t>(400 * (16.0/9.0)) , 400);
    camera cam{};

    cam.render(img);

    std::cout << img;
}
