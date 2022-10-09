#ifndef CAMERA_HPP
#define CAMERA_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include "ray.hpp"
#include "utilities.hpp"


class Camera
{
public:
    
    Vector3d origin_{0, 0, 0};
    Vector3d horizontal_component_{};
    Vector3d vertical_component_{};
    Vector3d lower_left_corner_{};


    Camera(const Vector3d &origin, const Vector3d &lookat, const Vector3d &vector_up, float fov, float ratio);

    Ray get_ray(float x_viewport_pos, float y_viewport_pos) const;
};


#endif