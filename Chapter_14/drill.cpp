//
// Created by Dmytrenko Kyrylo on 20.03.2026.
//
#include "drill_ex.h"

namespace ch14::drill{
    void Lines_window::next() {
        if (this->in_box.last_result() == In_box::accepted) {
            istringstream is(this->in_box.last_string_value());
            int x,y;
            char ch;

            if (!(is >> x >> ch >> y))
                error("Bad input: x,y values");

            this->lines.add(Point{x,y});

            ostringstream os;
            os << x << ch << y;
            this->out_box.data.set_label(os.str());
        }
        this->in_box.clear_last_result();

    }

    void drill() {
        Application app;
        Lines_window ln{app,{0,0},900,700,"drill"};
        app.gui_main();

    }
}