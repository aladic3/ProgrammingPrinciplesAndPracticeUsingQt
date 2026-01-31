#include "try_drill_ex.h"
#include <math.h>

namespace ch11::exercises{
    const int long_arrowhead = 14;
    const int half_wide_arrowhead = 6;

    namespace ex_2{
        Point n(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width()/2;

            return result;
        }
        Point s(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width()/2;
            result.y += r.height();

            return result;
        }
        Point e(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width();
            result.y += r.height()/2;

            return result;
        }
        Point w(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.y += r.height()/2;

            return result;
        }
        Point center(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width()/2;
            result.y += r.height()/2;

            return result;
        }
        Point ne(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width();

            return result;
        }
        Point nw(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            return result;
        }
        Point se(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width();
            result.y += r.height();

            return result;
        }
        Point sw(Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.y += r.height();

            return result;
        }
    }

    namespace ex_3{
        Point n(Circle& c){
            Point result {c.center()};
            result.y -= c.radius();

            return result;
        }

        Point s(Circle& c){
            Point result {c.center()};
            result.y += c.radius();

            return result;
        }

        Point e(Circle& c){
            Point result {c.center()};
            result.x += c.radius();

            return result;
        }

        Point w(Circle& c){
            Point result {c.center()};
            result.x -= c.radius();

            return result;
        }
        Point center(Circle& c){
            return c.center();
        }
        Point ne(Circle& c){
            Point result {c.center()};
            int xy = static_cast<int>(c.radius()/sqrt(2)) + 1;

            result.x += xy;
            result.y -= xy;

            return result;
        }
        Point nw(Circle& c){
            Point result {c.center()};
            int xy = static_cast<int>(c.radius()/sqrt(2))+ 1;

            result.x -= xy;
            result.y -= xy;

            return result;
        }
        Point se(Circle& c){
            Point result {c.center()};
            int xy = static_cast<int>(c.radius()/sqrt(2)) + 1;

            result.x += xy;
            result.y += xy;

            return result;
        }
        Point sw(Circle&c){
            Point result {c.center()};
            int xy = static_cast<int>(c.radius()/sqrt(2)) + 1;

            result.x -= xy;
            result.y += xy;

            return result;
        }

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

    void ex3(){
        using namespace ex_3;
        Application app;
        Simple_window win{zero_point,width_display_default,high_display_default,"ch11_ex3. Test"};

        Circle c{zero_point,100};
        c.move(200,200);

        Marks marks {"x",{
                          n(c),
                          s(c),
                          e(c),
                          w(c),
                          center(c),
                          ne(c),
                          nw(c),
                          se(c),
                          sw(c)}};

        win.attach(c);
        win.attach(marks);
        win.wait_for_button();

    }

    void ex2(){
        using namespace ex_2;
        Application app;
        Simple_window win{zero_point,width_display_default,high_display_default,"ch11_ex2. Test"};

        Rectangle rec{zero_point,{100,200}};
        rec.move(100,200);

        Marks marks {"x",{
                    n(rec),
                    s(rec),
                    e(rec),
                    w(rec),
                    center(rec),
                    ne(rec),
                    nw(rec),
                    se(rec),
                    sw(rec)}};

        win.attach(rec);
        win.attach(marks);
        win.wait_for_button();
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
