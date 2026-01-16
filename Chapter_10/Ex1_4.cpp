#include "Ex1_4.h"

namespace ex1_4{
    const int x_start = 50;
    const int y_start = 100;



    void ex1(){
        Application app;
        Simple_window win {Point{30,50},800,1000,"ex1_4"};

        // rectangle
        Rectangle r{Point{x_start, y_start},Point{x_start+100, y_start+100}};
        r.set_color(Color::blue);

        win.attach(r);

        // rectangle as polygon
        {
            Polygon rec_as_poly;
            Point start_p{x_start, y_start};

            rec_as_poly.add(start_p);
            rec_as_poly.add({start_p.x+100, start_p.y});
            rec_as_poly.add({start_p.x+100, start_p.y+100});
            rec_as_poly.add({start_p.x, start_p.y+100});

            rec_as_poly.set_color(Color::red);

            rec_as_poly.move(y_start+50,0);

            win.attach(rec_as_poly);
        }



        win.wait_for_button();
    }

}
