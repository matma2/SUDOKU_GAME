#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include "MyApplication.hpp"
#include "SudokuField.hpp"
#include "StaticText.hpp"
#include <sstream>

class SolveButton;
class CheckButton;
class RestartButton;
class GenerateButton;
class ExitButton;
class SudokuField;

class Sudoku : public MyApplication
{
private:
    /// játék logikáját képezõ eszközök
    int act_table[9][9];
    int solved_table[9][9];
    int original_table[9][9];

    std::vector<std::string> sudoku_tables;

    /// grafikus felület komponensei
    // gombok:
    SolveButton* sb;
    CheckButton* cb;
    RestartButton* rb;
    GenerateButton* gb;
    ExitButton* eb;

    // szövegdobozok:

    StaticText* st1;
    StaticText* st2;

    // sudoku mezõk widgetjei
    SudokuField* field[9][9];

    /// függvények
    void data_read(const std::string &filename);
    bool sudoku_solve();
    /// sudoku megoldásához függvények
    bool findUnassignedLocation(int &row, int &col);
    bool usedInRow(const int grid[9][9], const int &row, const int &num) const;
    bool usedInCol(const int grid[9][9], const int &col, const int &num) const;
    bool usedInBox(const int grid[9][9], const int &boxStartRow, const int &boxStartCol, const int &num) const;
    bool isSafe(const int grid[9][9], const int &row, const int &col, const int &num) const;

public:
    Sudoku();
    void solve();
    void restart();
    void check();
    void generate();
    void set_act_table(const int &i, const int &j, const int &num);
};

class SolveButton : public PushButton
{
private:
    Sudoku* sudoku;
public:
    SolveButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_, Sudoku* sudoku_) : PushButton(x_, y_, size_x, size_y, label_)
    {
        sudoku = sudoku_;
    }

    void event_handle(genv::event ev)
    {
        pushed_down(ev);
        if(pushed) sudoku->solve();
    }
};

class CheckButton : public PushButton
{
private:
    Sudoku* sudoku;
public:
    CheckButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_, Sudoku* sudoku_) : PushButton(x_, y_, size_x, size_y, label_)
    {
        sudoku = sudoku_;
    }

    void event_handle(genv::event ev)
    {
        pushed_down(ev);
        if(pushed) sudoku->check();
    }

};

class RestartButton : public PushButton
{
private:
    Sudoku* sudoku;
public:
    RestartButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_, Sudoku* sudoku_) : PushButton(x_, y_, size_x, size_y, label_)
    {
        sudoku = sudoku_;
    }

    void event_handle(genv::event ev)
    {
        pushed_down(ev);
        if(pushed) sudoku->restart();
    }

};

class GenerateButton : public PushButton
{
private:
    Sudoku* sudoku;
public:
    GenerateButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_, Sudoku* sudoku_) : PushButton(x_, y_, size_x, size_y, label_)
    {
        sudoku = sudoku_;
    }

    void event_handle(genv::event ev)
    {
        pushed_down(ev);
        if(pushed) sudoku->generate();
    }
};

class ExitButton : public PushButton
{
private:
    Sudoku* sudoku;
public:
    ExitButton(const int &x_, const int &y_, const int &size_x, const int &size_y, const std::string &label_, Sudoku* sudoku_) : PushButton(x_, y_, size_x, size_y, label_)
    {
        sudoku = sudoku_;
    }
    void event_handle(genv::event ev)
    {
        pushed_down(ev);

        if(pushed)
        {
            sudoku->set_running(false);
        }
    }
};

#endif // SUDOKU_HPP_INCLUDED
