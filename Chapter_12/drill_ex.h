#ifndef DRILL_EX_H
#define DRILL_EX_H
#include "../base.h"
#include "../Chapter_11/try_drill_ex.h"

namespace ch12::drill{
void virtual_func_drill();

}

namespace ch12::exercices {

struct Face : Circle {
    void draw_specifics(Painter& painter) const override;
    void move(int x, int y) override;
protected:
    Face(Point p, int rr);
    void make_frowny_mouth();
    void make_smiley_face();
private:
    int eye_size, radius;
    Circle left_eye, right_eye, eyes_accomodation;
    Open_polyline mouth;
};

struct Smiley : Face {
    Smiley(Point p, int rr) : Face(p,rr){make_smiley_face();}


};

struct Frowny : Face {
    Frowny(Point p, int rr) : Face(p,rr){make_frowny_mouth();}
};

struct Immobile_Circle : Circle{
    Immobile_Circle(Point p, int rr) : Circle(p,rr){};
    void move(int x, int y) {x+=y;y+=x;error("cant't move");} // do first 2 states because IDE not allow not using variables
};

struct Striped_rectangle : Rectangle {
    Striped_rectangle(Point x, Point y);
    Striped_rectangle(Point xy, int ww, int hh);

    void move(int x, int y) override;
    void draw_specifics(Painter& painter) const override;


private:
    void make_striped_lines(int margin = 5);
    Lines lines;
};

struct Striped_circle : Circle {
    Striped_circle(Point p, int r);

    void draw_specifics(Painter& painter) const override;

private:
    Lines lines;
};

struct Octagon : ch11::exercises::Regular_polygon{
    Octagon(Point center, int radius) :
        ch11::exercises::Regular_polygon(center,radius,8){};
};

struct Striped_closed_polyline : Closed_polyline{ // v1 stable without strong invariants
    Striped_closed_polyline(std::initializer_list<Point> p = {});
    void draw_specifics(Painter& painter) const override;

private:
    Lines lines;
};

struct Rounded : Shape {
    Rounded(Point p, int ww, int hh);
    void draw_specifics(Painter& painter) const override;
    void move(int x, int y) override;
private:
    Vector_ref<Arc> rounded_corners;
    Lines sides;
};

struct Box : Pie {
    Box(Point p, int ww, int hh) : Pie(p,ww,hh,90,180) {}
};

struct Group : Shape {
    Group(){}
    Group(bool is_checkers, Point pp = {100,100}, int size_board = 400);

    void add_shape(Shape& sh){ shapes.push_back(sh);}

    void move_checker_left();
    void move_checker_right();

    void move(int dx, int dy) override;
    void draw_specifics(Painter& painter) const override;
private:
    Vector_ref<Shape> shapes;
    int size_board = 400;
};


void ex_1();
void ex_4();
void ex_5();
void ex_6();
void ex_7();
void ex_8();
void ex_9();
void ex_10();
void ex_11();

}


#endif // DRILL_EX_H
