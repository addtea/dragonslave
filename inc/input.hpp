#pragma once

namespace dragonslave {


class Input
{
public:
    Input() { }
    virtual ~Input() { }

    void on_char(unsigned int codepoint) { }
    void on_key(int key, int scancode, int action, int mods) { }

    void on_cursor_pos(double x, double y) { }
    void on_mouse_button(int button, int action, int mods) { }
    void on_scroll(double dx, double dy) { }
};


}
