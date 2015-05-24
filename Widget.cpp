#include "Widget.hpp"

using namespace genv;

Widget :: Widget(const int &x_, const int &y_):x(x_), y(y_)
{
    focusable = false;
}
Widget :: Widget(const int &x_, const int &y_, const int &size_x, const int &size_y):x(x_), y(y_), s_x(size_x), s_y(size_y)
{
    focusable = false;
}

void Widget :: event_handle(event ev) {}
bool Widget :: selected(const int &pos_x, const int &pos_y)
{
    if(pos_x>=x && pos_x<=x+s_x && pos_y>=y && pos_y<=y+s_y) return true;
    return false;
}

bool Widget :: get_focusable() const
{
    return focusable;
}

void Widget :: draw_focus_line()
{
    /// objektum kijelölése
    if(focusable)
    {
        for(int i = 0; i<=s_y+4; i+=2)
        {
            gout << move_to(x-2, y-2+i) << color(255,255,255) << dot;
        }
        for(int i = 0; i<=s_x+4; i+=2)
        {
            gout << move_to(x-2+i, y+s_y+2) << color(255,255,255) << dot;
        }
        for(int i = 0; i<=s_x+4; i+=2)
        {
            gout << move_to(x-2+i, y-2) << color(255,255,255) << dot;
        }
        for(int i = 0; i<=s_y+4; i+=2)
        {
            gout << move_to(x+s_x+2, y-2+i) << color(255,255,255) << dot;
        }
    }
}

int Widget :: get_size_x() const
{
    return s_x;
}
