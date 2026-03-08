#ifndef DRILL_EX_H
#define DRILL_EX_H
#include <utility>

#include "../base.h"

namespace ch13::drill{
    constexpr pair age_range {0,150};

    void validate_age(int);
    void validate_name(const pair<string,string>&);
    void validate_name(const string&);

    struct Person {
        Person()= default;
        Person(const pair<string,string>& nn, int aa) : nname(nn), aage(aa)
            {validate_age(aa), validate_name(nn);}

        [[nodiscard]] const string& first_name() const { return nname.first;}
        [[nodiscard]]const string& second_name() const { return nname.second;}
        [[nodiscard]] int age() const {return aage;}

        void set_names(const pair<string,string>& nn) { validate_name(nn); nname = nn;}
        void set_age(int a) { validate_age(a); aage = a;}
    private:
        pair<string,string> nname;
        int aage = 0;
    };

    istream& operator>> (istream& is, Person& person);
    ostream& operator<< (ostream& os, const Person& person);

    void graphing_drill();
    void class_definition_drill();
}

struct Fct1 : Shape {
    Fct1(std::function<double(double)> f, pair<double,double> r1_2, Point orig, int count = 100,
    pair<double,double> xy_scale = {25,25}) :  f_shape(make_unique<Function>(f,r1_2.first,r1_2.second,
         orig,count,xy_scale.first,xy_scale.second)),f(f),r1_2(r1_2),orig(orig),count(count),
                                                  xy_scale(xy_scale){}



    void reset() {
        f_shape.reset();
        f_shape = make_unique<Function>(f,r1_2.first,r1_2.second,
                orig,count,xy_scale.first,xy_scale.second);
    }


    [[nodiscard]] std::function<double(double)> f1() const {
        return f;
    }

    void set_f(const std::function<double(double)> &ff) {
        this->f = ff;
    }

    [[nodiscard]] pair<double, double> r1_3() const {
        return r1_2;
    }

    void set_r1_2(const pair<double, double> &rr) {
        this->r1_2 = rr;
    }

    [[nodiscard]] Point orig1() const {
        return orig;
    }

    void set_orig(const Point &oo) {
        this->orig = oo;
    }

    [[nodiscard]] int count1() const {
        return count;
    }

    void set_count(int cc) {
        this->count = cc;
    }

    [[nodiscard]] pair<double, double> xy_scale1() const {
        return xy_scale;
    }

    void set_xy_scale(const pair<double, double> &xy) {
        this->xy_scale = xy;
    }

    void draw_specifics(Painter& painter) const {
        f_shape->draw_specifics(painter);
    }
    void move(int dx, int dy) {
        f_shape->move(dx,dy);
    }
    //f_shape(make_unique<Function>(f,r1_2.first,r1_2.second,
   // orig,count,xy_scale.first,xy_scale.second)),

private:
    unique_ptr<Function> f_shape;

    std::function<double(double)> f;
    pair<double,double> r1_2;
    Point orig;
    int count;
    pair<double,double> xy_scale;
};

namespace ch13::exercises {
    void ex_1();
    void ex_2();

}
#endif // DRILL_EX_H
