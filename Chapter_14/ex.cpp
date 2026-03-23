//
// Created by Dmytrenko Kyrylo on 23.03.2026.
//
#include "drill_ex.h"
#include "PPP/GUI_private.h"

namespace ch14::exercises {
    My_window::My_window(Application &application, Point xy, int w, int h, const string &title):
    Simple_window(xy,w,h,title),
    app(&application),
    quit_button(Point{w-60,30},30,20,"quit",[&]{quit();}) {
        attach(quit_button);
    }

    void My_window::quit() {
        this->get_impl().end_button_wait();

        app->quit();
        delete this;
    }

    void ex1() {
        Application app;
        My_window win{app,zero_point,1000,800,"Ex1"};
        Circle circle{{50,50},30};
        Rectangle rect {zero_point,100,200};
        win.attach(circle);
        win.wait_for_button();

        win.attach(rect);
        win.wait_for_button();

    }
}
