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

    void add_shape(unique_ptr<Shape> sh) {shapes.push_back(std::move(sh));}
    void set_fill_color_last_el(Color col) {shapes.back()->set_fill_color(col);}
    void set_color_last_el(Color col) {shapes.back()->set_color(col);}

    void move_checker_left();
    void move_checker_right();

    void move(int dx, int dy) override;
    void draw_specifics(Painter& painter) const override;
private:
    vector<unique_ptr<Shape>> shapes;
    int size_board = 400;
};

struct Pseudo_window : Shape {

    Pseudo_window(Point pp, int ww, int hh, const string label);

    void move(int dx, int dy) override;
    void draw_specifics(Painter& painter) const override;
private:
    Group elements{};
};

struct Node_shape_factory {
public:
    virtual unique_ptr<Shape> create_node(Point p, int size) const = 0;
};

struct Circle_node_factory : Node_shape_factory {
    unique_ptr<Shape> create_node(Point p, int size) const{
        return make_unique<Circle>(p,size);
    }
};

struct Rectangle_node_factory : Node_shape_factory {
    unique_ptr<Shape> create_node(Point p, int size) const{
        return make_unique<Rectangle>(p,size,size);
    }
};

struct Triangle_node_factory : Node_shape_factory {
    unique_ptr<Shape> create_node(Point p, int size) const{
        using namespace ch11::exercises;
        return make_unique<Regular_polygon>(p,size,3);
    }
};

struct Binary_tree : Shape {
    Binary_tree(size_t ll,
                const string& label ,
                Point pp, const Node_shape_factory& node_factory);
    void move(int dx, int dy) override;
    void draw_specifics(Painter& painter) const override;

private:
    size_t levels = 0; // 0 - zero node, 1 - single node, 2 - single with two subnodes
    unique_ptr<Shape> node_shape; // rect, triangle, circle or any another shape
    unique_ptr<Lines> lr_lines;
    unique_ptr<Text> label_node;


    unique_ptr<Binary_tree> left_node;
    unique_ptr<Binary_tree> right_node;

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
void ex_12();
void ex_13();
void ex_14();

}


#endif // DRILL_EX_H
