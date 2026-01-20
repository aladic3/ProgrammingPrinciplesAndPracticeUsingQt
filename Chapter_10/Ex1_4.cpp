#include "Ex1_4.h"
#include <iostream>
#include <vector>


namespace ex1_4{
    const int x_start = 100;
    const int y_start = 150;
    const int width_display_default = 1024;
    const int high_display_default = 800;

    const int width_default = 60;
    const int high_default = 150;
    const int margin_default = 10;
    const int bold_default = 5;
    const int tic_size = 50;


    const Point zero_point {0,0};
    const Point start_point {x_start,y_start};
    const Line_style style_default {Line_style::solid,bold_default};


    void set_rings_properties(Circle& r1, Circle& r2,
                              Circle& r3, Circle& r4, Circle& r5){
        r1.set_color(Color::blue);
        r2.set_color(Color::yellow);
        r3.set_color(Color::black);
        r4.set_color(Color::green);
        r5.set_color(Color::red);

        r1.set_style(style_default);
        r2.set_style(style_default);
        r3.set_style(style_default);
        r4.set_style(style_default);
        r5.set_style(style_default);
    }

    void set_rings_positions(int margin, Circle& r1, Circle& r2,
                             Circle& r3, Circle& r4, Circle& r5){
        auto x_step = r1.radius() + margin;
        auto y_step = r1.radius();

        r2.move(x_step,y_step);
        r3.move(2*x_step,0);
        r4.move(3*x_step,y_step);
        r5.move(4*x_step,0);
    }




    // about method Point Shape.point(int) i'm knew after 1h duration of coding...
    void ex10(){
        const int width_one_line = 230;
        const int high_one_line = 20;
        const std::string file_name {"ch10_ex10"};
        Application app;
        Simple_window win{zero_point,width_display_default,
                          high_display_default,file_name};


        Text file_main{start_point,"main.cpp:"};
        Text line0_main{start_point,"int main() {...}"};
        Rectangle r_main{start_point,width_one_line,high_one_line};
        file_main.move(width_one_line/2,high_one_line*14);
        r_main.move(width_one_line/2,high_one_line*15);
        line0_main.move(width_one_line/2,high_one_line*15);


        Text file_simple_window{start_point,"Simple_window.h:"};
        Text line0_simple_window{start_point,"// Simple window interface"};
        Text line1_simple_window{start_point,"struct Simple_window {...};"};
        Text line2_simple_window{start_point,"..."};
        Rectangle r_simple_window{start_point,width_one_line,high_one_line*3};
        r_simple_window.move(width_one_line+margin_default*3,high_one_line*9);
        file_simple_window.move(width_one_line+margin_default*3,high_one_line*8);
        line0_simple_window.move(width_one_line+margin_default*3,high_one_line*9);
        line1_simple_window.move(width_one_line+margin_default*3,high_one_line*10);
        line2_simple_window.move(width_one_line+margin_default*3,high_one_line*11);


        Text file_gui{start_point,"GUI.h:"};
        Text line0_gui{start_point,"// GUI interface"};
        Text line1_gui{start_point,"struct Button {...};"};
        Text line2_gui{start_point,"..."};
        Rectangle r_gui{start_point,width_one_line,high_one_line*3};
        file_gui.move(2*(width_one_line+margin_default*3),high_one_line*3);
        r_gui.move(2*(width_one_line+margin_default*3),high_one_line*4);
        line0_gui.move(2*(width_one_line+margin_default*3),high_one_line*4);
        line1_gui.move(2*(width_one_line+margin_default*3),high_one_line*5);
        line2_gui.move(2*(width_one_line+margin_default*3),high_one_line*6);


        Text file_graph{start_point,"Graph.h:"};
        Text line0_graph{start_point,"// Graphing interface"};
        Text line1_graph{start_point,"struct Shape {...};"};
        Text line2_graph{start_point,"..."};
        Rectangle r_graph{start_point,width_one_line,high_one_line*3};
        r_graph.move(0,high_one_line*5);
        file_graph.move(0,high_one_line*4);
        line0_graph.move(0,high_one_line*5);
        line1_graph.move(0,high_one_line*6);
        line2_graph.move(0,high_one_line*7);


        Text file_window{start_point,"Window.h:"};
        Text line0_window{start_point,"// Window interface"};
        Text line1_window{start_point,"struct Window {...};"};
        Text line2_window{start_point,"..."};
        Rectangle r_window{start_point,width_one_line,high_one_line*3};
        file_window.move(width_one_line+margin_default*3,high_one_line*2);
        r_window.move(width_one_line+margin_default*3,high_one_line*3);
        line0_window.move(width_one_line+margin_default*3,high_one_line*3);
        line1_window.move(width_one_line+margin_default*3,high_one_line*4);
        line2_window.move(width_one_line+margin_default*3,high_one_line*5);


        Text file_point{start_point,"Point.h:"};
        Text line0_point{start_point,"struct Point {...};"};
        Rectangle r_point{start_point,width_one_line,high_one_line};
        r_point.move(0,high_one_line);
        line0_point.move(1,high_one_line);

        // TODO can refactor this
        // Create function
        // pair<Point,Point> get_top_bottom_shape_points(Shape& sh, width_line)
        Point simple_window_bottom_point{r_simple_window.point(0).x+width_one_line/2,
                                         r_simple_window.point(0).y+high_one_line*3};
        Point main_top_point{r_main.point(0).x+width_one_line/2,r_main.point(0).y};
        Point simple_window_top_point{simple_window_bottom_point.x,
                                      simple_window_bottom_point.y-high_one_line*3};
        Point graph_top_point{r_graph.point(0).x+width_one_line/2,r_graph.point(0).y};
        Point graph_bottom_point{graph_top_point.x,graph_top_point.y+3*high_one_line};
        Point window_top_point{r_window.point(0).x + width_one_line/2,
                                     r_window.point(0).y};
        Point window_bottom_point{window_top_point.x,
                               window_top_point.y+high_one_line*3};
        Point gui_top_point{r_gui.point(0).x + width_one_line/2,
                               r_gui.point(0).y};
        Point gui_bottom_point{gui_top_point.x,
                                  gui_top_point.y+high_one_line*3};
        Point point_top_point{r_point.point(0).x + width_one_line/2,
                            r_point.point(0).y};
        Point point_bottom_point{point_top_point.x,
                               point_top_point.y+high_one_line};

        Line line_main_simple(main_top_point,simple_window_bottom_point);
        Line line_main_graph(main_top_point,graph_bottom_point);
        Line line_simple_gui(simple_window_top_point,gui_bottom_point);
        Line line_gui_window(gui_top_point,window_bottom_point);
        Line line_window_point(window_top_point,point_bottom_point);
        Line line_graph_point(graph_top_point,point_bottom_point);

        win.attach(line_main_simple);
        win.attach(line_main_graph);
        win.attach(line_simple_gui);
        win.attach(line_gui_window);
        win.attach(line_window_point);
        win.attach(line_graph_point);

        win.attach(file_main);
        win.attach(line0_main);
        win.attach(r_main);

        win.attach(file_point);
        win.attach(line0_point);
        win.attach(r_point);

        win.attach(file_graph);
        win.attach(r_graph);
        win.attach(line0_graph);
        win.attach(line1_graph);
        win.attach(line2_graph);

        win.attach(file_window);
        win.attach(r_window);
        win.attach(line0_window);
        win.attach(line1_window);
        win.attach(line2_window);

        win.attach(file_simple_window);
        win.attach(r_simple_window);
        win.attach(line0_simple_window);
        win.attach(line1_simple_window);
        win.attach(line2_simple_window);

        win.attach(file_gui);
        win.attach(r_gui);
        win.attach(line0_gui);
        win.attach(line1_gui);
        win.attach(line2_gui);
        win.wait_for_button();

    }

    void ex9(){
        const std::string file_name {"Gucci-flip-flap"};
        Application app;
        Simple_window win{Point{0,0},width_display_default,
                                     high_display_default,file_name};

        auto width = 600;
        auto high = 500;

        Image im {start_point,"image.png"};
        im.scale(width,high);
        Text label {start_point,file_name};

        label.set_font_size(30);
        label.move(width/3,-margin_default*6);

        win.attach(im);
        win.attach(label);

        win.wait_for_button();
    }

    /*
     * 1 3 5
     *  2 4
     * */
    void ex8(int radius){
        Application app;
        Simple_window default_window{Point{0,0},width_display_default,
                                     high_display_default,"ch10_ex8"};

        auto margin = radius/5;

        Circle ring1{start_point,radius};
        Circle ring2{start_point,radius};
        Circle ring3{start_point,radius};
        Circle ring4{start_point,radius};
        Circle ring5{start_point,radius};

        set_rings_properties(ring1,ring2,ring3,ring4,ring5);
        set_rings_positions(margin,ring1,ring2,ring3,ring4,ring5);

        default_window.attach(ring1);
        default_window.attach(ring2);
        default_window.attach(ring3);
        default_window.attach(ring4);
        default_window.attach(ring5);
        default_window.wait_for_button();


    }

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

        c1.move(static_cast<int>(x_multy*step+current_radius),
                static_cast<int>(y_multy*step-current_radius));
        current_radius += c2.radius();
        c2.move(static_cast<int>(x_multy*step+current_radius),
                static_cast<int>(y_multy*step-current_radius));
        current_radius += c3.radius();
        c3.move(static_cast<int>(x_multy*step+current_radius),
                static_cast<int>(y_multy*step-current_radius));
        current_radius += c4.radius();
        c4.move(static_cast<int>(x_multy*step+current_radius),
                static_cast<int>(y_multy*step-current_radius));
        current_radius += c5.radius();
        c5.move(static_cast<int>(x_multy*step+current_radius),
                static_cast<int>(y_multy*step-current_radius));

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

        Rectangle chimney{start_point,static_cast<int>(0.3*scale),
                          static_cast<int>(1*scale)};
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
        // change resolution == ex6
        //macbook air 13.3 itch / 2560 × 1600 px / 227 DPI... 1.25itch = 57px
        const int width_1_4_itch = 57;
        const int width_display = 2560;
        const int high_display = 1600;
        const int margin = 20*margin_default;

        Application app;
        Simple_window win {Point{0,0},width_display,high_display,"ex5-6_ch10"};

        Rectangle rect {start_point,2*width_display/3, 3*high_display/4};
        rect.set_style(style_default);
        rect.set_fill_color(Color::dark_blue);
        rect.move(margin/2, margin/2);

        Rectangle frame_around {start_point,2*width_display/3 + margin,
                               3*high_display/4 + margin};
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
        initial_letter_D.add({(2*start_point.x+width_default)/2,
                              (2*start_point.y+3)/2});
        initial_letter_D.add({start_point.x+width_default,start_point.y+5});
        initial_letter_D.add({start_point.x+width_default+5,
                              (2*start_point.y+high_default)/2});
        initial_letter_D.add({start_point.x+width_default,
                              start_point.y+high_default-5});
        initial_letter_D.add({(2*start_point.x+width_default) /2,
                              (2*start_point.y+2*high_default-3)/2});
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
