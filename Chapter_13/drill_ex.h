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
    constexpr pair length_xy_axis_default {700,700};

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

    struct XY_axis : Shape {
        XY_axis(Point origin, pair<int,int> length_xy_axis,int xy_scale) {
            int count_notches = length_xy_axis.second/xy_scale;
            this->xa = make_unique<Axis>(Axis::x,origin,length_xy_axis.first);
            this->ya = make_unique<Axis>(Axis::y,origin,length_xy_axis.second,count_notches);
        }
        void set_color(Color cc);
        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;
    private:
        unique_ptr<Axis> xa;
        unique_ptr<Axis> ya;
    };

    struct Graph_labels : Shape {
        Graph_labels(Point graph_label_point, const std::string& graph_label);

        void set_color(Color cc);
        void set_graph_label_color(Color cc);
        void set_label_to_graph(const string &label);

        void set_label_to_individual_bar(size_t index, const string &label);
        void add_specific_label(Point pp, const std::string& label);

        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;

    private:
        unique_ptr<Text> graph_label;
        vector<unique_ptr<Text>> bar_labels;
    };



    struct Graph : Shape {

        void set_label_to_graph(const string& label);
        void set_text_color(Color cc);
        void set_graph_label_color(Color cc);

        void add_specific_label(Point pp, const std::string& label);

        virtual void own_set_color(Color cc) = 0;
        virtual void own_set_fill_color(Color cc) = 0;

        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;

    protected:
        void set_label_to_individual_bar(size_t index, const string& label);
        Graph(Point label_pos, const string& label_graph );

    private:
        unique_ptr<Graph_labels> graph_labels;
    };

    struct Line_graph : Graph {
        Line_graph(const vector<double>& data, Point origin, int width_spase = 10,
            int xy_scale = 5,const string& label_graph = "Line_graph");

        void own_set_color(Color cc) override;
        void own_set_fill_color(Color cc) override;

        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;

    private:
        Open_polyline data_view;
    };

    struct Poly_graph : Shape {
        explicit Poly_graph(Point origin, int width_spase = 10,
                            int xy_scale = 5);

        void add_line_graph(const vector<double>& data,const string& label_graph = "Line_graph");
        void set_axis_color(Color cc);

        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;
    private:
        unique_ptr<XY_axis> xy_axis;

        const int width_spase;
        const int xy_scale;

        Point origin;
        vector<unique_ptr<Graph>> graphs;
    };

    struct Bar_graph : Shape {
        Bar_graph(const vector<double>& data, Point origin,  const pair<int,int>& width_bar_and_spase =  {10,10},
            int xy_scale = 5, const string& label_graph = "GG");

        void set_label_to_individual_bar(size_t index, const string& label);
        void set_label_to_graph(const string& label);
        void set_text_color(Color cc);
        void own_set_color(Color cc);
        void set_axis_color(Color cc);
        void own_set_fill_color(Color cc);


        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;
    private:
        vector<unique_ptr<Rectangle>> shape_each_bar;

        unique_ptr<Graph_labels> graph_labels;
        unique_ptr<XY_axis> xy_axis;
    };

    struct Point_graph : Shape {
        Point_graph(const vector<pair<double,double>>& data_xy, Point origin, int width_spase = 10,
            int xy_scale = 5, const string& label_graph = "GG",const string& marks_char = ".");

        void set_color(Color cc);

        void draw_specifics(Painter &painter) const override;
        void move(int dx, int dy) override;

    private:
        Marks data_points;

        unique_ptr<Graph_labels> graph_labels;
        unique_ptr<XY_axis> xy_axis;

    };

    void ex_1();
    void ex_2();
    void ex_4();
    void ex_5();
    void ex_6_9();
    void ex_10();
    void ex11();

}
#endif // DRILL_EX_H
