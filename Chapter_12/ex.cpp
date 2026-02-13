#include "drill_ex.h"

namespace ch12::exercices {

void Face::draw_specifics(Painter& painter) const{
    painter.draw_ellipse(center(),radius,radius);
    left_eye.draw_specifics(painter);
    right_eye.draw_specifics(painter);
    mouth.draw_specifics(painter);
}

void Face::move(int x, int y){
    Circle::move(x,y);
    left_eye.move(x,y);
    right_eye.move(x,y);
    mouth.move(x,y);
    redraw();
}

Face::Face(Point p, int rr) : Circle(p,rr),
                                eye_size(static_cast<int>(lround(rr*0.1))), radius(rr),
                                left_eye(p,eye_size), right_eye(p,eye_size),
                                eyes_accomodation(p,eye_size*5){
        using namespace ch11::exercises::ex_3;

        Point leye_pos = ne(eyes_accomodation);
        Point reye_pos = nw(eyes_accomodation);
        Point mouth_xy = s(eyes_accomodation);
        Point leye_dxy {leye_pos.x-left_eye.center().x,
                       leye_pos.y-left_eye.center().y};
        Point reye_dxy {reye_pos.x-right_eye.center().x,
                       reye_pos.y-right_eye.center().y};

        this->left_eye.move(leye_dxy.x,leye_dxy.y);
        this->right_eye.move(reye_dxy.x,reye_dxy.y);
        this->mouth.move(mouth_xy.x,mouth_xy.y);

}

void Face::make_frowny_mouth(){
    using namespace ch11::exercises::ex_3;
    mouth.add(se(eyes_accomodation));
    mouth.add(sw(eyes_accomodation));
}

void Face::make_smiley_face(){
    using namespace ch11::exercises::ex_3;
    mouth.add(se(eyes_accomodation));
    mouth.add(s(eyes_accomodation));
    mouth.add(sw(eyes_accomodation));
}

void Striped_rectangle::make_striped_lines(int margin){
    int y_start = this->point(0).y;
    int y_end = y_start + this->height();
    int x_start = this->point(0).x;
    int x_end = x_start + this->width();

    for(int y_iterator = y_start; y_iterator < y_end; y_iterator+=margin){
        Point first {x_start,y_iterator};
        Point last {x_end,y_iterator};
        lines.add(first,last);
    }
}

Striped_rectangle::Striped_rectangle(Point x, Point y) : Rectangle(x,y){
    make_striped_lines(5);
}

Striped_rectangle::Striped_rectangle(Point xy, int ww, int hh) : Rectangle(xy,ww,hh){
    make_striped_lines(5);
};

void Striped_rectangle::move(int x, int y){
    Rectangle::move(x,y);
    lines.move(x,y);
}

void Striped_rectangle::draw_specifics(Painter& painter) const{
    Rectangle::draw_specifics(painter);
    lines.draw_specifics(painter);
}

vector<pair<Point,Point>> get_coordinates_stripe_circle(Point center, int radius,
                                                         int margin = 5){
    vector<pair<Point,Point>> result;
    const int y_start = center.y - radius;
    const int y_end = center.y + radius;

    for (int y = y_start; y < y_end; y+=margin){
        int dy = y - center.y;
        double half_width = sqrt(radius*radius - dy*dy);
        int x_left = static_cast<int>(lround(center.x - half_width));
        int x_right = static_cast<int>(lround(center.x + half_width));

        Point left_point {x_left,y};
        Point right_point {x_right, y};

        result.push_back({left_point,right_point});
    }

    return result;
}

Striped_circle::Striped_circle(Point p, int r) : Circle(p, r){
    int margin = 15;
    auto lines_coordinates = get_coordinates_stripe_circle(p,r,margin);

    for (auto& line : lines_coordinates) {
        lines.add(line.first,line.second);
    }
}

void Striped_circle::draw_specifics(Painter& painter) const{
    Circle::draw_specifics(painter);
    lines.draw_specifics(painter);
}

void ex_1(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex1. "};

    Smiley sm (zero_point,21);
    sm.set_color(Color::white);

    Frowny fr (zero_point,50);
    fr.set_color(Color::dark_green);
    fr.move(100,100);



    win.attach(sm);
    win.attach(fr);
    win.wait_for_button();
}

void ex_4(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex4. Immobile circle"};

    Immobile_Circle imc {zero_point,32};
    imc.set_fill_color(Color::dark_blue);


    win.attach(imc);
    win.wait_for_button();
}

void ex_5(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex5. Striped_rectangle"};

    Striped_rectangle s_rec {{100,100}, {200,200}};
    s_rec.set_color(Color::white);

    win.attach(s_rec);
    win.wait_for_button();
}

void ex_6(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex6. Striped_circle"};

    Striped_circle s_cir {{200,200},100};
    s_cir.set_color(Color::white);

    win.attach(s_cir);
    win.wait_for_button();
}

void ex_8(){

    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex8. Regular octagon"};

    Octagon oct {{200,200}, 100};
    oct.set_color(Color::white);
    oct.move(100,100);
    oct.set_fill_color(Color::green);

    win.attach(oct);
    win.wait_for_button();
}
}
