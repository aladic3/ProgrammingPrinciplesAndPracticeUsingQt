#include "try_drill_ex.h"
#include <math.h>

namespace ch11::exercises{


    namespace ex_2{
        Point n(const Rectangle& r){
            const Point& left_top_corner = r.point(0);
            Point result{left_top_corner};

            result.x += r.width()/2;

            return result;
        }
        Point s(const Rectangle& r){
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

        void Regular_polygon::draw_specifics(Painter& painter) const{
            painter.draw_polygon(*this);
            //circle.draw_specifics(painter);
            //center.draw_specifics(painter);
        }

        Regular_polygon::Regular_polygon(Point center, int radius, int count_sides):
            circle(center,radius), center("x",{center,{center.x,center.y-radius}}),
            radius(radius), count_sides(count_sides){


        double corner = 2 * pi / count_sides;
        int x1 = center.x;
        int y1 = center.y;
        Point B = center;
        B.y -= radius;

        Regular_polygon::add(B);
        for (int i  = 1; i < count_sides; ++i){
            int x2 = B.x;
            int y2 = B.y;
            int dx = x2 - x1;
            int dy = y2 - y1;

            int x3 = x1 + dx * cos(corner) - dy * sin(corner);
            int y3 = y1 + dx * sin(corner) + dy * cos(corner);

            B = {x3,y3};
            Regular_polygon::add(B);

        }

    }

    void Regular_hexagons::draw_specifics(Painter& painter) const{
            for(auto& hex : vec)
                hex->draw_specifics(painter);
    }
    void Regular_hexagons::move(int x, int y){
            for (auto& hex : vec){
                hex->move(x,y);
            }
            redraw();
    }

    Regular_hexagons::Regular_hexagons(int count, Point center, int r, int margin = 0){
            const int minimum_count_per_row = 3;
            int count_per_row = count/10 + minimum_count_per_row;
            int dx_overall = r * sqrt(3);
            int dy_overall = 1.5*r;
            int offset_x_overall = r * sqrt(3) / 2;

            for (int i = 0; i < count; ++i){
                Point current_center_point;

                int x_index = i % count_per_row;
                int y_index = i / count_per_row;
                int offset_index = (i / count_per_row) % 2;

                int x_margin = x_index * margin;
                int y_margin = y_index * margin;
                int offset_margin = offset_index * margin;

                int dx_current = dx_overall * x_index + x_margin;
                int dy_current = dy_overall * y_index + y_margin;
                int offset_current = offset_x_overall * offset_index + offset_margin;

                current_center_point.x = center.x + dx_current + offset_current;
                current_center_point.y = center.y + dy_current;

                vec.push_back(make_unique<Regular_hexagon>(current_center_point,r));
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
        box(pp,width,high) {
            Shape::set_color(Color::dark_blue);
            Shape::set_fill_color(Color::yellow);
    }

    void Box::draw_specifics(Painter& painter) const{
        this->box.draw_specifics(painter);
        this->text.draw_specifics(painter);
    }
    void Box::move(int dx, int dy){
        this->box.move(dx,dy);
        this->text.move(dx,dy);
        redraw();
    }


    unique_ptr<Vector_ref<Box>> init_shape_boxes(){
        auto res  = make_unique<Vector_ref<Box>>
            (make_unique<Box>(zero_point,"      "),
             make_unique<Box>(zero_point,"Lines"),
             make_unique<Box>(zero_point,"Polygon"),
             make_unique<Box>(zero_point,"Axis"));
        res->push_back(make_unique<Box>(zero_point,"Rectangle"));
        res->push_back(make_unique<Box>(zero_point,"Text"));
        res->push_back(make_unique<Box>(zero_point,"Image"));

        return res;
    }

    unique_ptr<Vector_ref<Box>> get_arrange_attach_shape_boxes(Simple_window& win){

        auto res = init_shape_boxes();

        (*res)[0].move(50,300);
        win.attach((*res)[0]);

        for(int i = 1; i < (*res).size(); ++i){
            Point prev_start_position = (*res)[i-1].point(0);
            int prev_width = (*res)[i-1].get_width();
            (*res)[i].move(prev_start_position.x + prev_width + margin_default*2,
                                 prev_start_position.y);

            win.attach((*res)[i]);
        }

        return res;
    }

    unique_ptr<Vector_ref<Arrow>> get_attach_shape_arrows(Box& shape,
                                                   Vector_ref<Box>& shape_boxes,
                                                Simple_window& win){
        using namespace ex_2;

        unique_ptr<Vector_ref<Arrow>> arrows = make_unique<Vector_ref<Arrow>>();
        Point shape_south = s(shape.get_box());

        for(auto box: shape_boxes){
            arrows->push_back(make_unique<Arrow>(n(box->get_box()), shape_south));
            win.attach((*arrows)[arrows->size()-1]);
        }

        return arrows;
    }


    pair<Point,Point> Regular_hexagon::calculate_point_regular_hexagon(Point center, Point B){
        pair<Point,Point> result;

        int x1 = center.x;
        int x2 = B.x;
        int y1 = center.y;
        int y2 = B.y;

        int dx = x2 - x1;
        int dy = y2 - y1;

        result.first.x = x1 + dx * 0.5 - dy * sqrt(3)/2;
        result.first.y = y1 + dx * sqrt(3)/2 + dy * 0.5;

        result.second.x = x1 + dx * 0.5 + dy * sqrt(3)/2;
        result.second.y = y1 - dx * sqrt(3)/2 + dy * 0.5;


        return result;
    }

    void ex8(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex8."};

        Regular_polygon pol{{200,200},100,10};

        pol.set_fill_color(253);

        win.attach(pol);
        win.wait_for_button();
    }

    void ex7(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex7."};

        Regular_hexagons hex{103,zero_point,50,5};
        hex.move(100,100);
        hex.set_fill_color(Color::blue);

        win.attach(hex);
        win.wait_for_button();
    }

    void ex6(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex6."};

        Regular_hexagon hex{zero_point,50};
        hex.move(100,100);

        win.attach(hex);
        win.wait_for_button();
    }

    void ex5(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex5."};

        constexpr int rgb_limit = 255;
        constexpr int step = 4;
        constexpr int columns_count = 8;

        Vector_ref<Mark> rgb_color_chart;
        Point current_position = zero_point;
        int y_offset = 0;
        int x_offset = 0;
        int index = rgb_limit / step;

        for (int r = 0; r <= rgb_limit; r+=step){
            int x_block = (r / step) % columns_count;
            int y_block = (r / step) / columns_count;
            x_offset = index * x_block;
            y_offset = index * y_block;//x_offset==0 ? y_offset + (rgb_limit / step) : y_offset;      //(r / columns_count) * rgb_limit / step ;

            for(int g = 0; g <= rgb_limit; g+=step)
                for(int b = 0; b <= rgb_limit; b+=step)
                {
                    current_position.x = g / step + x_offset ;
                    current_position.y = b / step + y_offset ;

                    rgb_color_chart.push_back(make_unique<Mark>(current_position,'.'));
                    Mark& last_el = rgb_color_chart[rgb_color_chart.size()-1];
                    last_el.set_mark_color(Color{r,g,b});

                    win.attach(last_el);
                }

        }

        win.wait_for_button();
    }

    void ex4(){
        Application app;
        Simple_window win{zero_point,width_display_default,high_display_default,"ch11_ex4."};

        unique_ptr<Vector_ref<Box>> shape_boxes = get_arrange_attach_shape_boxes(win);
        unique_ptr<Box> shape = make_unique<Box>(zero_point,"Shape");
        unique_ptr<Vector_ref<Arrow>> shape_arrows;

        shape->move((*shape_boxes)[shape_boxes->size()/2].point(0).x,
                    (*shape_boxes)[0].point(0).y - 100);
        shape_arrows = get_attach_shape_arrows(*shape,*shape_boxes,win);

        using namespace ex_2;

        Box window_box{zero_point,"Window"};
        Box simple_window_box{zero_point,"Simple window"};
        window_box.move(width_default,high_default/3);
        simple_window_box.move(width_default,
                            high_default);
        Arrow simple_to_win_arrow {n(simple_window_box.get_box()),
                                  s(window_box.get_box())};

        Box line_style_box {{window_box.point(0).x + window_box.get_width() * 3,window_box.point(0).y},
                           "Line style"  };
        Box color_box {{window_box.point(0).x + window_box.get_width() * 3 * 2,window_box.point(0).y},
                      "Color"  };
        Box point_box {{window_box.point(0).x + window_box.get_width() * 3 * 2,simple_window_box.point(0).y},
                      "Point"  };

        win.attach(point_box);
        win.attach(color_box);
        win.attach(*shape);
        win.attach(line_style_box);
        win.attach(window_box);
        win.attach(simple_window_box);
        win.attach(simple_to_win_arrow);
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
