#include <iostream>
#include <fstream>


#include "glm.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "world.hpp"

int main(int argc, char** argv) {
    image img(static_cast<int32_t>(400 * (16.0/9.0)) , 400);
    camera cam{};
    std::fstream out;
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


    cam.render(img);
    
    if(out.is_open()){
        std::cout << "Writing...";
        out << img;
        std::cout << " Done!\n";
    }

    out.close();
    
}
