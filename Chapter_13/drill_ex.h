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



namespace ch13::exercises {
    template<class Precision>
    struct Fct1 : Shape {
        using F1 = std::function<double(double)>;
        using F2 = std::function<double(double,double)>;

        Fct1(const F1& ff, pair<double,double> rr, Point oo, pair<double,double> xy = {25,25}, Precision pp = 1);
        Fct1(const F2& ff2, pair<double,double> rr, Point oo,  pair<double,double> xy = {25,25}, Precision pp = 1);

        [[nodiscard]] F1 f1() const;
        void set_f(const F1 &ff);
        void set_f(const F2 &ff2);
        [[nodiscard]] pair<double, double> r1_3() const;
        void set_r1_2(const pair<double, double> &rr);
        [[nodiscard]] Point orig1() const ;
        void set_orig(const Point &oo);
        [[nodiscard]] int count1() const ;
        [[nodiscard]] pair<double, double> xy_scale1() const;
        void set_xy_scale(const pair<double, double> &xy);

        void reset();
        void draw_specifics(Painter& painter) const override;
        void move(int dx, int dy) override;

    private:
        unique_ptr<Function> f_shape;

        F1 function_one_arg;

        pair<double,double> r1_2;
        Point orig;
        const int base_count = 100;
        int count;
        pair<double,double> xy_scale;
        Precision precision;
    };

    struct Bar_graph : Shape {
        Bar_graph(const vector<double>& data, Point origin,  const pair<int,int>& width_bar_and_spase =  {10,10}, int xy_scale = 5);

        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;
    private:

        vector<unique_ptr<Rectangle>> shape_each_bar;
    };

    void ex_1();
    void ex_2();
    void ex_4();
    void ex_5();
    void ex_6();

}
#endif // DRILL_EX_H
