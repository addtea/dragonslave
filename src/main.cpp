#include <iostream>

#include "app.hpp"
#include "error.hpp"
#include "event_listener.hpp"
#include "input.hpp"
#include "input_queue.hpp"
#include "window.hpp"

struct EchoWindowSize : public dragonslave::EventListener<dragonslave::WindowResizeEvent>
{
    void handle(const dragonslave::WindowResizeEvent& ev)
    {
        std::cout << ev.width << " " << ev.height << std::endl;
    }
};


int main(int argc, char** argv) 
{
    try {
        dragonslave::App app;
        dragonslave::AppConfig app_config;
        app_config.title = "Lina is the best!";
        app_config.resizable = true;
        app.init(app_config);

        EchoWindowSize ews;

        app.get_window().get_resize_target().add_event_listener(
            &ews);

        bool is_running = true;
        dragonslave::InputQueue& input_queue = app.get_input().get_queue();
        while (is_running) {
            app.poll();
            while (input_queue.has_next_event()) {
                dragonslave::InputEvent ev = input_queue.pop_next_event(); 
                if (ev.type == dragonslave::InputType::KEYBOARD) {
                    if (ev.keyboard.action == GLFW_PRESS &&
                            ev.keyboard.key == GLFW_KEY_ESCAPE) {
                        is_running = false;
                    }
                }
            }
        }

        app.term();

    } catch (const dragonslave::FatalError& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
