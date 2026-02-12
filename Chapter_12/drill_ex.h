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

void ex_1();

}


#endif // DRILL_EX_H
