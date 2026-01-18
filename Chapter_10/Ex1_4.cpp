#include "Ex1_4.h"
#include <iostream>
#include <vector>


namespace ex1_4{
    const int x_start = 300;
    const int y_start = 250;
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

    // input empty polygon. color, position, size
    void set_all_roof_parameters(Polygon& roof, int step){
        Point B {3*step,0};
        Point A {0,2*step};
        Point C {6*step,2*step};
        roof.add(A);
        roof.add(B);
        roof.add(C);

        roof.set_fill_color(Color::dark_blue);
        roof.move(x_start,y_start);

    }

    void set_walls_parameters(Rectangle& walls, int step){
        walls.move(step,2*step);
        walls.set_fill_color(Color::yellow);
    }

    void set_door_parameters(Rectangle& door, int step){
        door.move(static_cast<int>(2.6*step),3*step);
        door.set_fill_color(Color::dark_red);
    }

    void set_windows_parameters(Rectangle& window1, Rectangle& window2, int step){
        window1.set_fill_color(Color::white);
        window2.set_fill_color(Color::white);
        window1.move(static_cast<int>(1.3*step),step*3);
        window2.move(static_cast<int>(3.7*step),step*3);
    }

    void set_chimney_parameters(Rectangle& chimney, int step){
        chimney.set_fill_color(Color::black);
        chimney.move(4*step,static_cast<int>(0.3*step));
    }

    void set_smoke_parameters(Circle& c1, Circle& c2, Circle& c3,
                              Circle& c4, Circle& c5, int step){
        c1.set_fill_color(Color::magenta);
        c2.set_fill_color(Color::magenta);
        c3.set_fill_color(Color::magenta);
        c4.set_fill_color(Color::magenta);
        c5.set_fill_color(Color::magenta);

        auto current_radius = c1.radius();
        double x_multy = 4.2;
        double y_multy = 0;

        c1.move(static_cast<int>(x_multy*step+current_radius), static_cast<int>(y_multy*step-current_radius));
        current_radius += c2.radius();
        c2.move(static_cast<int>(x_multy*step+current_radius), static_cast<int>(y_multy*step-current_radius));
        current_radius += c3.radius();
        c3.move(static_cast<int>(x_multy*step+current_radius), static_cast<int>(y_multy*step-current_radius));
        current_radius += c4.radius();
        c4.move(static_cast<int>(x_multy*step+current_radius), static_cast<int>(y_multy*step-current_radius));
        current_radius += c5.radius();
        c5.move(static_cast<int>(x_multy*step+current_radius), static_cast<int>(y_multy*step-current_radius));

    }

    void ex7(int scale){
        const int count_of_marks = 20;
        const int size_axis = count_of_marks*scale;
        auto ya_start_point = Point{x_start,y_start+size_axis};

        Application app;
        Simple_window win {Point{0,0},800,600,"ex7_ch10"};

        Axis xa(Axis::x,start_point,size_axis,count_of_marks);
        Axis ya(Axis::y,ya_start_point,size_axis,count_of_marks);
        xa.set_color(Color::invisible);
        ya.set_color(Color::invisible);

        Polygon roof;
        set_all_roof_parameters(roof,scale);

        Rectangle walls{start_point,4*scale,3*scale};
        set_walls_parameters(walls,scale);

        Rectangle door{start_point,static_cast<int>(0.8*scale),2*scale};
        set_door_parameters(door,scale);

        Rectangle window1{start_point,static_cast<int>(0.8*scale), scale};
        Rectangle window2{start_point,static_cast<int>(0.8*scale), scale};
        set_windows_parameters(window1,window2,scale);

        Rectangle chimney{start_point,static_cast<int>(0.3*scale), static_cast<int>(1*scale)};
        set_chimney_parameters(chimney,scale);

        //smoke from chimney
        int radius = static_cast<int>(0.1*scale);
        Circle c1{start_point,radius};
        radius*=2;
        Circle c2{start_point,radius};
        radius*=2;
        Circle c3{start_point,radius};
        radius*=2;
        Circle c4{start_point,radius};
        radius*=2;
        Circle c5{start_point,radius};
        set_smoke_parameters(c1,c2,c3,c4,c5,scale);



        win.attach(xa);
        win.attach(ya);

        win.attach(c1);
        win.attach(c2);
        win.attach(c3);
        win.attach(c4);
        win.attach(c5);


        win.attach(chimney);
        win.attach(roof);


        win.attach(walls);
        win.attach(window1);
        win.attach(window2);
        win.attach(door);
        win.wait_for_button();

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
