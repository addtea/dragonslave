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
        app.initiate(app_config);

        EchoWindowSize ews;

        app.window.get_resize_target().add_event_listener(
            &ews);

        dragonslave::Model& lina_model = app.asset.model.load_named_model("Lina", "assets/models/Lina/lina.dae");

        bool is_running = true;
        dragonslave::InputQueue& input_queue = app.input.get_queue();
        while (is_running) {
            app.poll();
            while (input_queue.has_events()) {
                const dragonslave::InputEvent* ev = input_queue.next_event(); 
                if (ev->type == dragonslave::InputEventType::KEYBOARD) {
                    const dragonslave::KeyboardInputEvent* kev =
                        static_cast<const dragonslave::KeyboardInputEvent*>(ev);
                    if (kev->action == GLFW_PRESS &&
                            kev->key == GLFW_KEY_ESCAPE) {
                        is_running = false;
                    }
                }
                input_queue.pop_event();
            }
        }

        app.terminate();

    } catch (const dragonslave::FatalError& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
