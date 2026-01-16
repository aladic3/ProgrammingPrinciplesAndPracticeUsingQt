#include "drill.h"

double dsin(double d){
    return sin(d);
};

using namespace Graph_lib;

namespace drill_10 {
void test(){
    Application app;
    Simple_window win(Point{20,30},800,700,"Canvas");
    Axis xa(Axis::x,Point{20,300},200,5,"x axis");
    Axis ya(Axis::y,Point{20,300},200,30,"y axis");
    Function sine(dsin,0,120,Point{25, 230},1000,5,50);
    Polygon poly;
    Rectangle rec(Point{120,120},100,50);
    Image scan{Point{50,150},"image.png"};
    Circle c{Point{300,200}, 80};
    Ellipse e{Point{300,200},160,60};
    std::ostringstream ostr;
    Text tt{Point{350, 300},""};
    Mark m{Point{300,200},'Q'};

    m.set_mark_color(Color::dark_yellow);
    m.set_font(Font::helvetica_bold_italic);
    m.set_font_size(25);

    ostr << "Hello" << std::endl
         <<"Graphic" << std::endl
         << "world" << std::endl;

    tt.set_font(Font::courier_bold);
    tt.set_font_size(20);
    tt.set_label(ostr.str());
    tt.set_fill_color(Color::dark_green);
    tt.set_color(Color::blue);

    e.set_fill_color(Color::cyan);
    c.set_style(Line_style::dashdot);

    scan.scale(400,600);
    scan.move(50,100);


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
    win.attach(scan);
    win.attach(xa);
    win.attach(ya);
    win.attach(sine);
    win.attach(poly);
    win.attach(rec);
    win.attach(tt);

    win.attach(e);
    win.attach(c);
    win.attach(m);
    //window.attach(xa);
    //window.set_label("Axis");

    //app.gui_main();
    win.wait_for_button();
}

}
