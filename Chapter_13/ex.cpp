//
// Created by Dmytrenko Kyrylo on 07.03.2026.
//

#include "drill_ex.h"

namespace ch13::exercises {
    [[nodiscard]] std::ifstream open_input_stream(const std::string& file_name) {
        std::ifstream ifs {file_name};
        if (!ifs)
            error("can't open file");

        return ifs;
    }

    std::istream& operator>>(std::istream& is, std::vector<pair<int,int>>& vec) {
        int input1, input2;
        char separator;

        while (is >> input1 >> separator >> input2)
            vec.emplace_back(input1,input2);

        if (!is.eof())
            error("bad input!");

        return is;
    }



    std::vector<pair<int,int>> read_pairs_from_file(const std::string& filename) {
        std::vector<pair<int,int>> result;
        auto is = open_input_stream(filename);
        is.exceptions(is.exceptions() | ios::badbit);

        is >> result;

        return result;
    }

    long long int fac_recursive(int n) {
        return n > 1 ? n * fac_recursive(n - 1) : 1;
    }

    long long int fac_loop(int n) {
        long long int res = 1;

        for (int i = 1; i <= n; i++)
            res *= i;

        return res;
    }

    using F1 = std::function<double(double)>;
    using F2 = function<double(double, double)>;
    inline F1 get_lamda_one_arg_from_two(const  F2&f,
                                                               double second_arg) {
        std::cout << "precision in get_lambda_one_from_two: " << second_arg << endl;
        return [=](double x) { return f(x, second_arg); };
    }

    template<class Precision>
    Fct1<Precision>::Fct1(const F1 &ff,
                          pair<double, double> rr, Point oo,
                          pair<double, double> xy, Precision pp) : function_one_arg(ff), r1_2(rr), orig(oo),
                                                                   count(pp * base_count), xy_scale(xy), precision(pp) {
        f_shape = make_unique<Function>(ff, rr.first, rr.second, oo, count, xy.first, xy.second);
    }

    template<class Precision>
    Fct1<Precision>::Fct1(const F2& ff2,
                          pair<double, double> rr, Point oo,
                          pair<double, double> xy,
                          Precision pp) : function_one_arg(get_lamda_one_arg_from_two(ff2, pp)),
                                          r1_2(rr), orig(oo), count(pp * base_count), xy_scale(xy), precision(pp) {
        f_shape = make_unique<Function>(function_one_arg, rr.first, rr.second, oo, count, xy.first, xy.second);
    }

    template<class Precision>
    void Fct1<Precision>::reset() {
        f_shape = make_unique<Function>(function_one_arg, r1_2.first, r1_2.second,
                                        orig, count, xy_scale.first, xy_scale.second);
        this->redraw();
    }

    template<class Precision>
    [[nodiscard]] F1 Fct1<Precision>::f1() const { return function_one_arg; }

    template<class Precision>
    void Fct1<Precision>::set_f(const F1 &ff) { this->function_one_arg = ff; }

    template<class Precision>
    void Fct1<Precision>::set_f(const F2 &ff2) {
        this->function_one_arg = get_lamda_one_arg_from_two(ff2, precision);
    }

    template<class Precision>
    [[nodiscard]] pair<double, double> Fct1<Precision>::r1_3() const { return r1_2; }

    template<class Precision>
    void Fct1<Precision>::set_r1_2(const pair<double, double> &rr) { this->r1_2 = rr; }

    template<class Precision>
    [[nodiscard]] Point Fct1<Precision>::orig1() const { return orig; }

    template<class Precision>
    void Fct1<Precision>::set_orig(const Point &oo) { this->orig = oo; }

    template<class Precision>
    [[nodiscard]] int Fct1<Precision>::count1() const { return count; }

    //void Fct1<Precision>::set_precision(Precision p) { precision = p; count = p * base_count;}

    template<class Precision>
    [[nodiscard]] pair<double, double> Fct1<Precision>::xy_scale1() const { return xy_scale; }

    template<class Precision>
    void Fct1<Precision>::set_xy_scale(const pair<double, double> &xy) { this->xy_scale = xy; }

    template<class Precision>
    void Fct1<Precision>::draw_specifics(Painter &painter) const { f_shape->draw_specifics(painter); }

    template<class Precision>
    void Fct1<Precision>::move(int dx, int dy) { f_shape->move(dx, dy); }


    Bar_graph::Bar_graph(const vector<double>& data, const Point origin, const pair<int,int>& width_bar_and_spase ,
        const int xy_scale, const string& label_graph){

        Point current = origin;
        const int wide_bar = width_bar_and_spase.first * xy_scale;
        const int wide_spase = width_bar_and_spase.second * xy_scale;
        const int count_bars = static_cast<int>(data.size());
        const int length_xa = (wide_bar + wide_spase) * count_bars;
        constexpr int length_ya = 800;

        this->xa = make_unique<Axis>(Axis::x,origin,length_xa);
        this->ya = make_unique<Axis>(Axis::y,origin,length_ya,length_ya/xy_scale);
        this->graph_label = make_unique<Text>(Point{origin.x,origin.y + 20}, label_graph);
        this->graph_label->set_font_size(16);


        for (const auto& el : data) {
            int high_el = static_cast<int>(lround(el * xy_scale));
            Point temp_point = current;

            if (high_el < 0)
                high_el = abs(high_el);
            else if (high_el == 0)
                ++high_el;
            else
                temp_point.y -= high_el;


            this->shape_each_bar.emplace_back(make_unique<Rectangle>(temp_point,wide_bar,high_el));
            this->bar_labels.emplace_back(make_unique<Text>(current,
                std::format("{:.2f}",el) ) );

            current.x += 2*wide_spase;
        }
    }

    void Bar_graph::set_label_to_individual_bar(size_t index, const string &label) {
        if (index > this->shape_each_bar.size()) error("bad index!");
        this->bar_labels[index]->set_label(label);

        redraw();
    }

    void Bar_graph::set_label_to_graph(const string &label) {
        this->graph_label->set_label(label);
        redraw();
    }

    void Bar_graph::set_text_color(Color cc) {
        for (auto& el : this->bar_labels)
            el->set_color(cc);

        this->graph_label->set_color(cc);

    }

    void Bar_graph::own_set_color(Color cc) {
        for (auto& el : this->shape_each_bar)
            el->set_color(cc);

    }

    void Bar_graph::set_axis_color(Color cc) {
        this->xa->set_color(cc);
        this->ya->set_color(cc);

    }

    void Bar_graph::own_set_fill_color(Color cc) {
        for (auto& el : this->shape_each_bar)
            el->set_fill_color(cc);

    }

    void Bar_graph::draw_specifics(Painter &painter) const {
        for (auto& el : this->shape_each_bar )
            el->draw(painter);

        for (auto& el : this->bar_labels)
            el->draw(painter);

        this->xa->draw_specifics(painter);
        this->ya->draw_specifics(painter);
        this->graph_label->draw(painter);
    }

    void Bar_graph::move(int dx, int dy) {
        for (const auto& el : this->shape_each_bar )
            el->move(dx,dy);

        for (auto& el : this->bar_labels)
            el->move(dx,dy);

        this->xa->move(dx,dy);
        this->ya->move(dx,dy);
        this->graph_label->move(dx,dy);
    }

    void ex_1() {
        constexpr int n = 1;
        std::cout << fac_recursive(n) << endl;
        cout << fac_loop(n) << endl;
    }

    void ex_2() {
        const F1 one = [](double) { return 1; };
        const F1 slope = [](double x) { return x * 0.5; };
        const F1 square = [](double x) { return x * x; };
        const F1 cos = [](double x) { return std::cos(x); };
        const F1 slope_cos = [&](double x) { return cos(x) + slope(x); };
        const F2 exp_n = [](double x, double precision) {
            double result = 1;
            for (int i = 0; i < precision; ++i) {
                result += pow(x, i) / static_cast<double>(fac_loop(i));
            }
            return result;
        };


        constexpr pair xy_scale{20, 20};

        constexpr pair range{-10, 30}; //min, max


        constexpr string xy_axis_label = "1 == 20 pixels";
        constexpr Point cross_point{300, 300};

        Application app;
        Simple_window win{zero_point, 1300, 800, "ch13_ex2. Class Fct"};

        Fct1<double> f_one{slope_cos, range, cross_point, xy_scale, 10};
        f_one.set_color(Color::dark_green);
        win.attach(f_one);
        win.wait_for_button();

        //f_one.set_f(square);
        f_one.set_f(exp_n);
        //f_one.set_precision(25);
        f_one.reset();
        f_one.move(0, 300);


        win.wait_for_button();
    }

    void ex_4() {

        const F1 cos = [](double x) { return std::cos(x); };
        const F1 sin = [](double x) { return std::sin(x); };
        const F1 sum_sin_cos = [](double x) { return std::cos(x) + std::sin(x); };
        const F1  sum_sin_cos_square = [](double x) {
            return std::cos(x) * std::cos(x) + std::sin(x) * std::sin(x);
        };


        constexpr int x_max = 600;
        constexpr int y_max = 600;
        constexpr int xya_length = 400;
        constexpr int xya_scale = 20;
        constexpr int xya_count_notches = xya_length / xya_scale;
        constexpr pair range{-10, 11}; //min, max
        constexpr int count_points = 400;

        constexpr string xy_axis_label = "1 == 20 pixels";
        constexpr Point cross_point{300, 300};
        const Color axes_color{Color::red};


        Application app;
        Simple_window win{zero_point, 1300, 800, "ch13_ex4"};


        Axis xa{Axis::x, {0, cross_point.y}, x_max, xya_count_notches, xy_axis_label};
        Axis ya{Axis::y, {cross_point.x, cross_point.y * 2}, y_max, xya_count_notches};

        Function f_sin{sin, range.first, range.second, cross_point, count_points, xya_scale, xya_scale};
        Function f_cos{cos, range.first, range.second, cross_point, count_points, xya_scale, xya_scale};
        Function f_square{
            sum_sin_cos_square, range.first, range.second, cross_point, count_points, xya_scale, xya_scale
        };
        Function f_sum{sum_sin_cos, range.first, range.second, cross_point, count_points, xya_scale, xya_scale};

        f_cos.set_color(Color::cyan);
        f_square.set_color(Color::blue);
        f_sum.set_color(Color::dark_red);

        xa.set_color(axes_color);
        ya.set_color(axes_color);
        ya.label.move(-150, 200);
        xa.label.move(150, 0);


        win.attach(xa);
        win.attach(ya);
        win.attach(f_cos);
        win.attach(f_sin);
        win.attach(f_square);
        win.attach(f_sum);

        win.wait_for_button();
    }

    void ex_5() {
        const F2 exp_n = [](double x, double precision) {
            double result = 1;
            for (int i = 0; i < precision; ++i) {
                result += pow(x, i) / static_cast<double>(fac_loop(i));
            }
            return result;
        };
        const F1 leibniz_n = [](double x) {
            double result = 0;
            for (int i = 0; i <= x; ++i) {
                result += pow(-1, i) / (2 * i + 1);
            }
            return result;
        };

        constexpr pair xy_scale{40, 40};
        constexpr pair range{0, 15}; //min, max
        constexpr Point cross_point{300, 300};

        Application app;
        Simple_window win{zero_point, 1300, 800, "ch13_ex5"};

        Fct1<double> f_one{leibniz_n, range, cross_point, xy_scale, 10};
        f_one.set_color(Color::dark_green);
        win.attach(f_one);
        win.wait_for_button();

        //f_one.set_f(square);
        f_one.set_f(exp_n);
        f_one.reset();


        win.wait_for_button();
    }

    void ex_6_9() {
        Application app;
        Simple_window win{zero_point, 1300, 800, "ch13_ex6_9. Bar graph class"};

        vector<pair<int,int>> data = read_pairs_from_file("heights_usa.txt");
        vector<string> name_bars;
        vector<double> count_people;

        count_people.reserve(data.size());
        name_bars.reserve(data.size());


        for (auto& el : data) {
            count_people.push_back(el.second);
            name_bars.push_back(format("{}\",{}%",el.first,el.second));
        }


        Bar_graph bar_graph {count_people,{30,300}};

        for (size_t i = 0; i < name_bars.size(); ++i)
            bar_graph.set_label_to_individual_bar(i,name_bars[i]);

        bar_graph.own_set_fill_color(Color::blue);
        bar_graph.own_set_color(Color::red);
        bar_graph.set_axis_color(Color::dark_green);
        bar_graph.set_text_color(Color::dark_yellow);
        //bar_graph.set_label_to_individual_bar(5,"123");
        bar_graph.set_label_to_graph("Heights people in USA (in,%)");
        bar_graph.move(10,100);

        win.attach(bar_graph);
        win.wait_for_button();
    }
}
