#pragma once

namespace dragonslave {


enum class InputEventType {
    KEYBOARD,
    MOUSE_MOTION,
    MOUSE_BUTTON,
    MOUSE_SCROLL,
};


class InputEvent
{
public:
    InputEventType type;

    InputEvent(InputEventType type)
      : type (type)
    { }

    virtual ~InputEvent() { }
};


class KeyboardInputEvent : public InputEvent
{
public:
    int key;
    int scancode;
    int action;
    int mods;

    KeyboardInputEvent(int key, int scancode, int action, int mods)
      : InputEvent (InputEventType::KEYBOARD)
      , key (key)
      , scancode (scancode)
      , action (action)
      , mods (mods)
    { }
};


class MouseMotionInputEvent : public InputEvent
{
public:
    double x;
    double y;
    double dx;
    double dy;

    MouseMotionInputEvent(double x, double y, double dx, double dy)
      : InputEvent (InputEventType::MOUSE_MOTION)
      , x (x)
      , y (y)
      , dx (dx)
      , dy (dy)
    { }
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
      : InputEvent (InputEventType::MOUSE_BUTTON)
      , x (x)
      , y (y)
      , button (button)
      , action (action)
      , mods (mods)
    { }
};


class MouseScrollInputEvent : public InputEvent
{
public:
    double x;
    double y; 
    double scroll_x;
    double scroll_y;

    MouseScrollInputEvent(double x, double y, double scroll_x, double scroll_y)
      : InputEvent (InputEventType::MOUSE_BUTTON)
      , x (x)
      , y (y)
      , scroll_x (scroll_x)
      , scroll_y (scroll_y)
    { }
};


}
