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
}
