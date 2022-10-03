#ifndef UTILITIES_HPP
#define UTILITIES_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "point3d.hpp"
#include "vector3d.hpp"
#include "objsys.hpp"
#include "event.hpp"
#include "sphere.hpp"
#include "image.hpp"


const double DOUBLE_COMPARISON_PRECISION = 0.001;

static const void *ABSENT_PTR_POISONED_VALUE = (const void *) 0xDEADBEEF;


bool is_in_rectangle(const Point3d *point, const Point3d *rect_angle1, const Point3d *rect_angle2);

bool is_in_rectangle(const Pixel3d *point, const Pixel3d *rect_angle1, const Pixel3d *rect_angle2);

void event_close(DisplayWindow *window);

float get_square(float value);

int get_square(int value);

void set_empty_pixel(Pixel3d *cur_pixel, Image *image);

double calc_Lambert_cos(Vector3d *light_ray_vector, Vector3d *normal_vector);

double calc_specular(const Vector3d *reflected_light_ray_vector, const Vector3d *camera_vector, const size_t specular_deg);

Color calc_pixel_color(Vector3d *light_ray_vector,
                       Vector3d *normal_vector,
                       Vector3d *reflected_light_ray_vector,
                       Vector3d *camera_vector,
                       Color    *sphere_color,
                       Color    *light_source_color,
                       Color    *ambient_color);


int min(int val1, int val2);

int max(int val1, int val2);

double min(double val1, double val2);

double max(double val1, double val2);


#endif