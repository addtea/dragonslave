#pragma once

namespace dragonslave {


class InputEventHandler;


class InputEvent
{
public:
    virtual ~InputEvent() { }

    virtual void dispatch(InputEventHandler* handler) const = 0;
};


class KeyboardInputEvent : public InputEvent
{
public:
    int key;
    int scancode;
    int action;
    int mods;

    KeyboardInputEvent(int key, int scancode, int action, int mods)
      : key (key)
      , scancode (scancode)
      , action (action)
      , mods (mods)
    { }

    void dispatch(InputEventHandler* handler) const override;
};


class MouseButtonInputEvent : public InputEvent
{
public:
    double x;
    double y; 
    int button;
    int action;
    int mods;

    MouseButtonInputEvent(double x, double y, int button, int action, int mods)
      : x (x)
      , y (y)
      , button (button)
      , action (action)
      , mods (mods)
    { }

    void dispatch(InputEventHandler* handler) const override;
};



class MouseMotionInputEvent : public InputEvent
{
public:
    double x;
    double y;
    double dx;
    double dy;

    MouseMotionInputEvent(double x, double y, double dx, double dy)
      : x (x)
      , y (y)
      , dx (dx)
      , dy (dy)
    { }

    void dispatch(InputEventHandler* handler) const override;
};


class MouseScrollInputEvent : public InputEvent
{
public:
    double x;
    double y; 
    double scroll_x;
    double scroll_y;

    MouseScrollInputEvent(double x, double y, double scroll_x, double scroll_y)
      : x (x)
      , y (y)
      , scroll_x (scroll_x)
      , scroll_y (scroll_y)
    { }

    void dispatch(InputEventHandler* handler) const override;
};


class InputEventHandler
{
public:
    virtual ~InputEventHandler() { }

    virtual void handle(const InputEvent& event);

    virtual void handle(const KeyboardInputEvent& event) { }
    virtual void handle(const MouseButtonInputEvent& event) { }
    virtual void handle(const MouseMotionInputEvent& event) { }
    virtual void handle(const MouseScrollInputEvent& event) { }
};


}
