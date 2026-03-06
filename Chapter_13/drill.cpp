#include "drill_ex.h"

namespace ch13::drill{

void graphing_drill(){
    const std::function<double(double)> one = [](double){return 1;};
    const std::function<double(double)> slope = [](double x){return x*0.5;};
    const std::function<double(double)> square = [](double x){return x*x;};
    const std::function<double(double)> cos = [](double x){return std::cos(x);};
    const std::function<double(double)> slope_cos = [&](double x){return cos(x)+slope(x);};



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
    Simple_window win {zero_point,x_max,y_max,"ch13. Graphing drill"};

    // first ver:
    //Axis xa {Axis::x,cross_point,xya_length,xya_count_notches,xy_axis_label};
    //Axis ya {Axis::y,cross_point,xya_length,xya_count_notches,xy_axis_label};

    // first version from drill:
    // Function f_one {one,range.first,range.second,cross_point,400,1,1};

    Axis xa {Axis::x,{0,cross_point.y},x_max,xya_count_notches,xy_axis_label};
    Axis ya {Axis::y,{cross_point.x,cross_point.y*2},y_max,xya_count_notches};

    Function f_one {one,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
    Function f_slope {slope,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
    Function f_square {square,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
    Function f_cos {cos,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
    Function f_slope_cos {slope_cos,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};


    Text label_f_slope {f_slope.point(0),"0.5x"};

    xa.set_color(axes_color);
    ya.set_color(axes_color);
    ya.label.move(-150,200);
    xa.label.move(150,0);

    f_cos.set_color(Color::blue);
    f_slope_cos.set_color(Color::dark_cyan);

    win.attach(f_slope_cos);
    win.attach(f_cos);
    win.attach(label_f_slope);
    win.attach(f_slope);
    win.attach(f_square);
    win.attach(f_one);
    win.attach(xa);
    win.attach(ya);
    win.wait_for_button();
}
void class_definition_drill(){

}
}
