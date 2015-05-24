#include "StaticText.hpp"

using namespace std;
using namespace genv;

StaticText :: StaticText(const int &x_, const int &y_, const int &size_x, const int &size_y, const string &label): Widget(x_, y_, size_x, size_y)
    {
        s_text = label;
    }
void StaticText :: draw()
    {
        gout << move_to(x,y)  << color(0,0,0) << box(s_x, s_y) << color(255,255,255) << move_to(x+5, y+s_y/2) << text(s_text);
    }
bool StaticText :: selected(const int &pos_x, const int &pos_y) const
{
    return false;
}

void StaticText :: set_text(const string &str)
{
    s_text = str;
}

std::string StaticText :: get_text() const
{
    return s_text;
}
