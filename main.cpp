#include <ctime>
#include "displaywindow.hpp"
#include "vector3d.hpp"
#include "lightsource.hpp"
#include "color.hpp"


int main()
{
    unsigned window_width  = 800;
    unsigned window_height = 800;
    DisplayWindow window{window_width, window_height, "Raytracing"};

    Sphere ball1{200, 200, -200, 150, LIME_GLASS};
    Sphere ball2{600, 600, -300, 100, TOMATO_RUBBER};
    Sphere ball3{300, 700, -100,  50, TOMATO_RUBBER};
    Sphere ball4{400, 400,    0,  50, LIME_GLASS};
    //Sphere ball1{100, 100, 0, 100, LIME_GLASS};
    //Sphere ball2{250, 250, 200, 25, TOMATO_RUBBER};
    SphereArr spheres{};
    spheres.add(&ball1);
    spheres.add(&ball2);
    spheres.add(&ball3);
    spheres.add(&ball4);

    //Vector3d light_source1_pos{400, 400, 400};
    Vector3d light_source1_pos{0,   800, 300};
    Vector3d light_source2_pos{800, 300, 300};
    Vector3d light_source3_pos{800, 800, 500};
    Color light_source1_color{WHITE};
    Color light_source2_color{YELLOW};
    Color light_source3_color{WHITE};
    LightSource light_source1{light_source1_pos, light_source1_color, 1};
    LightSource light_source2{light_source2_pos, light_source2_color, 1};
    LightSource light_source3{light_source3_pos, light_source3_color, 1};

    LightSourceArr lights{};
    lights.add(&light_source1);
    //lights.add(&light_source2);
    //lights.add(&light_source3);

    Point3d camera_position{400, 400, 600};

    window.open();
    while (window.is_open())
    {
        Image scene{};
        Color image_background_color{BLACK};
        scene.create(window_width, window_height, &image_background_color);

        window.handle_events();

        window.clear();

        scene.render(&spheres, &lights, &camera_position);

        Pixel3d sphere_picture_origin{0, 0};
        window.draw_image(&scene, &sphere_picture_origin);

        window.display();
    }
    
    return 0;
}