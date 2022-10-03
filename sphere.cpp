#include "sphere.hpp"
#include "utilities.hpp"


// void Sphere::draw(Image *image, LightSource *light_source, Color *ambient_light, Point3d *camera)
// {
//     assert(image         != nullptr);
//     assert(light_source  != nullptr);
//     assert(ambient_light != nullptr);
//     assert(camera        != nullptr);

//     image->render(this, light_source, ambient_light, camera);
// }

bool is_in_sphere_2d(Pixel3d *pixel, Sphere *sphere)
{
    assert(pixel  != nullptr);
    assert(sphere != nullptr);

    int x_diff = abs(pixel->get_x() - sphere->get_x_origin());
    int y_diff = abs(pixel->get_y() - sphere->get_y_origin());

    return (get_square(x_diff) + 
            get_square(y_diff))  
          < get_square(sphere->get_radius()) - DOUBLE_COMPARISON_PRECISION ?
            true : false;
}

float get_sphere_point_z_coord(Sphere *sphere, float x_pos, float y_pos)
{
    assert(sphere != nullptr);
    
    float z_square = get_square(sphere->get_radius()) -  get_square(x_pos) - get_square(y_pos);

    return z_square > DOUBLE_COMPARISON_PRECISION ? sqrtf(z_square) : 0;
}

void dump_vector(Vector3d v)
{
    std::cout << "vector_x: " << v.get_x() << " vector_y: " << v.get_y() << " vector_z: " << v.get_z() << std::endl;
}


bool ray_intersects_sphere(const Sphere *sphere,         float *distance,
                           const Vector3d &origin, const Vector3d &direction)
{
    assert(sphere   != nullptr);
    assert(distance != nullptr);
    
    Vector3d origin_to_center = sphere->get_origin_ptr() - origin;
    //if ((x_pos == 250) && (y_pos == 250))
    //std::cout << "origin_to_center: " << origin_to_center.get_x() << " " << origin_to_center.get_y() << " " << origin_to_center.get_z() << std::endl;
    float direction_projection = origin_to_center * direction;
    float leg_square =  origin_to_center * origin_to_center - get_square(direction_projection);
    //if ((x_pos == 250) && (y_pos == 250))
    {
    //    std::cout << "leg_square: " << leg_square << std::endl;
    }
    
    float radius_square = get_square(sphere->get_radius());
    if (leg_square >= radius_square)
    {
        return false;
    }

    // std::cout << "radius_square: " << radius_square << " leg_square: " << leg_square << std::endl;
    assert(radius_square - leg_square >= 0);

    float radius_leftover = sqrtf(radius_square - leg_square);
    *distance = direction_projection - radius_leftover;

    if (*distance < 0)
    {
        *distance = direction_projection + radius_leftover;
    }
    if (*distance < 0)
    {
        return false;
    }

    return true;
}
