#include "Sudoku.hpp"
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <iostream>

using namespace genv;
using namespace std;

Sudoku::Sudoku() : MyApplication()
{
    // fájl beolvasása a sudoku_tables vektorba
    data_read("tables.txt");
    srand(time(0));
    // választ egy random sort a táblák közül
    std::string chosen = sudoku_tables[rand()%sudoku_tables.size()];
    std::stringstream ss;
    ss << chosen;
    // beolvassuk az act_table-be és az original_table-be
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            char temp;
            ss >> temp;
            int s = temp - '0';
            act_table[i][j] = s;
            solved_table[i][j] = s;
            original_table[i][j] = s;
        }
    }

    // tábla megoldásának elmentése a solved_table-be
    bool isSolved = sudoku_solve();
    if(!sudoku_solve())
    {
        cerr << "Nem megoldható tábla! Kilépés..." << endl;
        running = false;
    }
    // GUI inicializálás
    sb = new SolveButton(600,50,70,30,"Solve!",this);
    cb = new CheckButton(600,100,70,30,"Check!",this);
    rb = new RestartButton(600,150,70,30,"Restart!",this);
    gb = new GenerateButton(600,200,70,30,"Generate!",this);
    st1 = new StaticText(600,250,100,30,"");
    st2 = new StaticText(220,0,100,30,"SUDOKU GAME!!!");
    eb = new ExitButton(600,400,70,30,"EXIT",this);

    widgets.push_back(sb);
    widgets.push_back(cb);
    widgets.push_back(rb);
    widgets.push_back(gb);
    widgets.push_back(st1);
    widgets.push_back(st2);
    widgets.push_back(eb);

    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            int number = act_table[i][j];
            std::string label;
            bool editable;

            if(number == 0)
            {
                label = "";
                editable = true;
            }

            else
            {
                std::stringstream sss;
                sss << number;
                sss >> label;
                editable = false;
            }

            // Tábla elemeinek koordinátái

            int separate = 5;

            if((i==0 || i==1 || i==2) && (j==3 || j==4 || j==5))
            {
                SudokuField* temp = new SudokuField(50+j*50+separate,50+i*50,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==0 || i==1 || i==2) && (j==6 || j==7 || j==8))
            {
                SudokuField* temp = new SudokuField(50+j*50+2*separate,50+i*50,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==3 || i==4 || i==5) && (j==0 || j==1 || j==2))
            {
                SudokuField* temp = new SudokuField(50+j*50,50+i*50+separate,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==3 || i==4 || i==5) && (j==3 || j==4 || j==5))
            {
                SudokuField* temp = new SudokuField(50+j*50+separate,50+i*50+separate,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==3 || i==4 || i==5) && (j==6 || j==7 || j==8))
            {
                SudokuField* temp = new SudokuField(50+j*50+2*separate,50+i*50+separate,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==6 || i==7 || i==8) && (j==0 || j==1 || j==2))
            {
                SudokuField* temp = new SudokuField(50+j*50,50+i*50+2*separate,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==6 || i==7 || i==8) && (j==3 || j==4 || j==5))
            {
                SudokuField* temp = new SudokuField(50+j*50+separate,50+i*50+2*separate,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else if((i==6 || i==7 || i==8) && (j==6 || j==7 || j==8))
            {
                SudokuField* temp = new SudokuField(50+j*50+2*separate,50+i*50+2*separate,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }

            else
            {
                SudokuField* temp = new SudokuField(50+j*50,50+i*50,48,48,label,editable,this,i,j);
                field[i][j] = temp;
                widgets.push_back(temp);
            }
        }
    }

    for(unsigned int i = 0; i < widgets.size(); i++)
    {
        if(widgets[i]->get_focusable()) focusable_widgets.push_back(widgets[i]);
    }
}

void Sudoku :: data_read(const std::string &filename)
{
    ifstream input_file(filename);
    if(!input_file.good())
    {
        cerr << "Hiba! Fájl nem található!";
        running = false;
    }
    else
    {
        while(input_file.good())
        {
            std::string temp;
            getline(input_file, temp);
            sudoku_tables.push_back(temp);
        }

        input_file.close();
    }
}

void Sudoku::solve()
{
    // solved_table-ben lévõ elemeket betölti a GUI-ba
    std::stringstream ss;
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            act_table[i][j]=solved_table[i][j];
            ss << solved_table[i][j];
            field[i][j]->set_init_text(ss.str());
            field[i][j]->wrong_field(false);
            ss.str("");
        }
    }
    st1->set_text("");
}

void Sudoku::restart()
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(field[i][j]->get_editable()) field[i][j]->set_init_text("");
            field[i][j]->wrong_field(false);
            act_table[i][j] = original_table[i][j];
        }
    }

    st1->set_text("");
}

void Sudoku::check()
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(field[i][j]->get_init_text() == "")
            {
                // státusz text widgetre hogy "TRY AGAIN"
                st1->set_text("TRY AGAIN!");
                return;
            }

            std::stringstream ss;
            int value;
            ss << field[i][j]->get_init_text();
            ss >> value;
            if(value != solved_table[i][j])
            {
                // státusz text widgetre hogy "TRY AGAIN"
                st1->set_text("TRY AGAIN!");
                return;
            }
        }
    }

    // státusz text widgetre hogy "WELL DONE!"

    st1->set_text("WELL DONE!");
}

void Sudoku::generate()
{
    srand(time(0));
    // választ egy random sort a táblák közül
    std::string chosen = sudoku_tables[rand()%sudoku_tables.size()];
    std::stringstream ss;
    ss << chosen;
    // beolvassuk az act_table-be
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            char temp;
            ss >> temp;
            int s = temp - '0';
            act_table[i][j] = s;
            solved_table[i][j] = s;
            field[i][j]->wrong_field(false);
            original_table[i][j] = s;
        }
    }

    // tábla megoldásának elmentése a solved_table-be
    bool isSolved = sudoku_solve();
    if(!sudoku_solve())
    {
        cerr << "Nem megoldható tábla! Kilépés..." << endl;
        running = false;
    }

    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            int number = act_table[i][j];
            std::string label;
            bool editable;
            if(number == 0)
            {
                label = "";
                editable = true;
            }
            else
            {
                std::stringstream sss;
                sss << number;
                sss >> label;
                editable = false;
            }

            field[i][j]->set_editable(editable);
            field[i][j]->set_init_text(label);
        }
    }

    st1->set_text("");
}

void Sudoku :: set_act_table(const int &i, const int &j, const int &num)
{
    if(!isSafe(act_table,i,j,num))
    {
        field[i][j]->wrong_field(true);
    }

    else
    {
        field[i][j]->wrong_field(false);
    }
    act_table[i][j] = num;
}


// tábla megoldására a backtracking algoritmust használtam
bool Sudoku::sudoku_solve()
{
    int row, col;


    if (!findUnassignedLocation(row, col))
       return true;


    for (int num = 1; num <= 9; num++)
    {

        if (isSafe(solved_table, row, col, num))
        {

            solved_table[row][col] = num;


            if (sudoku_solve())
                return true;


            solved_table[row][col] = 0;
        }
    }

    return false;
}

bool Sudoku::findUnassignedLocation(int& row, int& col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (solved_table[row][col] == 0)
                return true;
    return false;
}

bool Sudoku::usedInRow(const int grid[9][9], const int &row, const int &num) const
{
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool Sudoku::usedInCol(const int grid[9][9], const int &col, const int &num) const
{
    for (int row = 0; row < 9; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool Sudoku::usedInBox(const int grid[9][9], const int &boxStartRow, const int &boxStartCol, const int &num) const
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

bool Sudoku::isSafe(const int grid[9][9], const int &row, const int &col, const int &num) const
{
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row%3 , col - col%3, num);
}
