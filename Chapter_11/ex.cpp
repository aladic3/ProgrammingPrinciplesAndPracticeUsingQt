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

        Point n(Ellipse& e){
            Point result = e.center();

            result.y -= e.minor();

            return result;
        }

        Point s(Ellipse& e){
            Point result = e.center();

            result.y += e.minor();

            return result;
        }

        Point e(Ellipse& e){
            Point result = e.center();

            result.x += e.major();

            return result;
        }

        Point w(Ellipse& e){
            Point result = e.center();

            result.x -= e.major();

            return result;
        }

        Point center(Ellipse& e){
            return e.center();
        }

        Point ne(Ellipse& e){
            Point result = n(e);

            result.x += e.major();

            return result;
        }

        Point nw(Ellipse& e){
            Point result = n(e);

            result.x -= e.major();

            return result;
        }

        Point se(Ellipse& e){
            Point result = s(e);

            result.x += e.major();

            return result;
        }

        Point sw(Ellipse& e){
            Point result = s(e);

            result.x -= e.major();

            return result;
        }
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

    Box::Box(Point pp, const std::string ss):
        width_symbol(14),
        width(ss.size()*width_symbol),
        high(width_symbol*4),
        text({pp.x+width_symbol,pp.y+width_symbol},ss),
        box(pp,width,high) {}

    void Box::draw_specifics(Painter& painter) const{
        this->box.draw_specifics(painter);
        this->text.draw_specifics(painter);
    }
    void Box::move(int dx, int dy){
        this->box.move(dx,dy);
        this->text.move(dx,dy);
        redraw();
    }

    void ex4(){
        Application app;
        Simple_window win{zero_point,width_display_default,high_display_default,"ch11_ex4."};

        Vector_ref<Box> shapes_boxes {
            make_unique<Box>(zero_point,"      "),
            make_unique<Box>(zero_point,"Lines"),
            make_unique<Box>(zero_point,"Polygon"),
            make_unique<Box>(zero_point,"Axis")
        };
        shapes_boxes.push_back(make_unique<Box>(zero_point,"Rectangle"));
        shapes_boxes.push_back(make_unique<Box>(zero_point,"Text"));
        shapes_boxes.push_back(make_unique<Box>(zero_point,"Image"));
        shapes_boxes.push_back(make_unique<Box>(zero_point,"Shape"));

        shapes_boxes[0].move(50,300);
        win.attach(shapes_boxes[0]);
        for(int i = 1; i < shapes_boxes.size()-1; ++i){
            Point prev_start_position = shapes_boxes[i-1].point(0);
            int prev_width = shapes_boxes[i-1].get_width();
            shapes_boxes[i].move(prev_start_position.x + prev_width + margin_default*2,
                                 prev_start_position.y);

            win.attach(shapes_boxes[i]);
        }
        Box& shape = shapes_boxes[shapes_boxes.size()-1];
        shape.move(shapes_boxes[(shapes_boxes.size()-1)/2].point(0).x,
                   shapes_boxes[0].point(0).y - 100);
        win.attach(shape);

        Arrow ar1 {shapes_boxes[0].point(0),shape.point(0)};
        win.attach(ar1);



        win.wait_for_button();
    }

    void ex3(){
        using namespace ex_3;
        Application app;
        Simple_window win{zero_point,width_display_default,high_display_default,"ch11_ex3. Test"};

        Circle c{zero_point,100};
        Ellipse elipse{zero_point,200,100};
        elipse.move(400,400);
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

        Marked_polyline marks_e{"+",{
                            n(elipse),
                            s(elipse),
                            e(elipse),
                            w(elipse),
                            center(elipse),
                            ne(elipse),
                            nw(elipse),
                            se(elipse),
                    sw(elipse)}

        };

        win.attach(elipse);
        win.attach(marks_e);
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
