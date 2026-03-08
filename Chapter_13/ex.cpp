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
            res*= i <= 1 ? 1 : i;

        return res;
    }

    void ex_1() {
        const int n = 1;
        std::cout << fac_recursive(n) << endl;
        cout <<  fac_loop(n) << endl;
    }

    void ex_2() {
        const std::function<double(double)> one = [](double){return 1;};
        const std::function<double(double)> slope = [](double x){return x*0.5;};
        const std::function<double(double)> square = [](double x){return x*x;};
        const std::function<double(double)> cos = [](double x){return std::cos(x);};
        const std::function<double(double)> slope_cos = [&](double x){return cos(x)+slope(x);};


        constexpr pair xy_scale {20,20};

        constexpr pair<int,int> range {-10,11}; //min, max
        constexpr int count_points = 400;

        constexpr string xy_axis_label = "1 == 20 pixels";
        constexpr Point cross_point {300,300};
        const Color axes_color {Color::red};

        Application app;
        Simple_window win {zero_point,1300,800,"ch13_ex2. Class Fct"};

        Fct1 f_one {one,range,cross_point,count_points,xy_scale};
        f_one.set_f(square);
        f_one.set_count(1000);
        f_one.reset();
        f_one.move(0,300);

        win.attach(f_one);
        win.wait_for_button();
    }
}
