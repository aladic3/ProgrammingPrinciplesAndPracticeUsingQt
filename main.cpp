#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/Simple_window.h"

double dsin(double d){
    return sin(d);
};

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    Application app;
    Simple_window win(Point{20,30},600,500,"Canvas");

    Axis xa(Axis::x,Point{20,300},200,5,"x axis");
    Axis ya(Axis::y,Point{20,300},200,30,"y axis");

    Function sine(dsin,0,120,Point{25, 230},1000,5,50);

    Polygon poly;

    Rectangle rec(Point{120,120},100,50);

    poly.add(Point{50, 100});
    poly.add(Point{100, 100});
    poly.add(Point{75, 180});

    poly.set_color(Color::dark_magenta);
    poly.set_fill_color(Color::dark_green);
    poly.set_style(Line_style::dashdotdot);

    rec.set_style(Line_style::dash);

    sine.set_color(Color::blue);

    xa.set_color(Color::dark_magenta);
    ya.set_color(Color::dark_cyan);


    //Window window({20, 20}, 600, 400, "Main window");
    //Text text({150, 20}, "Well hello there!");

    //win.attach(text);
    win.attach(xa);
    win.attach(ya);
    win.attach(sine);
    win.attach(poly);
    win.attach(rec);

    //window.attach(xa);
    //window.set_label("Axis");

    //app.gui_main();
    win.wait_for_button();
}
