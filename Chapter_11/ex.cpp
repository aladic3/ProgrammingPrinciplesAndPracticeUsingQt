#include "try_drill_ex.h"
#include <math.h>

namespace ch11::exercises{
    const int long_arrowhead = 14;
    const int half_wide_arrowhead = 6;
    void Arrow::draw_specifics(Painter& painter) const{
        painter.draw_line(point(0), point(1));
        dir_triangle.draw_specifics(painter);
    }

    void Arrow::move(int dx, int dy){
        Shape::move(dx,dy);
        dir_triangle.move(dx,dy);
        redraw();
    }

    Polygon Arrow::get_direction_triangle(Point p1, Point p2){
        Point C, left_basepoint, right_basepoint;

        double corner_direction = atan2(p2.y - p1.y, p2.x - p1.x);

        C.x = p2.x - long_arrowhead * cos(corner_direction);
        C.y = p2.y - long_arrowhead * sin(corner_direction);

        left_basepoint.x = C.x + half_wide_arrowhead * sin(corner_direction);
        left_basepoint.y = C.y - half_wide_arrowhead * cos(corner_direction);

        right_basepoint.x = C.x - half_wide_arrowhead * sin(corner_direction);
        right_basepoint.y = C.y + half_wide_arrowhead * cos(corner_direction);


        return Polygon{left_basepoint,right_basepoint,p2};
    }

    void ex1(){
        Application app;
        Simple_window win {zero_point,width_display_default,high_display_default,"ch11_ex1. Test"};

        Arrow arr{{30,100},zero_point};
        arr.set_fill_color(Color::black);

        win.attach(arr);
        win.wait_for_button();
    }

}
