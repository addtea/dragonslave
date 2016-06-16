#pragma once

namespace dragonslave {


class Window
{
public:
    Window() { }
    virtual ~Window() { }

    void on_resize(int width, int height) { }
};


}
