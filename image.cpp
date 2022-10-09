#include "image.hpp"


void Image::create(int width, int height, const Color &color)
{
    width_  = width;
    height_ = height;

    image_.create(width, height, color.get_color_ref());
}

void Image::set_pixel(int x_coord, int y_coord, const Color &color)
{
    image_.setPixel(x_coord, (height_ - 1) - y_coord, color.get_color_ref());
}

void Image::render(DisplayWindow *window, const Camera &camera, const SphereArr &spheres)
{
    for (int y_pos = height_ - 1; y_pos >= 0; --y_pos)
    {
        for (int x_pos = 0; x_pos < width_; ++x_pos)
        {
            Vector3d congregated_color{0, 0, 0};
            for (int pixel_processing_num = 0; pixel_processing_num < ANTI_ALIASING_PROCESSING_PER_PIXEL; ++pixel_processing_num)
            {
                float x_viewport_pos = (get_random_fractional_float() + x_pos) / (width_  - 1);
                float y_viewport_pos = (get_random_fractional_float() + y_pos) / (height_ - 1);

                congregated_color += color_to_vector(get_ray_color(camera.get_ray(x_viewport_pos, y_viewport_pos), 
                                                     spheres, 
                                                     MAX_RAY_COLOR_RECURSION_DEPTH));
            }

            Color result_color = vector_to_color(congregated_color / ANTI_ALIASING_PROCESSING_PER_PIXEL);

            set_pixel(x_pos, y_pos, result_color.gamma_correction(GAMMA_CORRECTION_COEF));

            window->draw_image(*this, Point3d{0, 0});

            window->display();
        }
    }
}