//
// Created by Dmytrenko Kyrylo on 20.03.2026.
//

#ifndef PROGRAMMING_QT_DRILL_EX_H
#define PROGRAMMING_QT_DRILL_EX_H
#include "../base.h"

namespace ch14::drill{

   struct Lines_window : Window {
      Lines_window(Application& app, Point origin, int ww, int hh, const string& title) :
      Window(origin,ww,hh,title),
      app(&app),
      quit_button(Point{origin.x + ww-100,origin.y+5},15,7,"quit",[this]{quit();}),
      in_box(Point{origin.x+ww/2,origin.y+50},50,10,"input \"x,y\":",[this]{next();}),
      out_box(origin,"last x,y:"),
      menu_button(Point{quit_button.loc.x,quit_button.loc.y+30},quit_button.width,quit_button.height,"Menu",[this]{show_menu();}),
      color_menu(Point{menu_button.loc.x,menu_button.loc.y + 30},70,30,Menu::vertical,"Color menu") {
         this->attach(lines);
         this->attach(quit_button);
         this->attach(in_box);
         in_box.hide_buttons();
         in_box.show();
         this->attach(out_box);
         this->attach(menu_button);
         this->attach(color_menu);




         color_menu.attach(make_unique<Button>(origin,0,0,"red",[&]{change(Color::red);}));
         color_menu.attach(make_unique<Button>(origin,0,0,"blue",[&]{change(Color::blue);}));
         color_menu.attach(make_unique<Button>(origin,0,0,"yellow",[&]{change(Color::yellow);}));

         color_menu.hide();

      }




   private:
      Application* app;
      Open_polyline lines;
      Button quit_button;
      In_box in_box;
      Out_box out_box;
      Button menu_button;
      Menu color_menu;

      void show_menu(){menu_button.hide();color_menu.show();}
      void hide_menu(){menu_button.show();color_menu.hide();}

      void quit(){ app->quit();}
      void next();

      void change(Color col){lines.set_color(col);hide_menu();}


   };

   void drill();
}

#endif //PROGRAMMING_QT_DRILL_EX_H