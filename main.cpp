#include "displaywindow.hpp"
#include "color.hpp"
#include "colorlibrary.hpp"
#include "materiallibrary.hpp"


int main()
{
    int window_width  = 800;
    int window_height = 450;
    DisplayWindow window{window_width, window_height, "Raytracing"};

    Camera camera{Vector3d{0,  10,   0},
                  Vector3d{0,  10, -10},
                  Vector3d{ 0 , 1,   0},
                  90, 
                  (float) window_width / window_height};

    SphereArr spheres{};
    Sphere front_plane {   0.0,    0.0, -1000.0,  980.0, MATTE, LIME,    false};
    Sphere left_plane  {-990.0,    0.0,     0.0,  970.0, MATTE, GREY,    false};
    Sphere right_plane { 990.0,    0.0,     0.0,  970.0, MATTE, ORANGE,  false};
    Sphere bottom_plane{   0.0, -990.0,     0.0,  990.0, MATTE, CRIMSON, false};
    Sphere top_plane   {   0.0, 1000.0,     0.0,  980.0, MATTE, YELLOW,  false};
    //Sphere back_plane  {   0.0,    0.0,  1000.0,  980.0, MATTE, TOMATO,  false};
    spheres.add(&front_plane);
    spheres.add(&left_plane);
    spheres.add(&right_plane);
    spheres.add(&bottom_plane);
    spheres.add(&top_plane);
    //spheres.add(&back_plane);
    Sphere ball1{ -1.0,  10.0,  -5.0, 1.0, MIRROR, GREEN,      false};
    Sphere ball2{  5.0,  12.0,  -7.0, 3.0, MIRROR, YELLOW,     false};
    Sphere ball3{-10.0,   5.0, -17.0, 5.0, MIRROR, TOMATO,     false};
    Sphere ball4{  7.0,   3.0, -13.0, 3.0, MIRROR, MAGENTA,    false};
    Sphere ball5{-13.0,   2.0, -11.5, 2.0, MIRROR, LIGHT_BLUE, false};
    Sphere ball6{  0.0,   1.0, -11.0, 1.0, MATTE,  ORANGE,     false};
    Sphere ball7{ 13.0,   2.0, -14.0, 2.0, TRANSPARENT, SEA_GREEN, false};
    spheres.add(&ball1);
    spheres.add(&ball2);
    spheres.add(&ball3);
    spheres.add(&ball4);
    spheres.add(&ball5);
    spheres.add(&ball6);
    spheres.add(&ball7);

    Sphere light1{-1.0,  3.0, -17.0,  3.0, LIGHT_SOURCE, WHITE, true};
    Sphere light2{12.0,  4.0, -17.0,  4.0, LIGHT_SOURCE, WHITE, true};
    Sphere light3{-7.0, 13.0, -13.0,  3.0, LIGHT_SOURCE, WHITE, true};
    Sphere giant_sun{0.0,  0.0,  1000.0, 970.0, LIGHT_SOURCE, WHITE, true};
    spheres.add(&light1);
    spheres.add(&light2);
    spheres.add(&light3);
    spheres.add(&giant_sun);

    Image scene{};
    Color image_background_color{WHITE};
    scene.create(window_width, window_height, image_background_color);

    window.open();
    for (; window.is_open(); )
    {
        window.handle_events();

        scene.render(&window, camera, spheres);
    }
    
    return 0;
}