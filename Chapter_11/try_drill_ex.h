#ifndef TRY_DRILL_EX_H
#define TRY_DRILL_EX_H
#pragma once
#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/Simple_window.h"

const double pi = std::acos(-1.0);;

const int x_start = 300;
const int y_start = 150;
const int width_display_default = 1000;
const int high_display_default = 1000;

const int width_default = 60;
const int high_default = 150;
const int margin_default = 10;
const int bold_default = 2;
const int tic_size = 50;


const Point zero_point {0,0};
const Point start_point {x_start,y_start};
const Line_style style_default {Line_style::solid,bold_default};

namespace ch11::_try{
    void first_try();
}


#endif // TRY_DRILL_EX_H
