#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "Widget.hpp"

class TextBox : public Widget
{
protected:
    std::string init_text;
    int time;
    bool cursor;
public:
    TextBox(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &init_text_);
    virtual void draw();
    virtual void event_handle(genv::event ev);
    virtual void draw_focus_line();
    std::string get_init_text() const;
    void clear_textbox();
    void set_init_text(const std::string &init_text_);
};


#endif // TEXTBOX_HPP_INCLUDED
