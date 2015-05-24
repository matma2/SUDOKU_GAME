#ifndef PUSHBUTTON_HPP_INCLUDED
#define PUSHBUTTON_HPP_INCLUDED

#include "Widget.hpp"

class PushButton : public Widget
{
protected:
    int act_color;
    bool pushed;
    std::string label;
public:
    PushButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_);
    void draw();
    virtual void event_handle(genv::event ev) = 0;
    void pushed_down(genv::event ev);
};

#endif // PUSHBUTTON_HPP_INCLUDED
