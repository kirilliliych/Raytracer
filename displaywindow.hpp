#ifndef DISPLAYWINDOW_HPP
#define DISPLAYWINDOW_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "event.hpp"
#include "image.hpp"
#include "utilities.hpp"


const size_t MAX_WINDOW_NAME_LENGTH             = 31;
const size_t STANDARD_WINDOW_WIDTH              = 800;
const size_t STANDARD_WINDOW_HEIGHT             = 600;


static const char *STANDARD_WINDOW_NAME = "SFML Window";


class DisplayWindow
{
private:

    int window_width_  = 0;
    int window_height_ = 0;

    char window_name_[MAX_WINDOW_NAME_LENGTH] = {};

    sf::RenderWindow window_{};
    
public:

    DisplayWindow(){};

    DisplayWindow(int window_width  = STANDARD_WINDOW_WIDTH, 
                  int window_height = STANDARD_WINDOW_HEIGHT, 
                  const char *window_name = STANDARD_WINDOW_NAME);
    
    void create(int window_width  = STANDARD_WINDOW_WIDTH,
                int window_height = STANDARD_WINDOW_HEIGHT,
                const char *window_name = STANDARD_WINDOW_NAME);

    void open();

    bool is_open();

    bool poll_event(Event *event);

    void close();

    void handle_events();
    
    void handle_draw_requests();

    void clear();

    void display();

    void draw_image(const Image &image, const Point3d &origin);
   
    int get_width() const
    {
        return window_width_;
    }
    int get_height() const
    {
        return window_height_;  
    }
};

void event_close(DisplayWindow *window);

#endif