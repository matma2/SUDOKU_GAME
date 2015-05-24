#include "SudokuField.hpp"

using namespace genv;

SudokuField::SudokuField(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label, bool editable_, Sudoku* sudoku_, const int &i_, const int &j_) : TextBox(x_,y_,size_x,size_y,label)
{
    sudoku = sudoku_;
    editable = editable_;
    i = i_;
    j = j_;
    isWrong = false;
}

void SudokuField::draw()
{
    if(editable)
    {
        if(isWrong)
        {
            gout << move_to(x,y) << color(255,0,0) << box(s_x,s_y) << move_to(x+s_x/2-gout.twidth(init_text)/2, y+s_y/2+gout.cdescent()) << color(255,255,255) << text(init_text);
        }

        else
        {
            gout << move_to(x,y) << color(255,255,255) << box(s_x,s_y) << move_to(x+s_x/2-gout.twidth(init_text)/2, y+s_y/2+gout.cdescent()) << color(255,100,100) << text(init_text);
        }
    }
    else
    {
        gout << move_to(x,y) << color(150,150,150) << box(s_x,s_y) << move_to(x+s_x/2-gout.twidth(init_text)/2, y+s_y/2+gout.cdescent()) << color(0,0,0) << text(init_text);
    }
}

void SudokuField::draw_focus_line()
{
    if(editable)
    {
        for(unsigned int i=0; i<10; i++)
        {
            gout << color(25*i,25*i,25*i) << move_to(x+i,y+i) << line_to(x+s_x-i,y+i) << line_to(x+s_x-i, y+s_y-i)
            << line_to(x+i,y+s_y-i) << line_to(x+i,y+i);
        }
    }
}

void SudokuField::event_handle(event ev)
{
    if(editable)
    {
        if(ev.type == ev_key)
        {
            char actual_value;
            std::stringstream str;
            str << init_text;
            str >> actual_value;
            if(ev.keycode >= 49 && ev.keycode <= 57 && ev.keycode != actual_value)
            {
                if(init_text.size()!=0) init_text.erase();
                init_text.push_back(ev.keycode);
                std::stringstream ss;
                ss << init_text;
                int temp;
                ss >> temp;
                sudoku->set_act_table(i,j,temp);
            }
        }
    }
}

bool SudokuField::get_editable() const
{
    return editable;
}

void SudokuField::set_editable(bool editable)
{
    this->editable = editable;
}

void SudokuField::wrong_field(bool isWrong)
{
    this->isWrong = isWrong;
}
