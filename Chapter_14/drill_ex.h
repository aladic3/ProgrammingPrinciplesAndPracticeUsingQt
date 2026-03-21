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
      quit_button(Point{origin.x + ww-50,origin.y+5},15,7,"quit",[this]{quit();}),
      in_box(Point{origin.x+ww/2,origin.y+50},50,10,"input \"x,y\":",[this]{next();}),
      out_box(origin,"last x,y:"){
         this->attach(lines);
         this->attach(quit_button);
         this->attach(in_box);
         in_box.hide_buttons();
         in_box.show();
         this->attach(out_box);
      }




   private:
      Application* app;
      Open_polyline lines;
      Button quit_button;
      In_box in_box;
      Out_box out_box;

      void quit(){ app->quit();}
      void next();

   };

   void drill();
}

#endif //PROGRAMMING_QT_DRILL_EX_H