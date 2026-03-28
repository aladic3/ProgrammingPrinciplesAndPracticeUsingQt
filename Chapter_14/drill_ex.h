//
// Created by Dmytrenko Kyrylo on 20.03.2026.
//

#ifndef PROGRAMMING_QT_DRILL_EX_H
#define PROGRAMMING_QT_DRILL_EX_H
#include <utility>

#include "../base.h"
#include "Chapter_11/try_drill_ex.h"

namespace ch14::drill{

   struct Lines_window : Window {
      Lines_window(Application& app, Point origin, int ww, int hh, const string& title) :
      Window(origin,ww,hh,title),
      app(&app),
      quit_button(Point{origin.x + ww-100,origin.y+5},15,7,"quit",[this]{quit();}),
      in_box(Point{origin.x+ww/2,origin.y+50},50,10,"input \"x,y\":",[this]{next();}),
      out_box(origin,"last x,y:"),
      menu_button(Point{quit_button.loc.x,quit_button.loc.y+30},quit_button.width,quit_button.height,"Menu",[this]{show_menu();}),
      color_menu(Point{menu_button.loc.x,menu_button.loc.y + 30},70,30,Menu::vertical,"Color menu"),
      style_menu(Point{menu_button.loc.x-75,menu_button.loc.y},70,30,Menu::vertical,"Line style"){
         this->attach(lines);
         this->attach(quit_button);
         this->attach(in_box);
         in_box.hide_buttons();
         in_box.show();
         this->attach(out_box);
         this->attach(menu_button);
         this->attach(color_menu);
         this->attach(style_menu);

         color_menu.attach(make_unique<Button>(origin,0,0,"red",[&]{change_color(Color::red);}));
         color_menu.attach(make_unique<Button>(origin,0,0,"blue",[&]{change_color(Color::blue);}));
         color_menu.attach(make_unique<Button>(origin,0,0,"yellow",[&]{change_color(Color::yellow);}));

         style_menu.attach(make_unique<Button>(origin,0,0,"Dash dot",[&]{change_style(Line_style::dashdot);}));
         style_menu.attach(make_unique<Button>(origin,0,0,"Dash dot dot",[&]{change_style(Line_style::dashdotdot);}));
         style_menu.attach(make_unique<Button>(origin,0,0,"Dash",[&]{change_style(Line_style::dash);}));
         style_menu.attach(make_unique<Button>(origin,0,0,"Dot",[&]{change_style(Line_style::dot);}));
         style_menu.attach(make_unique<Button>(origin,0,0,"Solid",[&]{change_style(Line_style::solid);}));

         style_menu.hide();
         color_menu.hide();
         this->lines.set_style(Line_style{Line_style::solid,4});

      }




   private:
      Application* app;
      Open_polyline lines;
      Button quit_button;
      In_box in_box;
      Out_box out_box;
      Button menu_button;
      Menu color_menu;
      Menu style_menu;

      void show_menu(){menu_button.hide();color_menu.show();style_menu.show();}
      void hide_menu(){menu_button.show();color_menu.hide();style_menu.hide();}

      void quit(){ app->quit();}
      void next();

      void change_color(Color col){lines.set_color(col);hide_menu();}
      void change_style(Line_style line_style) {
         lines.set_style(Line_style{static_cast<Line_style::Line_style_type>(line_style.style()),
                                 lines.style().width()});
         hide_menu();
      }


   };

   void drill();
}

namespace ch14::exercises {
   struct ImageButton : Button {
      ImageButton(Point xy, int w, int h, const string &label, Callback cb, const string& img_name = "button.PNG");

      void attach(Window &) override;
      void move(int dx, int dy) override;

   private:
      Image image;
   };

   struct My_window : Simple_window {
      My_window(Application& application, Point xy, int w, int h, const string& title );

   private:
      Application* app;
      Button quit_button;
      void quit();
   };


   struct Checkerboard_window : My_window {
      Checkerboard_window(Application& application, Point xy, int w, int h, const string& title);

      [[nodiscard]] Point get_inputted_xy() const;
      [[nodiscard]] Shape* get_last_shape() const;

   private:
      Point inputted_xy {-1,-1};
      pair<int,int> inputted_size {-1,-1};

      Out_box out_box;
      In_box xy_coordinates_input;
      In_box wh_input;

      vector<unique_ptr<Button>> checkerboard_buttons;
      vector<unique_ptr<Button>> make_shapes_buttons;

      int last_index_checkerboard = 0;

      vector<unique_ptr<Shape>> own_shapes;


      void input_coordinates();
      void input_size();

      void create_square();
      void create_circle();
      void create_equilateral_triangle();
      void create_hexagon();

      void create_shapes_buttons(Point origin);
      void create_checkerboard_buttons(Point origin);
      void press_button_ex2(int iterator);
      void press_button_ex3(int iterator);

      void print_coordinates(Point p);
   };


   struct Watch_face : Shape {
      Watch_face(Point origin, int radius);

      void draw_specifics(Painter &painter) const override;
      void move(int dx, int dy) override;

      void increment_seconds_by_one();

      void set_minute_hand(int minutes);
      void set_second_hand(int second);
      void set_hour_hand(int hour);

      struct Properties {
         Point center{100,100};
         int radius = 50;

         int width_hour = 4;
         int width_minute = 4;
         int width_second = 2;
         int width_tick = 1;

         int current_second = 15;
         int current_minute = 35;
         int current_hour = 17;

         int long_second_hand = radius;
         int long_minute_hand = long_second_hand;
         int long_hour_hand = static_cast<int>(lround(0.6 * long_minute_hand));

         int long_tick = radius/10;

         Color second_color = Color::red;
         Color minute_color = Color::blue;
         Color hour_color = Color::cyan;
         Color ticks_color = Color::white;
         Color face_color = Color::black;
      };

   private:
      Properties properties;


      unique_ptr<Shape> clockFace;
      unique_ptr<Shape> hourHand;
      unique_ptr<Shape> minuteHand;
      unique_ptr<Shape> secondHand;
      std::vector<unique_ptr<Shape>> tickMarks;

      void update_time_from_std();

      //std::vector<Point> hour_hand_coordinates;

      Point calculate_hour_hand_coordinate();
      void createClockFace();
      void createHourHand();
      void createMinuteHand();
      void createSecondHand();
      void createTickMarks();

      void set_minute_hand();
      void set_second_hand();
      void set_hour_hand();

      static Point get_turn_coordinate(Point center, Point north, double angle);
      static Point get_segment_coordinate(Point center, Point edge_point, double lambda);
   };

   struct Window_ex5 {
      Window_ex5(Application& application, Point xy, int w, int h, const string& title);

      void attach(Shape& sh);
      void wait_for_button();

   private:
      Button next_location_button;
      Checkerboard_window win;

      void move_last_shape();
   };



   void ex1();
   void ex2_4();
   void ex5();
   void ex6();
}
#endif //PROGRAMMING_QT_DRILL_EX_H