#include <iostream>
#include <fstream>


#include "util.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "world.hpp"
#include "hittable_types.hpp"

int main(int argc, char** argv) {
    image img(static_cast<int32_t>(400 * (16.0/9.0)) , 400);
    camera cam{};
    std::fstream out;
    world w;

    if(argc > 1){
        try
        {
            out.open(argv[1], std::ios_base::out);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    }else {
       try
        {
            out.open("image.ppm", std::ios_base::out);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        } 
    }

    w.add(make_shared<sphere>(glm::dvec3{0,0,-1},0.5));


    cam.render(w, img);
    
    if(out.is_open()){
        std::cout << "Writing...";
        out << img;
        std::cout << " Done!\n";
    }

    out.close();
    
}
