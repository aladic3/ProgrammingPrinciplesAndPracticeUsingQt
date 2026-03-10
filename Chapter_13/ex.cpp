//
// Created by Dmytrenko Kyrylo on 07.03.2026.
//

#include "drill_ex.h"

namespace ch13::exercises {
    long long int fac_recursive(int n) {
        return n > 1 ? n*fac_recursive(n-1) : 1;
    }

    long long int fac_loop(int n) {
        long long int res = 1;

        for (int i = 1; i <=n; i++)
            res *= i;

        return res;
    }

    void ex_1() {
        constexpr int n = 1;
        std::cout << fac_recursive(n) << endl;
        cout <<  fac_loop(n) << endl;
    }

    void ex_2() {
        const std::function<double(double)> one = [](double){return 1;};
        const std::function<double(double)> slope = [](double x){return x*0.5;};
        const std::function<double(double)> square = [](double x){return x*x;};
        const std::function<double(double)> cos = [](double x){return std::cos(x);};
        const std::function<double(double)> slope_cos = [&](double x){return cos(x)+slope(x);};
        const std::function<double(double,double)> exp_n = [](double x, double precision) {
            double result = 1;
            for (int i = 0; i < precision; ++i) {
                result += pow(x,i) / static_cast<double>(fac_loop(i));
            }
            return result;
        };


        constexpr pair xy_scale {20,20};

        constexpr pair range {-10,30}; //min, max


        constexpr string xy_axis_label = "1 == 20 pixels";
        constexpr Point cross_point {300,300};

        Application app;
        Simple_window win {zero_point,1300,800,"ch13_ex2. Class Fct"};

        Fct1<double> f_one {slope_cos,range,cross_point,xy_scale,10};
        f_one.set_color(Color::dark_green);
        win.attach(f_one);
        win.wait_for_button();

        //f_one.set_f(square);
        f_one.set_f(exp_n);
        //f_one.set_precision(25);
        f_one.reset();
        f_one.move(0,300);


        win.wait_for_button();
    }

    void ex_4() {
        const std::function<double(double)> cos = [](double x){return std::cos(x);};
        const std::function<double(double)> sin = [](double x){return std::sin(x);};
        const std::function<double(double)> sum_sin_cos = [](double x){return std::cos(x) + std::sin(x);};
        const std::function<double(double)> sum_sin_cos_square = [](double x) {
            return std::cos(x)*std::cos(x) + std::sin(x)*std::sin(x);
        };


        constexpr int x_max = 600;
        constexpr int y_max = 600;
        constexpr int xya_length = 400;
        constexpr int xya_scale = 20;
        constexpr int xya_count_notches = xya_length / xya_scale;
        constexpr pair<int,int> range {-10,11}; //min, max
        constexpr int count_points = 400;

        constexpr string xy_axis_label = "1 == 20 pixels";
        constexpr Point cross_point {300,300};
        const Color axes_color {Color::red};


        Application app;
        Simple_window win {zero_point,1300,800,"ch13_ex4"};


        Axis xa {Axis::x,{0,cross_point.y},x_max,xya_count_notches,xy_axis_label};
        Axis ya {Axis::y,{cross_point.x,cross_point.y*2},y_max,xya_count_notches};

        Function f_sin {sin,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_cos {cos,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_square {sum_sin_cos_square,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_sum {sum_sin_cos,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};

        f_cos.set_color(Color::cyan);
        f_square.set_color(Color::blue);
        f_sum.set_color(Color::dark_red);

        xa.set_color(axes_color);
        ya.set_color(axes_color);
        ya.label.move(-150,200);
        xa.label.move(150,0);


        win.attach(xa);
        win.attach(ya);
        win.attach(f_cos);
        win.attach(f_sin);
        win.attach(f_square);
        win.attach(f_sum);

        win.wait_for_button();
    }

    void ex_5() {
        const std::function<double(double,double)> exp_n = [](double x, double precision) {
            double result = 1;
            for (int i = 0; i < precision; ++i) {
                result += pow(x,i) / static_cast<double>(fac_loop(i));
            }
            return result;
        };

        const std::function<double(double)> leibniz_n = [](double x) {
            double result = 0;
            for (int i = 0; i <= x; ++i) {
                result += pow(-1,i) / (2*i + 1);
            }
            return result;
        };


        constexpr pair xy_scale {40,40};

        constexpr pair range {0,15}; //min, max

        constexpr Point cross_point {300,300};

        Application app;
        Simple_window win {zero_point,1300,800,"ch13_ex5"};

        Fct1<double> f_one {leibniz_n,range,cross_point,xy_scale,10};
        f_one.set_color(Color::dark_green);
        win.attach(f_one);
        win.wait_for_button();

        //f_one.set_f(square);
        f_one.set_f(exp_n);
        f_one.reset();


        win.wait_for_button();

    }
}
