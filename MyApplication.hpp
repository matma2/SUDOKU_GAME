#ifndef MYAPPLICATION_HPP_INCLUDED
#define MYAPPLICATION_HPP_INCLUDED

#include "Widget.hpp"
#include "PushButton.hpp"
#include <vector>
///     ********Sz�ks�ges include-ok********


///     ********--------********

class MyApplication
{
protected:
    std::vector<Widget*> widgets;
    std::vector<Widget*> focusable_widgets;
    bool running;
public:
    ///      *******sz�ks�ges v�ltoz�k �s f�ggv�nyek deklar�l�sa********

        MyApplication();
        inline void clc(const int &Width, const int &Height) const;
        void run_application(const int &Width, const int &Height, const std::string &title_) const;
        void set_running(bool running);
        bool get_running() const;


    ///      ********---------********
};

#endif // MYAPPLICATION_HPP_INCLUDED
