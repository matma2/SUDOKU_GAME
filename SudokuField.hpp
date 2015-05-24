#ifndef SUDOKUFIELD_HPP_INCLUDED
#define SUDOKUFIELD_HPP_INCLUDED

#include "TextBox.hpp"
#include "Sudoku.hpp"
#include <sstream>

class Sudoku;

class SudokuField : public TextBox
{
private:
    bool editable;
    Sudoku* sudoku;
    int i, j;
    bool isWrong;
public:
    SudokuField(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label, bool editable_, Sudoku* sudoku_, const int &i_, const int &j_);
    void draw();
    void event_handle(genv::event ev);
    void draw_focus_line();
    bool get_editable() const;
    void set_editable(bool editable);
    void wrong_field(bool isWrong);
};

#endif // SUDOKUFIELD_HPP_INCLUDED
