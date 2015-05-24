#include "TextBox.hpp"

using namespace std;
using namespace genv;

TextBox :: TextBox(const int &x_, const int &y_, const int &size_x, const int &size_y, const string &init_text_):Widget(x_, y_, size_x, size_y)
{
    init_text = init_text_;
    focusable = true;
    cursor = false;
    time = 0;
}

void TextBox :: draw()
{
    gout << move_to(x,y) << color(150, 150, 150) << box(s_x, s_y)
    << move_to(x,y) << color(255,0,0) << line_to(x+s_x, y) << line_to(x+s_x, y+s_y) << line_to(x, y+s_y)
    << line_to(x,y) << move_to(x+2, y+s_y/2+gout.cdescent()) << color(0,0,0) << text(init_text);
}

void TextBox :: event_handle(event ev)
{
    if(ev.type == ev_key)
    {
        if(ev.keycode != key_backspace && ev.keycode != key_enter && ev.keycode != key_tab && ev.keycode >= 0 && ev.keycode <= 255 && gout.twidth(init_text)+10 < s_x)
        {
            init_text.push_back(ev.keycode);
        }

        if(ev.keycode == key_backspace && init_text.size() != 0)
        {
            init_text.pop_back();
        }
    }
    if(ev.type == ev_timer)
    {
        time = ev.time;
        if(time%1000 >= 0 && time%1000 <= 500) cursor = true;
        else cursor = false;
    }
}

void TextBox :: draw_focus_line()
{
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

        gout << move_to(x,y) << color(255, 255, 255) << box(s_x, s_y)
        << move_to(x,y) << color(255,0,0) << line_to(x+s_x, y) << line_to(x+s_x, y+s_y) << line_to(x, y+s_y)
        << line_to(x,y) << move_to(x+2, y+s_y/2+gout.cdescent()) << color(0,0,0) << text(init_text);

        if(cursor)
        {
            gout << color(0,0,0) << move_to(x+2+gout.twidth(init_text), y+s_y/2+gout.cdescent()+3)
            << line_to(x+2+gout.twidth(init_text), y+s_y/2-gout.cascent()+5);
        }
    }
}

string TextBox :: get_init_text() const
{
    return init_text;
}

void TextBox :: clear_textbox()
{
    init_text.clear();
}

void TextBox :: set_init_text(const std::string &init_text_)
{
    init_text = init_text_;
}
