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
#include "camera.hpp"
#include "displaywindow.hpp"


class  Sphere;
struct SphereArr;
class  Camera;
class  DisplayWindow;


class Image
{
private:

    int width_  = 0;
    int height_ = 0;

    sf::Image image_{};

public:

    Image(){};

    void create(int width, int height, const Color &color);

    void set_pixel(int x_coord, int y_coord, const Color &color);

    void render(DisplayWindow *window, const Camera &camera, const SphereArr &spheres);

    unsigned get_width() const
    {
        return width_;
    }
    unsigned get_height() const
    {
        return height_;
    }

    const sf::Image &get_image_ref() const   //
    {                                        // required for drawing image
        return image_;                       //
    }                                        //
};

const size_t MAX_RAY_COLOR_RECURSION_DEPTH      = 5;
const size_t ANTI_ALIASING_PROCESSING_PER_PIXEL = 100;

#endif