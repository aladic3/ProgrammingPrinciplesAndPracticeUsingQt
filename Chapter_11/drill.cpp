#include "try_drill_ex.h"

namespace ch11::drill {

constexpr int width_element = 100;
constexpr int high_element = 100;
constexpr int width_grid = 800;
constexpr int high_grid = 800;

void set_lines_to_grid(Lines& grid){

    int width = width_element; //width == high

    int x_limit = width_grid; //x_limit == y_limit
    int y_limit = high_grid;

    for (int xy = 0; xy <= x_limit; xy += width){
        grid.add({xy,0},{xy,y_limit});
        grid.add({0,xy},{x_limit,xy});
    }

}

unique_ptr<Vector_ref<Rectangle>> get_diagonal_and_attach(Simple_window& win){
    unique_ptr<Vector_ref<Rectangle>> result = make_unique<Vector_ref<Rectangle>>();
    int width = width_element; //width == high
    int high = high_element;

    int x_limit = width_grid; //x_limit == y_limit


    for (int x = 0; x < x_limit; x += width){
        Point top_left{x,x};
        result->push_back(make_unique<Rectangle>(top_left,width,high));
    }

    for (auto* rec: *result){
        rec->set_fill_color(Color::red);
        rec->set_color(Color::invisible);
        win.attach(*rec);
    }

    return result;
}

void do_drill(){
    Application app;
    Simple_window win{zero_point,800,1000,"ch11_drills"};

    Lines grid;
    set_lines_to_grid(grid);
    auto diagonal = get_diagonal_and_attach(win);

    win.attach(grid);
    win.wait_for_button();
}

}
