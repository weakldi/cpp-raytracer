#ifndef IMAGE
#define IMAGE

#include "util.hpp"

struct image{
    image() = delete;
    image(const int32_t w, const int32_t h) :
        m_width(w), m_height(h) {
            m_data = new int32_t[w*h];
        };
    ~image(){
        delete[] m_data;
    }

    inline void write_rgb(const int32_t x, const int32_t y,const glm::dvec3 color, uint32_t samples){
        double scale = 1.0 / samples;
        /*
            double r = sqrt(color.r * scale);
        double g = sqrt(color.g * scale);
        double b = sqrt(color.b * scale);

        */
        glm::dvec3 _color =  glm::sqrt(color*scale);
        int32_t c = (static_cast<int32_t>(256 * clamp(_color.r, 0, 0.999)) << 16) | 
                    (static_cast<int32_t>(256 * clamp(_color.g, 0, 0.999)) << 8 ) |
                    (static_cast<int32_t>(256 * clamp(_color.b, 0, 0.999)) <<  0);
        write_rgb(x,y,c);
    }

    inline void write_rgb(const int32_t x, const int32_t y,const glm::dvec3 color){
        int32_t c = (static_cast<int32_t>(255.999 * color.r) << 16) | 
                    (static_cast<int32_t>(255.999 * color.g) << 8 ) |
                    (static_cast<int32_t>(255.999 * color.b) <<  0);
        write_rgb(x,y,c);
    }

    inline void write_rgb(const int32_t x, const int32_t y, int32_t rgb){
        m_data[x+(m_width*(m_height-1-y))] = rgb;
    }

    inline int32_t get_rgb(const int32_t x, const int32_t y){
        return  m_data[x+m_width*y];
    }

    void write_to_stream(std::ostream &out) const{
        out << "P3\n" << m_width << " " <<  m_height << "\n255\n";
        for(uint64_t i = 0; i < m_width*m_height;i++)
        {
            int color = m_data[i];
            out << ((color & 0xFF0000) >> 16) << " "
                << ((color & 0x00FF00) >> 8)  << " "
                << (color & 0x0000FF) << std::endl;
        }
        
    }

    inline int32_t width() const {return m_width;} 
    inline int32_t height() const {return m_height;} 

    friend std::ostream& operator<<(std::ostream& os, const image& img) {
        img.write_to_stream(os);
        return os;
    }


    private:
        int32_t m_width, m_height;
        int32_t* m_data;

};



#endif /* IMAGE */
