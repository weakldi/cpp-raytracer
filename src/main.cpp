#include <iostream>
#include <fstream>


#include "util.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "world.hpp"
#include "hittable_types.hpp"

#include "ray.hpp"


void gen_world(world& w){
    auto ground_material = make_shared<diffuse>(color(0.5, 0.5, 0.5));
    w.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_vec3() * random_vec3();
                    sphere_material = make_shared<diffuse>(albedo);
                    w.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_vec3(0.5,1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    w.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(glm::dvec3{1,1,1},1.5);
                    w.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(glm::dvec3{1,1,1},1.5);
    w.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<diffuse>(color(0.4, 0.2, 0.1));
    w.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    w.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
}

int main(int argc, char** argv) {
    image img(static_cast<int32_t>(500 * (16.0/9.0)) , 500);
    point3 origin(13,2,3);
    point3 lookat(0,0,0);
    dvec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam{origin,lookat, vup,16.0/9.0,20,aperture,dist_to_focus};
    cam.sampels = 50;
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
    //gen_world(w);


    auto material1 = make_shared<dielectric>(glm::dvec3{1,1,1},1.5);
    w.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<diffuse>(color(0.4, 0.2, 0.1));
    w.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    w.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    //cam.render(w, img);
    //aabb test{{0,0,0}, {1,1,1}};
    aabb test(glm::vec3{0,0,0}, glm::vec3{1,1,1});
    ray r {{0,-1,0}, {1,1,1}};
    
    std::cout << test.hit(r) << "\n";
    if(out.is_open()){
        std::cout << "Writing...";
        out << img;
        std::cout << " Done!\n";
    }

    out.close();
    
}
