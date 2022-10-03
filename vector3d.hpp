#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "point3d.hpp"
#include "pixel3d.hpp"
#include "color.hpp"


class CoordSys;
class DisplayWindow;


class Vector3d : public Drawable    // not drawable but shape
{
private:

    float x_coord_ = 0;
    float y_coord_ = 0;
    float z_coord_ = 0;

public:
    
    Vector3d()
    {
        type_ = DrawableType::VECTOR;
    }

    Vector3d(float x_coord, float y_coord, float z_coord = 0);

    Vector3d(const Point3d *beginning, const Point3d *ending);

    Vector3d(const Pixel3d *beginning, const Pixel3d *ending);

    Vector3d(const Point3d *radius_vector_ending);

    Vector3d(const Pixel3d *radius_vector_ending);

    float get_x() const
    {
        return x_coord_;
    }
    float get_y() const
    {
        return y_coord_;
    }
    float get_z() const
    {
        return z_coord_;
    }

    void set_x(const float x)
    {
        x_coord_ = x;
    }
    void set_y(const float y)
    {
        y_coord_ = y;
    }
    void set_z(const float z)
    {
        z_coord_ = z;
    }


    void operator +=(const Vector3d &another_vector)
    {
        x_coord_ += another_vector.x_coord_;
        y_coord_ += another_vector.y_coord_;
        z_coord_ += another_vector.z_coord_;
    }

    void operator -=(const Vector3d &another_vector)
    {
        x_coord_ -= another_vector.x_coord_;
        y_coord_ -= another_vector.y_coord_;
        z_coord_ -= another_vector.z_coord_;
    }

    void operator *=(float scalar)
    {
        x_coord_ *= scalar;
        y_coord_ *= scalar;
        z_coord_ *= scalar;
    }

    Vector3d operator +(const Vector3d &another_vector) const
    {
        Vector3d result = *this;
        result += another_vector;        

        return result;
    }
    
    Vector3d operator -(const Vector3d &another_vector) const
    {
        Vector3d result = *this;
        result -= another_vector;

        return result;
    }
    
    Vector3d operator *(float scalar) const
    {
        Vector3d result = *this;
        result *= scalar;

        return result;
    }

    Vector3d operator -() const
    {
        return {-x_coord_, -y_coord_, -z_coord_};
    }

    float operator *(const Vector3d &another_vector)
    {
        return (get_x() * another_vector.get_x() +
                get_y() * another_vector.get_y() +
                get_z() * another_vector.get_z());
    }
};

Vector3d get_reflected_vector(Vector3d *to_reflect, Vector3d *normal_vector);

void multiply_vector(Vector3d *vector, float multiplier);

float get_vector_length_square(const Vector3d *vector);

void normalize_vector(Vector3d *vector);

void set_vector_length(Vector3d *vector, float length);

float scalar_multiplication(const Vector3d *opd1, const Vector3d *opd2);

float cos_between_vectors(const Vector3d *opd1, const Vector3d *opd2);

Vector3d get_reflected(const Vector3d &cur_vector, const Vector3d &normal_vector);

#endif
