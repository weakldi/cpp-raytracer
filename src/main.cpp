#include <iostream>

#include "glm.hpp"
#include "image.hpp"

int main(int, char**) {
    image img(static_cast<int32_t>(400 * (16.0/9.0)) , 400);

    for(int i = img.width()-1; i >= 0 ; --i){
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for(int j = 0; j < img.height(); j++){
            glm::vec3 c{
                double(i) / img.width(),
                double(j) / img.height(),
                0.25
            };
            img.write_rgb(i,j,c);
        }
    }
    std::cout << img;
}
