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

        Poly::Poly(initializer_list<Point> ll){
            if (ll.size() < 3)
                error("bad count points for Poly\n");

            for (auto& el : ll)
                Polygon::add(el);
        }

        Right_triangle::Right_triangle(Point pp, int ww, int hh, Orientation oo){
            if (hh < 1 || ww < 1)
                error("high or width < 1 px!");

            switch(oo){
            case nw:
                Right_triangle::add(pp);
                Right_triangle::add({pp.x+ww,pp.y});
                Right_triangle::add({pp.x+ww,pp.y-hh});
                break;
            case se:
                Right_triangle::add(pp);
                Right_triangle::add({pp.x,pp.y-hh});
                Right_triangle::add({pp.x+ww,pp.y-hh});
                break;
            case ne:
                Right_triangle::add(pp);
                Right_triangle::add({pp.x+ww,pp.y});
                Right_triangle::add({pp.x,pp.y-hh});
                break;
            case sw:
                Right_triangle::add({pp.x,pp.y-hh});
                Right_triangle::add({pp.x+ww,pp.y-hh});
                Right_triangle::add({pp.x+ww,pp.y});
                break;
            default:
                error("orientation right triangle is bad");
            }

        }

        // arguments np and last_el_index is changing by refference!
        unique_ptr<Right_triangle> get_triangle_for_octagonal(Point& np,
            std::pair<int,int> delta_wh,std::pair<int,int> wh,
            Right_triangle::Orientation oo, int& last_el_index){
            unique_ptr<Right_triangle> res;

            np.x += delta_wh.first;
            np.y += delta_wh.second;

            res = make_unique<Right_triangle>(np,wh.first,wh.second,oo);

            res->set_fill_color(Color(last_el_index));
            ++last_el_index;

            return res;
        }


        Tile_triangles::Tile_triangles(Point pp, int ww, int hh, int size, int margin){
            const std::vector<Right_triangle::Orientation> oo {Right_triangle::ne,Right_triangle::sw};
            const int minimum_count_per_row = 3;
            int count_per_row = size/20 + minimum_count_per_row;
            int dx_overall = ww;
            int dy_overall = hh;


            for (int i = 0; i < size; ++i){
                Point current_start_point;

                int x_index = i % count_per_row;
                int y_index = i / (count_per_row * 2);

                int oo_index = (i / count_per_row) % 2;

                int x_margin = x_index * margin;
                int y_margin = y_index * margin;


                int dx_current = dx_overall * x_index + x_margin;
                int dy_current = dy_overall * y_index + y_margin;

                current_start_point.x = pp.x + dx_current;
                current_start_point.y = pp.y + dy_current;

                this->tri_v.push_back(make_unique<Right_triangle>(current_start_point,ww,hh,oo[oo_index]));
            }
        }
        void Tile_triangles::draw_specifics(Painter& painter) const{
            for (auto& el: this->tri_v)
                el->draw_specifics(painter);
        }
        void Tile_triangles::move(int dx, int dy){
            for (auto& el: this->tri_v)
                el->move(dx,dy);
        }



        unique_ptr<Vector_ref<Right_triangle>> get_octagonal
            (Point pp, int ww, int hh){
            auto triangle_vec = make_unique<Vector_ref<Right_triangle>>();
            Point np = pp;
            int last_el_index = 0;
            //first
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{0,0},{ww,hh},Right_triangle::nw,last_el_index)
                );
            //second
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{ww,0},{ww,hh},Right_triangle::sw,last_el_index)
                );
            //third
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{ww,0},{ww,hh},Right_triangle::ne,last_el_index)
                );
            //4
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{0,hh},{ww,hh},Right_triangle::nw,last_el_index)
                );
            //5
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{0,hh},{ww,hh},Right_triangle::se,last_el_index)
                );
            //6
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{-ww,0},{ww,hh},Right_triangle::nw,last_el_index)
                );
            //7
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{-ww,0},{ww,hh},Right_triangle::sw,last_el_index)
                );
            //8
            triangle_vec->push_back(
                get_triangle_for_octagonal(np,{0,-hh},{ww,hh},Right_triangle::se,last_el_index)
                );

            /*for (int i = 0; i < triangle_vec.size(); ++i)
                triangle_vec[i].set_fill_color(Color(i));*/

            return triangle_vec;
        }




        void Regular_polygon::draw_specifics(Painter& painter) const{
            painter.draw_polygon(*this);
            //circle.draw_specifics(painter);
            //center.draw_specifics(painter);
        }

        std::vector<Point> calculate_coordinates_equal_corner(Point center,
                                                              int radius, int count_points){
            std::vector<Point> result;
            double corner = 2 * pi / count_points;
            int x1 = center.x;
            int y1 = center.y;
            Point B = center;
            B.y -= radius;

            result.push_back(B);
            for (int i  = 1; i < count_points; ++i){
                int x2 = B.x;
                int y2 = B.y;
                int dx = x2 - x1;
                int dy = y2 - y1;

                int x3 = static_cast<int>(lround(x1 + dx * cos(corner) - dy * sin(corner)));
                int y3 = static_cast<int>(lround(y1 + dx * sin(corner) + dy * cos(corner)));

                B = {x3,y3};
                result.push_back(B);

            }
            return result;
        }

    Regular_polygon::Regular_polygon(Point center, int radius, int count_sides):
                circle(center,radius), center("x",{center,{center.x,center.y-radius}}),
                radius(radius), count_sides(count_sides){
            auto points = calculate_coordinates_equal_corner(center, radius, count_sides);

            for(auto& el : points)
                Closed_polyline::add(el);

    }

    Star::Star(Point cc, int radius, int count_corners){
        auto coordinates_top_corners = calculate_coordinates_equal_corner(cc, radius, count_corners);
        auto coordinates_low_corners = calculate_coordinates_equal_corner(cc, static_cast<int>(radius*0.3), count_corners*2);

        size_t lower_index = 1;
        for (size_t i = 0; i < coordinates_top_corners.size(); ++i){
            Closed_polyline::add(coordinates_top_corners[i]);
            Closed_polyline::add(coordinates_low_corners[lower_index]);
            lower_index += 2;
        }

    }

    void Regular_hexagons::draw_specifics(Painter& painter) const{
            for(auto& hex : *vec)
                hex->draw_specifics(painter);
    }
    void Regular_hexagons::move(int x, int y){
            for (auto& hex : *vec){
                hex->move(x,y);
            }
            redraw();
    }

    unique_ptr<Vector_ref<Regular_hexagon>> get_tile_hexagons(int count, Point center, int r, int margin = 0){
        unique_ptr<Vector_ref<Regular_hexagon>> vec = make_unique<Vector_ref<Regular_hexagon>>();

        const int minimum_count_per_row = 3;
        int count_per_row = count/20 + minimum_count_per_row;
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

            vec->push_back(make_unique<Regular_hexagon>(current_center_point,r));
            (*vec)[i].set_fill_color(Color(i%255));
        }

        return vec;
    }

    Regular_hexagons::Regular_hexagons(int count, Point center, int r, int margin = 0):
        vec(get_tile_hexagons(count,center,r,margin)){}


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

    void ex17(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex17. class Star"};
        Vector_ref<Star> stars;
        const int count = 100;
        const int r = 100;
        const int margin = 5;
        const Point start_point {100,100};

        const int minimum_count_per_row = 3;
        int count_per_row = count/11 + minimum_count_per_row;
        int dx_overall = 2*r;
        int dy_overall = 2*r;


        for (int i = 0; i < count; ++i){
            Point current_center_point;
            int count_top_points = i + 3;

            int x_index = i % count_per_row;
            int y_index = i / count_per_row;

            int x_margin = x_index * margin;
            int y_margin = y_index * margin;

            int dx_current = dx_overall * x_index + x_margin;
            int dy_current = dy_overall * y_index + y_margin;

            current_center_point.x = start_point.x + dx_current;
            current_center_point.y = start_point.y + dy_current;

            stars.push_back(make_unique<Star>(current_center_point,r,count_top_points));
            stars[i].set_fill_color(Color(i%255));
            stars[i].set_color(Color(255-i%255));
            win.attach(stars[i]);
        }



        win.wait_for_button();
    }

    void ex16(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex16. class Poly"};
        Vector_ref<Poly> v_poly;

        vector<initializer_list<Point>> good_init_values{
            initializer_list<Point>{
                {50,50}, {150,20}, {250,80}, {230,180},
                    {180,250}, {80,220}, {30,150}
            },
            initializer_list<Point>{
                {100,0}, {200,50}, {200,150},
                    {100,200}, {0,150}, {0,50}
            },
            initializer_list<Point>{{0,0}, {200,0}, {100,150}},
            initializer_list<Point>{{0,0}, {200,0}, {200,200}, {0,200}},
            initializer_list<Point>{{0,0}, {200,0}, {150,100}, {200,200}, {0,200}},
            initializer_list<Point>{{0,0}, {100,100},{300,250}}
        };

        vector<initializer_list<Point>> bad_init_values {
            initializer_list<Point>{{0,0}, {100,100}},
            initializer_list<Point>{{0,0}, {100,100}, {100,100}, {200,0}},
            initializer_list<Point>{{0,0}, {100,0}, {200,0}, {300,0}},
            initializer_list<Point>{{0,0}, {200,200}, {0,200}, {200,0}},
            initializer_list<Point>{{0,0}, {300,0}, {100,200}, {200,-100}, {0,200}}
        };

        // init good val
        for(auto& el : good_init_values){
            v_poly.push_back(make_unique<Poly>(el));
            int index = v_poly.size()-1;
            v_poly[index].set_color(Color(index));
            win.attach(v_poly[index]);
        }

        // test for bad init
        for (auto& el : bad_init_values)
            try{
                v_poly.push_back(make_unique<Poly>(el));
            } catch (exception& ex){
                std::cerr << "Must be bad: msg:" << ex.what() << endl;
            }

        win.wait_for_button();
    }

    void ex14_15(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex14-15. Tile hexagons/different colors."};
        auto tile = get_tile_hexagons(300,zero_point,30, 4);

        for (auto& el: *tile){
            win.attach(*el);
        }
        //Regular_hexagons hex{200,zero_point,30, 4};
        //hex.set_fill_color(Color::dark_blue);
        //win.attach(hex);
        win.wait_for_button();
    }

    void ex13(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex13. Tile Right triangle."};
        Tile_triangles tile_tri{zero_point,30,20,504,1};
        tile_tri.set_fill_color(Color::dark_green);

        win.attach(tile_tri);
        win.wait_for_button();
    }

    void ex12(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex12. Right triangle."};

        Vector_ref<Right_triangle> tri_v;
        int width = 100;
        int high = 200;
        int margin = margin_default;

        for (int i = 0; i < 4; ++i){
            tri_v.push_back(make_unique<Right_triangle>(zero_point,width,high,
                                                        Right_triangle::Orientation(i)));
            tri_v[i].set_fill_color(Color(i));
            tri_v[i].move((width+margin)*i,high);
            win.attach(tri_v[i]);
        }


        auto triangle_vec = get_octagonal({400,300},100,150);


        for (auto& el: *triangle_vec)
            win.attach(*el);



        win.wait_for_button();
    }

    void ex11(int margin){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex11. Color matrix."};

        Vector_ref<Rectangle> vec;
        const int size_h = 25;
        const int size_w = 25;


        for (int i = 0; i < 255; ++i){
            int index = 20;
            int x_offset_index = i / index;
            int y_offset_index = i % index;
            int x_offset = x_offset_index * size_w;
            int y_offset = y_offset_index * size_h;

            int x_margin = x_offset_index * margin;
            int y_margin = y_offset_index * margin;


            Point xy {zero_point.x + x_offset + x_margin,
                     zero_point.y + y_offset + y_margin};

            vec.push_back(make_unique<Rectangle>(xy,size_w,size_h));
            vec[i].set_color(Color::Transparency(0));
            vec[i].set_fill_color(Color(i));
            win.attach(vec[i]);
        }

        win.wait_for_button();
    }

    void ex10(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex10"};

        using namespace ex_3;
        Circle c{zero_point, 50};
        c.move(200,200);

        Mark m {n(c),'x'};
        win.attach(c);
        win.attach(m);


        win.wait_for_button();
        m.move(ne(c).x-m.point(0).x,ne(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(e(c).x-m.point(0).x,e(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(se(c).x-m.point(0).x,se(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(s(c).x-m.point(0).x,s(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(sw(c).x-m.point(0).x,sw(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(w(c).x-m.point(0).x,w(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(nw(c).x-m.point(0).x,nw(c).y-m.point(0).y);
        win.wait_for_button();
        m.move(n(c).x-m.point(0).x,n(c).y-m.point(0).y);

        win.wait_for_button();
    }

    void ex9(){
        Application app;
        Simple_window win{zero_point,1920,1080,"ch11_ex9"};

        using namespace ex_3;
        Ellipse el{zero_point,300,200};
        Axis xa{Axis::x,zero_point,400,40,"x axis"};
        Axis ya{Axis::y,zero_point,300,30,"y axis"};
        Marks foci_s{"x",{el.focus1(),el.focus2(),s(el)}};
        Lines lines{el.focus1(),s(el),s(el),el.focus2()};

        el.move(500,500);
        xa.move(500,500);
        ya.move(500,500);
        foci_s.move(500,500);
        lines.move(500,500);


        win.attach(el);
        win.attach(xa);
        win.attach(ya);
        win.attach(foci_s);
        win.attach(lines);
        win.wait_for_button();

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
