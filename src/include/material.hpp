#ifndef MATERIAL
#define MATERIAL
#include "util.hpp"
#

struct hit_record;

class material{
    public:
        virtual bool scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const = 0;
        
};

class diffuse : public material{
    public:
        diffuse() = delete;
        diffuse(const glm::dvec3& color) 
            : color(color) {}
        virtual bool scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const override;
    public:
        glm::dvec3 color;
};

class metal : public material{
    public:
        metal() = delete;
        metal(const glm::dvec3& color,const double fuzz) 
            : color(color), fuzz(fuzz) {}
        virtual bool scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const override;
    public:
        glm::dvec3 color;
        double fuzz;
};
#endif /* MATERIAL */
