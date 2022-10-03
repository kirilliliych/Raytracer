#include "vector3d.hpp"
#include "displaywindow.hpp"
#include "coordsys.hpp"


Vector3d::Vector3d(float x_coord, float y_coord, float z_coord)
  : x_coord_(x_coord),
    y_coord_(y_coord),
    z_coord_(z_coord)
{
    assert(std::isfinite(x_coord));
    assert(std::isfinite(y_coord));
    assert(std::isfinite(z_coord));

    type_ = DrawableType::VECTOR;
}

Vector3d::Vector3d(const Point3d *beginning, const Point3d *ending)
{
    assert(beginning != nullptr);
    assert(ending    != nullptr);

    x_coord_ = ending->get_x() - beginning->get_x();
    y_coord_ = ending->get_y() - beginning->get_y();
    z_coord_ = ending->get_z() - beginning->get_z();

    type_ = DrawableType::VECTOR;
}

Vector3d::Vector3d(const Pixel3d *beginning, const Pixel3d *ending)
{
    assert(beginning != nullptr);
    assert(ending    != nullptr);

    x_coord_ = ending->get_x() - beginning->get_x();
    y_coord_ = ending->get_y() - beginning->get_y();
    z_coord_ = ending->get_z() - beginning->get_z();

    type_ = DrawableType::VECTOR;
}

Vector3d::Vector3d(const Point3d *radius_vector_ending)
{
    assert(radius_vector_ending != nullptr);

    x_coord_ = radius_vector_ending->get_x();
    y_coord_ = radius_vector_ending->get_y();
    z_coord_ = radius_vector_ending->get_z(); 
}

Vector3d::Vector3d(const Pixel3d *radius_vector_ending)
{
    assert(radius_vector_ending != nullptr);

    x_coord_ = radius_vector_ending->get_x();
    y_coord_ = radius_vector_ending->get_y();
    z_coord_ = radius_vector_ending->get_z(); 
}

Vector3d get_reflected_vector(Vector3d *to_reflect, Vector3d *normal_vector)
{
    assert(to_reflect    != nullptr);
    assert(normal_vector != nullptr);

    float cos_between = cos_between_vectors(to_reflect, normal_vector);

    Vector3d updated_normal = *normal_vector;
    multiply_vector(&updated_normal, 2 * cos_between);

    Vector3d reflected = updated_normal - *to_reflect;

    return reflected;
}

void multiply_vector(Vector3d *vector, float multiplier)
{
    assert(vector != nullptr);
    assert(std::isfinite(multiplier));

    vector->set_x(vector->get_x() * multiplier);
    vector->set_y(vector->get_y() * multiplier);
    vector->set_z(vector->get_z() * multiplier);

}

float get_vector_length_square(const Vector3d *vector)
{
    assert(vector != nullptr);

    return get_square(vector->get_x()) + get_square(vector->get_y()) + get_square(vector->get_z());
}

void normalize_vector(Vector3d *vector)
{
    assert(vector != nullptr);

    float denominator = get_vector_length_square(vector);
    assert(denominator != 0);

    double sqrt_denom = sqrt(denominator);
    vector->set_x(vector->get_x() / sqrt_denom);
    vector->set_y(vector->get_y() / sqrt_denom);
    vector->set_z(vector->get_z() / sqrt_denom);
}

void set_vector_length(Vector3d *vector, float length)
{
    assert(vector != nullptr);

    normalize_vector(vector);
    multiply_vector (vector, length);
}

float scalar_multiplication(const Vector3d *opd1, const Vector3d *opd2)
{
    assert(opd1 != nullptr);
    assert(opd2 != nullptr);

    return opd1->get_x() * opd2->get_x() +
           opd1->get_y() * opd2->get_y() +
           opd1->get_z() * opd2->get_z();
}

float cos_between_vectors(const Vector3d *opd1, const Vector3d *opd2)
{
    assert(opd1 != nullptr);
    assert(opd2 != nullptr);

    return scalar_multiplication(opd1, opd2) / (sqrt(get_vector_length_square(opd1)) * 
                                                sqrt(get_vector_length_square(opd2)));
}

Vector3d get_reflected(const Vector3d &cur_vector, const Vector3d &normal_vector)
{
    return cur_vector - normal_vector * 2 * cos_between_vectors(&cur_vector, &normal_vector);       // 
}