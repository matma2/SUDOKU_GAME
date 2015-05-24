#include "MyApplication.hpp"

using namespace genv;
using namespace std;

MyApplication :: MyApplication()
    {
        ///         ******Widget vector feltöltése elemekkel******


            ///  ez a leszármazottban megtörténik



        ///         *******---------*******



        for(unsigned int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->get_focusable()) focusable_widgets.push_back(widgets[i]);
        }

        running = true;
    }

    void MyApplication :: set_running(bool running)
    {
        this->running = running;
    }

    bool MyApplication :: get_running() const
    {
        return running;
    }

    inline void MyApplication :: clc(const int &Width, const int &Height) const
    {
        gout << move_to(0,0) << color(0,0,0) << box(Width,Height);
    }

    void MyApplication :: run_application(const int &Width, const int &Height, const std::string &title_) const
    {
        gout.open(Width, Height);
        gout.set_title(title_);

        event ev;
        int focus = -1;
        gin.timer(50);
        while(gin >> ev && ev.keycode != key_escape && running)
        {
            if(ev.type == ev_mouse)
            {
                if(ev.button == btn_left)
                {
                    focus = -1;
                    for(unsigned int i=0; i<focusable_widgets.size(); i++)
                    {
                        if(focusable_widgets[i]->selected(ev.pos_x, ev.pos_y)) focus = i;
                    }
                }
            }

            if(focus!=-1) focusable_widgets[focus]->event_handle(ev);

            if(ev.type == ev_timer)
            {
                for(Widget *w:widgets)
                {
                    w->draw();
                }
                if(focus!=-1) focusable_widgets[focus]->draw_focus_line();

                gout << refresh;
            }
            clc(Width, Height);
        }
    }

