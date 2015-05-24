#include "PushButton.hpp"
using namespace genv;

PushButton :: PushButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_) : Widget(x_, y_, size_x, size_y)
{
    label = label_;
    focusable = true;
    pushed = false;
    act_color = 70;
}

void PushButton :: draw()
{
    gout << move_to(x,y) << color(act_color,act_color,act_color) << box(s_x, s_y) << move_to(x+s_x/2-gout.twidth(label)/2, y+s_y/2+gout.cascent()/2)
    << color(0,0,0) << text(label);
}

void PushButton :: pushed_down(event ev)
{
        if(ev.type == ev_mouse && ev.button == btn_left && ev.pos_x >= x && ev.pos_x <= x+s_x && ev.pos_y >= y && ev.pos_y <= y+s_y)
        {
            pushed = true;
            act_color = 150;
        }
        else pushed = false;
        if(ev.button == -btn_left)
        {
            act_color = 70;
        }
}
