#include "utilities.hpp"
#include "displaywindow.hpp"


bool is_in_rectangle(const Point3d *point, const Point3d *rect_angle1, const Point3d *rect_angle2)
{
    assert(point       != nullptr);
    assert(rect_angle1 != nullptr);
    assert(rect_angle2 != nullptr);

    return ((rect_angle1->get_x() - DOUBLE_COMPARISON_PRECISION < point->get_x()) && (point->get_x() < rect_angle2->get_x() + DOUBLE_COMPARISON_PRECISION) &&
            (rect_angle1->get_y() - DOUBLE_COMPARISON_PRECISION < point->get_y()) && (point->get_y() < rect_angle2->get_y() + DOUBLE_COMPARISON_PRECISION))
    ? true : false;
}

bool is_in_rectangle(const Pixel3d *point, const Pixel3d *rect_angle1, const Pixel3d *rect_angle2)
{
    assert(point       != nullptr);
    assert(rect_angle1 != nullptr);
    assert(rect_angle2 != nullptr);

    return ((rect_angle1->get_x() <= point->get_x()) && (point->get_x() <= rect_angle2->get_x()) &&
            (rect_angle2->get_y() <= point->get_y()) && (point->get_y() <= rect_angle1->get_y()))
    ? true : false;
}

float get_square(float value)
{
    assert(std::isfinite(value));

    return value * value;
}

int get_square(int value)
{
    return value * value;
}

void set_empty_pixel(Pixel3d *cur_pixel, Image *image)
{
    assert(cur_pixel != nullptr);
    assert(image     != nullptr);

    Color empty_pixel_color{GREY};
    image->set_pixel(cur_pixel->get_x(), cur_pixel->get_y(), &empty_pixel_color);  
}

double calc_Lambert_cos(Vector3d *light_ray_vector, Vector3d *normal_vector)
{
    assert(light_ray_vector != nullptr);
    assert(normal_vector    != nullptr);

    double Lambert_cos = cos_between_vectors(light_ray_vector,
                                             normal_vector);

    return Lambert_cos < DOUBLE_COMPARISON_PRECISION ? 0 : Lambert_cos;
}

double calc_specular(const Vector3d *reflected_light_ray_vector, const Vector3d *camera_vector, const size_t specular_deg)
{
    assert(reflected_light_ray_vector != nullptr);
    assert(camera_vector              != nullptr);

    double cos_specular_base = cos_between_vectors(reflected_light_ray_vector,
                                                   camera_vector);
    if (cos_specular_base < DOUBLE_COMPARISON_PRECISION)
    {
        cos_specular_base = 0;
    }
    
    return pow(cos_specular_base, specular_deg);
}

Color calc_pixel_color(Vector3d *light_ray_vector,
                       Vector3d *normal_vector,
                       Vector3d *reflected_light_ray_vector,
                       Vector3d *camera_vector,
                       Color    *sphere_color,
                       Color    *light_source_color,
                       Color    *ambient_color)
{
    assert(light_ray_vector           != nullptr);
    assert(normal_vector              != nullptr);
    assert(reflected_light_ray_vector != nullptr);
    assert(camera_vector              != nullptr);
    assert(sphere_color               != nullptr);
    assert(light_source_color         != nullptr);
    assert(ambient_color              != nullptr);

    double cos_Lambert_law = calc_Lambert_cos(light_ray_vector,
                                              normal_vector);

    double specular = calc_specular(reflected_light_ray_vector,
                                    camera_vector, 3);

    Color Lambert_component  = *sphere_color * *light_source_color * cos_Lambert_law;
    Color ambient_component  = *sphere_color * *light_source_color * *ambient_color;
    Color specular_component = *light_source_color * specular;

    return Lambert_component + ambient_component + specular_component;
}

void event_close(DisplayWindow *window)
{
    assert(window != nullptr);

    window->close();
}

int min(int val1, int val2)
{
    return val1 > val2 ? val2 : val1;
}

int max(int val1, int val2)
{
    return val1 > val2 ? val1 : val2;
}

double min(double val1, double val2)
{
    return val1 - val2 > DOUBLE_COMPARISON_PRECISION ? val2 : val1;
}

double max(double val1, double val2)
{
    return val1 - val2 > DOUBLE_COMPARISON_PRECISION ? val1 : val2;
}
