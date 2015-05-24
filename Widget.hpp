#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"

class Widget
{
protected:
    int x, y;   /// pozíció
    int s_x, s_y;   /// méret
    bool focusable;
public:
    Widget(const int &x_, const int &y_);
    Widget(const int &x_, const int &y_, const int &size_x, const int &size_y);
    virtual void draw() = 0;
    virtual void event_handle(genv::event ev);
    virtual bool selected(const int &pos_x, const int &pos_y);
    bool get_focusable() const;
    virtual void draw_focus_line();
    int get_size_x() const;
};

#endif // WIDGET_HPP_INCLUDED
