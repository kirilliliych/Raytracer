#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <cfloat>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "color.hpp"
#include "sphere.hpp"
#include "lightsource.hpp"


const Color ambient_light{0.2, 0.2, 0.2};

const size_t DEPTH_BORDER = 3;


class Sphere;
struct SphereArr;

class Image
{
private:

    unsigned width_  = 0;
    unsigned height_ = 0;

    sf::Image image_{};

public:

    Image(){};

    void create(unsigned width, unsigned height, Color *color);

    void set_pixel(unsigned x_coord, unsigned y_coord, Color *color);

    void render(const SphereArr *spheres, const LightSourceArr *lights, const Point3d *camera);

    unsigned get_width()
    {
        return width_;
    }
    unsigned get_height()
    {
        return height_;
    }

    const sf::Image &get_image_ref()    //
    {                                   // required for drawing image
        return image_;                  //
    }                                   //
};

Color cast_rays(const Vector3d &origin, const Vector3d &direction, const SphereArr *spheres,
                                                                   const LightSourceArr *lights,
                                                                   int depth);

#endif