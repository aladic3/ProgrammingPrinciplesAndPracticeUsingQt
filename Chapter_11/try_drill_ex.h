#ifndef TRY_DRILL_EX_H
#define TRY_DRILL_EX_H
#pragma once
#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/Simple_window.h"

const double pi = std::acos(-1.0);;


const int x_start = 300;
const int y_start = 150;
const int width_display_default = 1000;
const int high_display_default = 1000;

const int width_default = 60;
const int high_default = 150;
const int margin_default = 10;
const int bold_default = 2;
const int tic_size = 50;


const Point zero_point {0,0};
const Point start_point {x_start,y_start};
const Line_style style_default {Line_style::solid,bold_default};

namespace ch11::_try{
    void first_try();
    void second_try();
}

namespace ch11::drill {
    void do_drill();

}

namespace ch11::exercises{
    struct Box : Shape {
        Box(Point pp, const std::string ss);
        Box(Point pp, int ww, int hh, const std::string ss) : text(pp,ss),
            width(ww), high(hh), box(pp,high,width){};
        void draw_specifics(Painter& painter) const override;
        void move(int dx, int dy) override;
    private:
        Text text;
        int width_symbol = 7;
        int width;
        int high;
        Rectangle box;

    };


    struct Arrow : Shape{
        Arrow(Point p1, Point p2): dir_triangle(get_direction_triangle(p1,p2))
        { add(p1); add(p2);}

        void draw_specifics(Painter& painter) const override;
        void move(int dx, int dy) override;

    private:
        Polygon dir_triangle;
        Polygon get_direction_triangle(Point p1, Point p2);
    };

    namespace ex_2{
        Point n(Rectangle&);
        Point s(Rectangle&);
        Point e(Rectangle&);
        Point w(Rectangle&);
        Point center(Rectangle&);
        Point ne(Rectangle&);
        Point nw(Rectangle&);
        Point se(Rectangle&);
        Point sw(Rectangle&);
    }

    namespace ex_3{
        Point n(Circle&);
        Point s(Circle&);
        Point e(Circle&);
        Point w(Circle&);
        Point center(Circle&);
        Point ne(Circle&);
        Point nw(Circle&);
        Point se(Circle&);
        Point sw(Circle&);

        Point n(Ellipse&);
        Point s(Ellipse&);
        Point e(Ellipse&);
        Point w(Ellipse&);
        Point center(Ellipse&);
        Point ne(Ellipse&);
        Point nw(Ellipse&);
        Point se(Ellipse&);
        Point sw(Ellipse&);
    }

    void ex1();
    void ex2();
    void ex3();
    void ex4();

}

#endif // TRY_DRILL_EX_H
