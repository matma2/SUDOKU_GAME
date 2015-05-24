#ifndef STATICTEXT_HPP_INCLUDED
#define STATICTEXT_HPP_INCLUDED

#include "Widget.hpp"

class StaticText : public Widget
{
protected:
    std::string s_text;
public:
    StaticText(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label);
    virtual void draw();
    bool selected(const int &pos_x, const int &pos_y) const;
    void set_text(const std::string &str);
    std::string get_text() const;
};

#endif // STATICTEXT_HPP_INCLUDED
