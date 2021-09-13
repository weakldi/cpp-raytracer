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
            : color(color), fuzz(fuzz < 1? fuzz : 1) {}
        virtual bool scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const override;
    public:
        glm::dvec3 color;
        double fuzz;
};

class dielectric : public material{
    public:
        dielectric() = delete;
        dielectric(const glm::dvec3& color,const double ir) 
            : color(color), ir(ir) {}
        virtual bool scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const override;
    public:
        glm::dvec3 color;
        double ir;
};
#endif /* MATERIAL */
