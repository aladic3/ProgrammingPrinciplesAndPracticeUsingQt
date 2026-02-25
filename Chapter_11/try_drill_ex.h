#ifndef TRY_DRILL_EX_H
#define TRY_DRILL_EX_H

#include "../base.h"

namespace ch11::_try{
    void first_try();
    void second_try();
}

namespace ch11::drill {
    void do_drill();

}

namespace ch11::exercises{
    struct Poly : Polygon {
        Poly(initializer_list<Point> ll);
    };


    struct Box : Shape {
        Box(Point pp, const std::string ss);
        Box(Point pp, int ww, int hh, const std::string ss) :
            width(ww), high(hh), text(pp,ss), box(pp,high,width){};
        void draw_specifics(Painter& painter) const override;
        void move(int dx, int dy) override;
        int get_width() const {return width;}
        Point point(int i) {return box.point(i);}
        const Rectangle& get_box() const{return box;}
    private:
        int width_symbol = 14;
        int width;
        int high;
        Text text;
        Rectangle box;

    };

    struct Regular_polygon : Closed_polyline{
        Regular_polygon(Point center, int radius, int count_sides);
        void draw_specifics(Painter& painter) const override;
        int get_radius() const {return radius;}
        int get_count_sides() const {return count_sides;}

    private:
        Circle circle;
        Marks center;
        int radius;
        int count_sides;
    };

    struct Regular_hexagon : Closed_polyline{

        Regular_hexagon(Point center, int radius){
            Point north = {center.x,center.y-radius};
            Point south = {center.x,center.y+radius};
            auto rl_north = calculate_point_regular_hexagon(center,north);
            auto rl_south = calculate_point_regular_hexagon(center,south);

            Closed_polyline::add(north);
            Closed_polyline::add(rl_north.second);
            Closed_polyline::add(rl_south.first);

            Closed_polyline::add(south);
            Closed_polyline::add(rl_south.second);
            Closed_polyline::add(rl_north.first);
        }
        Regular_hexagon(){Regular_hexagon(zero_point,30);}

    private:
        pair<Point,Point> calculate_point_regular_hexagon(Point center, Point B);

    };

    struct Regular_hexagons : Regular_hexagon {
        Regular_hexagons(int count, Point center, int radius, int margin);
        void draw_specifics(Painter& painter) const override;
        void move(int x, int y) override;

    private:
        unique_ptr<Vector_ref<Regular_hexagon>> vec;
    };


    struct Arrow : Line{
        Arrow(Point p1, Point p2): Line(p1,p2),dir_triangle(get_direction_triangle(p1,p2))
        { Shape::set_fill_color(Color::black);}

        void set_color(Color col) {Shape::set_fill_color(col);Shape::set_color(col);}

        void draw_specifics(Painter& painter) const override;
        void move(int dx, int dy) override;

    private:
        Polygon dir_triangle;
        Polygon get_direction_triangle(Point p1, Point p2);
    };

    struct Right_triangle : Polygon {
        enum Orientation{nw,se,ne,sw};

        Right_triangle(Point pp, int ww, int hh, Orientation oo=ne);
    };

    struct Tile_triangles : Shape {
        Tile_triangles(Point pp, int ww, int hh, int size, int margin = 5);
        void draw_specifics(Painter& painter) const override;
        void move(int dx, int dy) override;
    private:
        Vector_ref<Right_triangle> tri_v;
    };

    namespace ex_2{
        Point n(const Rectangle&);
        Point s(const Rectangle&);
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

    struct Star : Closed_polyline{
        Star(Point cc, int radius, int count_corners);

    };

    std::vector<Point> calculate_coordinates_equal_corner(Point center, int radius, int count_points);


    void ex1();
    void ex2();
    void ex3();
    void ex4();
    void ex5();
    void ex6();
    void ex7();
    void ex8();
    void ex9();
    void ex10();
    void ex11(int margin = 5);
    void ex12();
    void ex13();
    void ex14_15();
    void ex16();
    void ex17();
    void ex18();

}

#endif // TRY_DRILL_EX_H
