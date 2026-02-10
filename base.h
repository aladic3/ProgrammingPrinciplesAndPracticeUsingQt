#ifndef BASE_H
#define BASE_H
#pragma once
#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/Simple_window.h"

const double pi = std::acos(-1.0);;

const int long_arrowhead = 14;
const int half_wide_arrowhead = 4;

const int x_start = 300;
const int y_start = 150;
const int width_display_default = 1000;
const int high_display_default = 1000;

const int width_default = 60;
const int high_default = 150;
const int margin_default = 10;
const int bold_default = 2;
const int tic_size = 50;


const Point zero_point {30,30};
const Point start_point {x_start,y_start};
const Line_style style_default {Line_style::solid,bold_default};

#endif // BASE_H
