#include "drill_ex.h"

namespace ch13::drill{

void graphing_drill(){
    constexpr int x_max = 600;
    constexpr int y_max = 600;
    constexpr int xya_length = 400;
    constexpr int xya_scale = 20;
    constexpr int xya_count_notches = xya_length / xya_scale;

    const string xy_axis_label = "1 == 20 pixels";
    Point cross_point {300,300};
    const Color axes_color {Color::red};

    Application app;
    Simple_window win {zero_point,x_max,y_max,"ch13. Graphing drill"};

    Axis xa {Axis::x,cross_point,xya_length,xya_count_notches,xy_axis_label};
    Axis ya {Axis::y,cross_point,xya_length,xya_count_notches,xy_axis_label};

    xa.set_color(axes_color);
    ya.set_color(axes_color);
    ya.label.move(-150,200);
    xa.label.move(150,0);

    win.attach(xa);
    win.attach(ya);
    win.wait_for_button();
}
void class_definition_drill(){

}
}
