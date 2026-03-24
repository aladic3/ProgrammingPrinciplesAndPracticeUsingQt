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

    /*
    *  Out_box out_box;
      vector<Shape*> shapes;
      vector<unique_ptr<Shape>> internal_shapes;

      Menu checkerboard_menu_1; // 4x4 buttons
      Menu checkerboard_menu_2;
      Menu checkerboard_menu_3;
      Menu checkerboard_menu_4;
     */

    Checkerboard_window::Checkerboard_window(Application &application, Point xy, int w, int h, const string &title) :
                My_window(application,xy,w,h,title),
                out_box(Point{10, 40}, "Coordinates:")
                 {
        this->attach(out_box);
        create_checkerboard_buttons(Point{100,100});
    }


    void Checkerboard_window::create_checkerboard_buttons(Point origin) {
        Point current = origin;
        int margin = 5;
        int width_button = 50;
        int height_button = 30;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ostringstream name;
                int iterator_2d = j + i*4;

                name << iterator_2d;

                this->buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,name.str(),[this,iterator_2d]
                        {press_button(iterator_2d);}));

                attach(*this->buttons.back()); // attach to window

                current.x += width_button + margin;
            }
            current.x = origin.x;
            current.y += height_button + margin;
        }

    }

    void Checkerboard_window::press_button(int iterator) {
        buttons[last_index]->get_impl().widget->setStyleSheet("background-color: grey;"); // reset last button

        auto button = &buttons[iterator];
        print_coordinates((*button)->loc);
        (*button)->get_impl().widget->setStyleSheet("background-color: blue;");
        last_index = iterator;
    }



    void Checkerboard_window::print_coordinates(Point p) {
        ostringstream os;
        os << p.x << "," << p.y;
        out_box.data.set_label(os.str());
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

    void ex2() {
        Application app;
        Checkerboard_window win{app,zero_point,1000,800,"Ex2"};
        Circle circle{{50,50},30};
        Rectangle rect {zero_point,100,200};
        win.attach(circle);
        win.wait_for_button();

        win.attach(rect);
        win.wait_for_button();
    }
}
