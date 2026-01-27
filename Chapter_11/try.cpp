#include "try_drill_ex.h"

namespace ch11::_try {
    void first_try(){
        int width_grid_el = 30;
        int high_grid_el = 30;
        int width_line = 3;
        Application app;
        Simple_window win {zero_point,width_display_default,high_display_default,"ch11_try1"};

        Lines grid;

        for (int x = 0; x < width_display_default; x += width_grid_el)
            grid.add({x,0},{x,high_display_default});

        for (int y = 0; y < high_display_default; y += high_grid_el)
            grid.add({0,y},{width_display_default,y});

        grid.set_color(Color::blue);
        grid.set_style(Line_style{Line_style::dashdotdot,width_line});

        win.attach(grid);
        win.wait_for_button();
    }

    void second_try(){
        Application app;
        Simple_window win {zero_point,width_display_default,high_display_default,"ch11_try2"};

        Image img{zero_point,"image.png"};
        img.scale(width_display_default,high_display_default,false);

        win.attach(img);
        win.wait_for_button();
    }
}
