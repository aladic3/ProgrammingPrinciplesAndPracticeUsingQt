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

inline  function<double(double)> get_lamda_one_arg_from_two(const function<double(double,double)>& f, double second_arg) {
    std::cout << "precision in get_lambda_one_from_two: " << second_arg << endl;
    return [=](double x) {  return f(x,second_arg);  };
}

template<class Precision>
struct Fct1 : Shape {
    Fct1(const std::function<double(double)>& ff,
                pair<double,double> rr, Point oo,
                pair<double,double> xy = {25,25}, Precision pp = 1) :
                            function_one_arg(ff),r1_2(rr),orig(oo),count(pp*base_count),xy_scale(xy),precision(pp)
    {
            f_shape = make_unique<Function>(ff,rr.first,rr.second,oo,count,xy.first,xy.second);
    }

    Fct1(const std::function<double(double,double)>& ff2,
        pair<double,double> rr, Point oo,
        pair<double,double> xy = {25,25}, Precision pp = 1) :
            function_one_arg(get_lamda_one_arg_from_two(ff2,pp)),
            r1_2(rr),orig(oo),count(pp*base_count),xy_scale(xy),precision(pp)
    {
        f_shape = make_unique<Function>(function_one_arg,rr.first,rr.second,oo,count,xy.first,xy.second);
    }

    void reset() {
        f_shape = make_unique<Function>(function_one_arg,r1_2.first,r1_2.second,
                orig,count,xy_scale.first,xy_scale.second);
        this->redraw();
    }

    [[nodiscard]] std::function<double(double)> f1() const {    return function_one_arg; }
    void set_f(const std::function<double(double)> &ff) {     this->function_one_arg = ff;    }
    void set_f(const std::function<double(double,double)> &ff2) {
        cout << "Precision in set_f: " << static_cast<double>(precision) << endl;
        this->function_one_arg = get_lamda_one_arg_from_two(ff2,precision);
    }

    [[nodiscard]] pair<double, double> r1_3() const {        return r1_2;    }
    void set_r1_2(const pair<double, double> &rr) {        this->r1_2 = rr;    }

    [[nodiscard]] Point orig1() const {        return orig;    }
    void set_orig(const Point &oo) {        this->orig = oo;    }

    [[nodiscard]] int count1() const {        return count;    }
    //void set_precision(Precision p) { precision = p; count = p * base_count;}

    [[nodiscard]] pair<double, double> xy_scale1() const {        return xy_scale;    }
    void set_xy_scale(const pair<double, double> &xy) {        this->xy_scale = xy;    }

    void draw_specifics(Painter& painter) const override{        f_shape->draw_specifics(painter);    }
    void move(int dx, int dy) override{        f_shape->move(dx,dy);    }

private:
    unique_ptr<Function> f_shape;

    std::function<double(double)> function_one_arg;

    pair<double,double> r1_2;
    Point orig;
    const int base_count = 100;
    int count;
    pair<double,double> xy_scale;
    Precision precision;
};

namespace ch13::exercises {
    void ex_1();
    void ex_2();
    void ex_4();
    void ex_5();

}
#endif // DRILL_EX_H
