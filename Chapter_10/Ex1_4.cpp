#include "Ex1_4.h"
#include <iostream>
#include <vector>


namespace ex1_4{
    const int x_start = 50;
    const int y_start = 100;
    const int width_default = 60;
    const int high_default = 150;
    const int margin_default = 10;
    const int bold_default = 5;
    const int tic_size = 50;

    const Point start_point {x_start,y_start};
    const Line_style style_default {Line_style::solid,bold_default};

    void set_color_position_rectangle(Rectangle& red_field, int i){
        red_field.set_fill_color(Color::red);
        red_field.set_color(Color::red);
        red_field.move(tic_size*(i%3),tic_size*(i/3));

    }


    void ex5_6(){
        // change resolution == ex6 XD
        const int width_1_4_itch = 57; //macbook air 13.3 itch / 2560 × 1600 px / 227 DPI
        const int width_display = 2560;
        const int high_display = 1600;
        const int margin = 20*margin_default;

        Application app;
        Simple_window win {Point{0,0},width_display,high_display,"ex5-6_ch10"};

        Rectangle rect {start_point,2*width_display/3, 3*high_display/4};
        rect.set_style(style_default);
        rect.set_fill_color(Color::dark_blue);
        rect.move(margin/2, margin/2);

        Rectangle frame_around {start_point,2*width_display/3 + margin, 3*high_display/4 + margin};
        frame_around.set_style({Line_style::solid,width_1_4_itch});
        frame_around.set_color(Color::red);

        win.attach(rect);
        win.attach(frame_around);
        win.wait_for_button();
    }

    /*
         * tic-tac-toe board
         *
         *  x * x
         *  * x *
         *  x * x
         *
         *  0 1 2
         *  3 4 5
         *  6 7 8
         *
         *
         * x - red field
         * * - white
         *
         */
    void ex4(){
        Application app;
        Simple_window win {Point{30,50},800,1000,"ex4_ch10"};

        Rectangle red_field_0{Point{x_start, y_start},tic_size,tic_size};
        Rectangle red_field_2{Point{x_start, y_start},tic_size,tic_size};
        Rectangle red_field_4{Point{x_start, y_start},tic_size,tic_size};
        Rectangle red_field_6{Point{x_start, y_start},tic_size,tic_size};
        Rectangle red_field_8{Point{x_start, y_start},tic_size,tic_size};

        set_color_position_rectangle(red_field_0, 0);
        set_color_position_rectangle(red_field_2, 2);
        set_color_position_rectangle(red_field_4, 4);
        set_color_position_rectangle(red_field_6, 6);
        set_color_position_rectangle(red_field_8, 8);

        win.attach(red_field_0);
        win.wait_for_button();
        win.attach(red_field_2);
        win.attach(red_field_4);
        win.attach(red_field_6);
        win.attach(red_field_8);

        win.wait_for_button();

    }



    void ex3(){
        Application app;  
        Simple_window win {Point{30,50},800,1000,"ex3_ch10"};
        //initial letter K
        Point point_a {start_point};
        Point point_b {x_start,y_start+high_default};
        Point point_c {x_start,y_start+high_default/2};
        Point point_d {x_start + width_default, y_start};
        Point point_e {x_start + width_default, y_start+high_default};

        Line line1 {point_a,point_b};
        Line line2 {point_c, point_d};
        Line line3 {point_c,point_e};

        line1.set_style(style_default);
        line2.set_style(style_default);
        line3.set_style(style_default);
        line1.set_color(Color::dark_cyan);
        line2.set_color(Color::dark_cyan);
        line3.set_color(Color::dark_cyan);


        Ellipse initial_letter_o(start_point,width_default/2,high_default/2);
        initial_letter_o.set_color(Color::dark_green);
        initial_letter_o.set_style(style_default);
        initial_letter_o.move(width_default+3*margin_default,high_default/2);


        Polygon initial_letter_D;
        initial_letter_D.add(start_point);
        initial_letter_D.add({(2*start_point.x+width_default)/2,(2*start_point.y+3)/2}); //TODO
        initial_letter_D.add({start_point.x+width_default,start_point.y+5});
        initial_letter_D.add({start_point.x+width_default+5,(2*start_point.y+high_default)/2}); //TODO
        initial_letter_D.add({start_point.x+width_default,start_point.y+high_default-5});
        initial_letter_D.add({(2*start_point.x+width_default) /2,(2*start_point.y+2*high_default-3)/2}); //TODO
        initial_letter_D.add({start_point.x,start_point.y+high_default});

        initial_letter_D.move(2*width_default+margin_default,0);
        initial_letter_D.set_style(style_default);
        initial_letter_D.set_color(Color::red);


        win.attach(initial_letter_o);
        win.attach(initial_letter_D);
        win.attach(line1);
        win.attach(line2);
        win.attach(line3);

        win.wait_for_button();

    }

    void ex2(){
        Application app;
        Simple_window win {Point{30,50},800,1000,"ex2_ch10"};

        // rectangle
        Rectangle r{Point{x_start, y_start},100,30};
        Text t{{x_start+5, y_start+10}, "Howdy!"};

        win.attach(r);
        win.attach(t);
        win.wait_for_button();
    }


    void ex1(){
        Application app;
        Simple_window win {Point{30,50},800,1000,"ex1_4"};

        // rectangle
        Rectangle r{Point{x_start, y_start},Point{x_start+100, y_start+100}};
        r.set_color(Color::blue);

        win.attach(r);

        // rectangle as polygon
        Polygon rec_as_poly;
        Point start_p{x_start, y_start};

        rec_as_poly.add(start_p);
        rec_as_poly.add({start_p.x+100, start_p.y});
        rec_as_poly.add({start_p.x+100, start_p.y+100});
        rec_as_poly.add({start_p.x, start_p.y+100});

        rec_as_poly.set_color(Color::red);
        rec_as_poly.move(y_start+50,0);

        win.attach(rec_as_poly);


        win.wait_for_button();
    }

}
