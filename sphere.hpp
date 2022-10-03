#ifndef SPHERE_HPP
#define SPHERE_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vector3d.hpp"
#include "pixel3d.hpp"
#include "lightsource.hpp"
#include "image.hpp"
#include "material.hpp"


const size_t MAX_SPHERES_QUANTITY_SCENE = 1024;


class Image;


class Sphere
{
private:

    Vector3d origin_{};
    Material material_{};
    
    float radius_ = 0;

public:

    Sphere(){};

    Sphere(const Point3d &origin, float radius, const Material &material)
      : radius_(radius),
        material_ (material)
    {
        assert(std::isfinite(radius));
        assert(radius > 0);

        origin_.set_x(origin.get_x());
        origin_.set_y(origin.get_y());
        origin_.set_z(origin.get_z());
    }
    
    Sphere(const Vector3d &origin, float radius, const Material &material)
      : origin_(origin),
        radius_(radius),
        material_(material)
    {
        assert(std::isfinite(radius));
        assert(radius > 0);
    }
    
    Sphere(float x_origin, float y_origin, float z_origin, float radius, const Material &material)
      :  radius_(radius),
         material_ (material)
    {
        assert(std::isfinite(radius));
        assert(radius > 0);

        origin_.set_x(x_origin);
        origin_.set_y(y_origin);
        origin_.set_z(z_origin);
    }

    float get_x_origin() const
    {
        return origin_.get_x();
    }
    float get_y_origin() const
    {
        return origin_.get_y();
    }
    float get_z_origin() const 
    {
        return origin_.get_z();
    }
    Vector3d get_origin() const
    {
        return origin_;
    }
    const Vector3d &get_origin_ptr() const
    {
        return origin_;
    }
    

    float get_radius() const
    {
        return radius_;
    }
    Material get_material() const
    {
        return material_;
    }

    void set_x_origin(float x_origin)
    {
        origin_.set_x(x_origin);
    }
    void set_y_origin(float y_origin)
    {
        origin_.set_y(y_origin);
    }
    void set_z_origin(float z_origin)
    {
        origin_.set_z(z_origin);
    }
    void set_radius(float radius)
    {
        assert(std::isfinite(radius));
        assert(radius > 0);

        radius_ = radius;
    }

    void set_material(Material material)
    {
        material_ = material;
    }

    // void draw(Image *image, LightSource *light_source, Color *ambient_light, Point3d *camera);
};


// enum SphereArrErrors
// {
//     OK,
//     OVERFLOW
// };


struct SphereArr
{
    Sphere *array_[MAX_SPHERES_QUANTITY_SCENE] = {};
    size_t size_ = 0;

    int add(Sphere *new_sphere)
    {
        assert(new_sphere != nullptr);

        if (size_ >= MAX_SPHERES_QUANTITY_SCENE)
        {
            return 1;
        }

        array_[size_] = new_sphere;
        ++size_;

        return 0;
    }
};


bool is_in_sphere_2d(Pixel3d *pixel, Sphere *sphere);

float get_sphere_point_z_coord(Sphere *sphere, float x_pos, float y_pos);

bool ray_intersects_sphere(const Sphere *sphere,         float *distance,
                           const Vector3d &origin, const Vector3d &direction);

#endif
