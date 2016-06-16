#include "app.hpp"

namespace dragonslave {


App::App() { } 

App::~App() { }

void App::init(const AppConfig& config)
{
    if (!glfwInit()) {
        throw AppInitError("Failed to initialize GLFW.");
    }

    int width = config.width;
    int height = config.height;

    GLFWmonitor* monitor = nullptr;

    if (config.fullscreen) {
        monitor = glfwGetPrimaryMonitor();
    }

    glfwWindowHint(GLFW_VISIBLE, config.shown ? 1 : 0);
    glfwWindowHint(GLFW_DECORATED, !config.borderless ? 1 : 0);
    glfwWindowHint(GLFW_RESIZABLE, config.resizable ? 1 : 0);
    glfwWindowHint(GLFW_DOUBLEBUFFER, config.double_buffered ? 1 : 0);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfw_window_ = glfwCreateWindow(width, height, config.title.c_str(), monitor, nullptr);

    if (!glfw_window_) {
        throw AppInitError("Failed to create GLFW window.");
    }

    glfwMakeContextCurrent(glfw_window_);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw AppInitError("Failed to initialize GLEW.");
    }
    glGetError();

    glfwSetWindowUserPointer(glfw_window_, this);

    glfwSetCharCallback(glfw_window_, App::handle_char);
    glfwSetKeyCallback(glfw_window_, App::handle_key);
    glfwSetCursorPosCallback(glfw_window_, App::handle_cursor_pos);
    glfwSetMouseButtonCallback(glfw_window_, App::handle_mouse_button);
    glfwSetScrollCallback(glfw_window_, App::handle_scroll);
    glfwSetFramebufferSizeCallback(glfw_window_, App::handle_framebuffer_size);

    glfwGetFramebufferSize(glfw_window_, &width, &height);
    window_.on_resize(width, height);
}

void App::term()
{
    glfwTerminate();
}

void App::handle_char(GLFWwindow* window, unsigned int codepoint) 
{ 
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->input_.on_char(codepoint);
}

void App::handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) 
{ 
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->input_.on_key(key, scancode, action, mods);
}

void App::handle_cursor_pos(GLFWwindow* window, double x, double y) 
{ 
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->input_.on_cursor_pos(x, y);
}

void App::handle_mouse_button(GLFWwindow* window, int button, int action, int mods) 
{ 
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->input_.on_mouse_button(button, action, mods);
}

void App::handle_scroll(GLFWwindow* window, double dx, double dy) 
{ 
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->input_.on_scroll(dx, dy);
}

void App::handle_framebuffer_size(GLFWwindow* window, int width, int height) 
{ 
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->window_.on_resize(width, height);
}


}
