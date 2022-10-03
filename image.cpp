#include "image.hpp"
#include "utilities.hpp"


void Image::create(unsigned width, unsigned height, Color *color)
{
    assert(color != nullptr);

    width_  = width;
    height_ = height;

    image_.create(width, height, color->get_color_ref());
}

void Image::set_pixel(unsigned x_coord, unsigned y_coord, Color *color)
{
    assert(color != nullptr);

    image_.setPixel(x_coord, y_coord, color->get_color_ref());
}

void Image::render(const SphereArr *spheres, const LightSourceArr *lights, const Point3d *camera)
{
    assert(spheres != nullptr);
    assert(lights  != nullptr);
    assert(camera  != nullptr);

    int quantity = 0;
    for (unsigned x_pos = 0; x_pos < get_width(); ++x_pos)
    {
        for (unsigned y_pos = 0; y_pos < get_height(); ++y_pos)
        {
            Point3d cur_pixel{x_pos, y_pos, 0};
            Vector3d camera_vector{camera};

            Vector3d direction{camera, &cur_pixel};
            normalize_vector(&direction);
            Color pixel_color = cast_rays(camera_vector, direction, spheres, lights, 0);
            
            set_pixel(x_pos, y_pos, &pixel_color);
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// scene class
Color cast_rays(const Vector3d &origin, const Vector3d &direction, const SphereArr      *spheres,
                                                                   const LightSourceArr *lights,
                                                                   int depth)
{
    assert(lights  != nullptr);
    assert(spheres != nullptr);

    Color result_color{BLACK};
    Color congregated_light_color{BLACK};
    Color congregated_light_specular{BLACK};
    
    size_t closest_sphere_index = spheres->size_;
    float closest_camera_sphere_intersection_distance = FLT_MAX;
    float camera_sphere_intersection_distance         = FLT_MAX;
///////////////////////////////////////////////////////////////////////////////////
    for (size_t sphere_index = 0; sphere_index < spheres->size_; ++sphere_index)                            // decides which sphere is closer to camera
    {
        if ((ray_intersects_sphere(spheres->array_[sphere_index], 
                                   &camera_sphere_intersection_distance,
                                   origin, direction))                               &&                     // ray class with origin & direction
            (closest_camera_sphere_intersection_distance >                                                  // do scene_intersect function
                     camera_sphere_intersection_distance))
        {
            closest_camera_sphere_intersection_distance = camera_sphere_intersection_distance;
            closest_sphere_index = sphere_index;
        } 
    }
///////////////////////////////////////////////////////////////////////////////////
    Color reflect_color{BLACK};
    if ((depth >= DEPTH_BORDER) || (closest_sphere_index == spheres->size_))
    {
        result_color.set_color(GREY);

        return result_color;
    }//////////////////////////////////////////////////////////////////////////////
    else
    {   
        const Material sphere_material = spheres->array_[closest_sphere_index]->get_material();
        const Color    sphere_color    = sphere_material.color_;

        Vector3d intersection_point_radius_vector = origin + direction * closest_camera_sphere_intersection_distance;
        Vector3d normal_vector = intersection_point_radius_vector - spheres->array_[closest_sphere_index]->get_origin();
        normalize_vector(&normal_vector);

        Vector3d reflect_direction = get_reflected(-direction, normal_vector);
        normalize_vector(&reflect_direction);
        Vector3d reflect_origin = intersection_point_radius_vector;
        reflect_origin += reflect_direction * normal_vector > 0 ? normal_vector : -normal_vector;

        reflect_color = cast_rays(reflect_origin, reflect_direction, spheres, lights, depth + 1);          // recursive call causing reflection
//////////////////////////////////////////////////////////////////////////////////////
        for (size_t light_index = 0; light_index < lights->size_; ++light_index)
        {
            LightSource *cur_light = lights->array_[light_index];
            Vector3d light_ray_direction = cur_light->position_ - intersection_point_radius_vector;
            normalize_vector(&light_ray_direction);

            bool with_shadow = false;
///////////////////////////////////////////////////////////////////////////////////////
            for (size_t sphere_index = 0; sphere_index < spheres->size_; ++sphere_index)                    // checking if there should be shadow
            {
                if (sphere_index == closest_sphere_index)                                                   // intersection with sphere being drawn is obvious 
                {
                    continue;
                }

                float light_barrier_distance   = FLT_MAX;
                float light_cur_point_distance = FLT_MAX;
                if (ray_intersects_sphere(spheres->array_[sphere_index], &light_barrier_distance,
                                          cur_light->position_, -light_ray_direction)                           &&
                    ray_intersects_sphere(spheres->array_[closest_sphere_index], &light_cur_point_distance,
                                          cur_light->position_, -light_ray_direction)                           &&
                    (light_barrier_distance < light_cur_point_distance))
                {
                    with_shadow = true;

                    break;
                } 
            }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (!with_shadow)                                                                               // light contribute to pixel color if no shadow
            {
                float Lambert_cos = calc_Lambert_cos(&light_ray_direction, &normal_vector);
                congregated_light_color += sphere_color * Lambert_cos * sphere_material.albedo_.get_x();

                Vector3d reflected_light_ray_direction = get_reflected(light_ray_direction, normal_vector);
                normalize_vector(&reflected_light_ray_direction);
                float specular_coef = calc_specular(&reflected_light_ray_direction, &direction, 
                                                    sphere_material.specular_pow_);
                congregated_light_specular += cur_light->color_ * cur_light->intensity_ *
                                                specular_coef * sphere_material.albedo_.get_y();
            }
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Color ambient = sphere_color * ambient_light * sphere_material.albedo_.get_z();

        result_color += congregated_light_color + congregated_light_specular + ambient + reflect_color * 0.3;
    }

    return result_color;
}