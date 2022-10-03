#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vector3d.hpp"
#include "color.hpp"
// #include "materiallibrary.hpp"


struct Material
{
    Vector3d albedo_{};
    Color color_{};
    float specular_pow_ = 0;


    Material(){};

    Material(const Vector3d &albedo, const Color &color, const float &spec)
      :  albedo_       (albedo),
         color_        (color),
         specular_pow_ (spec)
    {}


};


const Material LIME_GLASS    = {{0.8, 0.7, 1}, LIME,   100};
const Material TOMATO_RUBBER = {{1,   0.7, 1}, TOMATO, 3};
const Material RED_GLASS     = {{0.8, 0.7, 1}, ABOBA,  100};


#endif