#include "displaywindow.hpp"


DisplayWindow::DisplayWindow(int window_width, 
                             int window_height, 
                             const char *window_name)
  : window_width_ (window_width),
    window_height_(window_height)
{
    assert(window_name != nullptr);

    strncpy(window_name_, window_name, MAX_WINDOW_NAME_LENGTH);
}

void DisplayWindow::create(int window_width,
                           int window_height,
                           const char *window_name)
{
    assert(window_name != nullptr);

    DisplayWindow(window_width, window_height, window_name);

    window_.create(sf::VideoMode(window_width, window_height), window_name);
}

void DisplayWindow::open()
{
    window_.create(sf::VideoMode(window_width_, window_height_), window_name_);
}

bool DisplayWindow::is_open()
{
    return window_.isOpen();
}

void DisplayWindow::close()
{
    window_.close();
}

bool DisplayWindow::poll_event(Event *event)
{
    assert(event != nullptr);

    return window_.pollEvent(event->get_event_ref());
}

void DisplayWindow::handle_events()
{
    Event event;
    while (poll_event(&event))
    {
        switch (event.get_event_type())
        {
            case sf::Event::Closed:
            {
                event_close(this);

                break;
            }
            
            default:
            {
                break;
            }
        }
    }
}

void DisplayWindow::clear()
{
    window_.clear();
}

void DisplayWindow::display()
{
    window_.display();
}

void DisplayWindow::draw_image(const Image &image, const Point3d &origin)
{
    sf::RectangleShape picture(sf::Vector2f(image.get_width(), image.get_height()));
    picture.setPosition(sf::Vector2f(origin.get_x(), origin.get_y()));

    sf::Texture picture_texture{};
    picture_texture.loadFromImage(image.get_image_ref());
    picture.setTexture(&picture_texture);

    window_.draw(picture);
}


void event_close(DisplayWindow *window)
{
    assert(window != nullptr);

    window->close();
}