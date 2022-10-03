#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vector3d.hpp"
#include "color.hpp"


const size_t MAX_LIGHTS_QUANTITY_SCENE = 1024;


class LightSource
{
public:

    Vector3d position_{};
    Color    color_{};
    float    intensity_ = 1;

    LightSource(){};

    LightSource(Vector3d position, Color color, float intensity = 1)
    :  position_  (position),
       color_     (color),
       intensity_ (intensity)
    {}
};


// enum LightSourceArrErrors
// {
//     OK,
//     OVERFLOW
// };


struct LightSourceArr
{
    LightSource *array_[MAX_LIGHTS_QUANTITY_SCENE] = {};
    size_t size_ = 0;

    int add(LightSource *new_light_source)
    {
        assert(new_light_source != nullptr);

        if (size_ >= MAX_LIGHTS_QUANTITY_SCENE)
        {
            return 1;
        }

        array_[size_] = new_light_source;

        ++size_;

        return 0;
    }  
};

#endif