//
// Created by Dmytrenko Kyrylo on 23.03.2026.
//
#include "drill_ex.h"
#include "PPP/GUI_private.h"

namespace ch14::exercises {
    ImageButton::ImageButton(Point xy, int w, int h, const string &label, Callback cb, const string &img_name)  :
      Button(xy, w, h,label, std::move(cb)),
      image(xy,img_name) {
        //image.set_mask({0,0},w,h);
        image.scale(w,h,false);
    }

    void ImageButton::attach(Window &window) {
        Button::attach(window);
        window.attach(image);
    }

    void ImageButton::move(int dx, int dy) {
        Button::move(dx, dy);
        image.move(dx,dy);
    }

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

    Checkerboard_window::Checkerboard_window(Application &application, Point xy, int w, int h, const string &title) :
                My_window(application,xy,w,h,title),
                out_box(Point{10, 40}, "Coordinates:"),
                xy_coordinates_input({100,20},50,15,"example:'x,y'. coordinates input:",[this]{input_coordinates();}),
                wh_input({100,50},50,15,"example:'w,h'. sizes input:",[this]{input_size();})
                 {
        this->attach(out_box);
        this->attach(wh_input);
        this->attach(xy_coordinates_input);
        wh_input.hide_buttons();
        wh_input.show();

        xy_coordinates_input.hide_buttons();
        xy_coordinates_input.show();
        create_checkerboard_buttons(Point{100,100});
        create_shapes_buttons(Point{500,200});


    }


    void Checkerboard_window::input_coordinates() {
        if (this->xy_coordinates_input.last_result() != In_box::accepted) {
            this->xy_coordinates_input.clear_last_result();
            return;
        }

        istringstream is(this->xy_coordinates_input.last_string_value());
        int x,y;
        char ch;

        if (!(is >> x >> ch >> y))
            error("Bad input: x,y values");

        this->inputted_xy = {x,y};
    }

    void Checkerboard_window::input_size() {
        if (this->wh_input.last_result() != In_box::accepted) {
            this->xy_coordinates_input.clear_last_result();
            return;
        }

        istringstream is(this->wh_input.last_string_value());
        int w,h;
        char ch;

        if (!(is >> w >> ch >> h))
            error("Bad input: x,y values");

        this->inputted_size = {w,h};

    }

    void Checkerboard_window::create_square() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");

        this->own_shapes.emplace_back(make_unique<Rectangle>(inputted_xy,inputted_size.first,inputted_size.second));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_circle() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");

        this->own_shapes.emplace_back(make_unique<Circle>(inputted_xy,inputted_size.first));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_equilateral_triangle() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");
        using Triangle = ch11::exercises::Right_triangle;

        this->own_shapes.emplace_back(make_unique<Triangle>(inputted_xy,inputted_size.first,inputted_size.second));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_hexagon() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");
        using Hexagon = ch11::exercises::Regular_hexagon;

        this->own_shapes.emplace_back(make_unique<Hexagon>(inputted_xy,inputted_size.first));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_shapes_buttons(Point origin) {
        Point current = origin;
        int margin = 5;
        int width_button = 50;
        int height_button = 30;

        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Circle",[this]
                        {create_circle();}));
        current.y+=height_button+margin;

        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Triangle",[this]
                        {create_equilateral_triangle();}));
        current.y+=height_button+margin;
        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Hexagon",[this]
                        {create_hexagon();}));
        current.y+=height_button+margin;
        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Square",[this]
                        {create_square();}));

        for (auto& el : checkerboard_buttons)
            attach(*el);
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

                this->checkerboard_buttons.emplace_back(
                    make_unique<ImageButton>(current,width_button,height_button,name.str(),[this,iterator_2d]
                        {press_button_ex3(iterator_2d);}));

                attach(*this->checkerboard_buttons.back()); // attach to window

                current.x += width_button + margin;
            }
            current.x = origin.x;
            current.y += height_button + margin;
        }

    }

    void Checkerboard_window::press_button_ex2(int iterator) {
        checkerboard_buttons[last_index_checkerboard]->get_impl().widget->setStyleSheet("background-color: grey;"); // reset last button

        auto button = &checkerboard_buttons[iterator];
        print_coordinates((*button)->loc);
        (*button)->get_impl().widget->setStyleSheet("background-color: blue;");
        last_index_checkerboard = iterator;
    }

    void Checkerboard_window::press_button_ex3(int iterator) {
        auto& button = *checkerboard_buttons[iterator];
        button.move(randint(-100,100),randint(-100,100));
        print_coordinates(button.loc);
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
