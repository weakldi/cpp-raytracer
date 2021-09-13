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
    shared_ptr<diffuse> mat = make_shared<diffuse>(glm::dvec3{0.5,0.5,0.5});

    auto material_ground = make_shared<diffuse>(glm::dvec3(0.8, 0.8, 0.0));
    auto material_center = make_shared<dielectric>(glm::dvec3(1,1,1),1.5);
    auto material_left   = make_shared<dielectric>  (glm::dvec3(1, 1, 1),1.5);
    auto material_right  = make_shared<metal>  (glm::dvec3(0.8, 0.6, 0.2), 1);

    w.add(make_shared<sphere>(glm::dvec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    w.add(make_shared<sphere>(glm::dvec3( 0.0,    0.0, -1.0),   0.5, material_center));
    w.add(make_shared<sphere>(glm::dvec3(-1.0,    0.0, -1.0),   0.5, material_left));
    w.add(make_shared<sphere>(glm::dvec3( 1.0,    0.0, -1.0),   0.5, material_right));

    cam.render(w, img);
    
    if(out.is_open()){
        std::cout << "Writing...";
        out << img;
        std::cout << " Done!\n";
    }

    out.close();
    
}
