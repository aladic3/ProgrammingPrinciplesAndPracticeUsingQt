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

unique_ptr<Vector_ref<Image>> get_attach_images(int N, Simple_window& win){
    unique_ptr<Vector_ref<Image>> result = make_unique<Vector_ref<Image>>();
    const std::string image_name = "image.png";

    int width = width_element; //width == high
    int high = high_element;
    int start = width*2;

    for (int i = 0; i < N; ++i){
        Point left_top {start+width*i*2, i*high*2};
        result->push_back(make_unique<Image>(left_top,image_name));
    }

    for (auto* img: *result){
        img->set_mask(zero_point,width*2,high*2);
        win.attach(*img);
    }


    return result;
}

unique_ptr<Image> get_image(const std::string name, int size = 100){
    auto img = make_unique<Image>(zero_point,name);
    img->scale(size,size,false);
    return img;
}

void attach_snake_image(Simple_window& win, unique_ptr<Image>& img, int x = 8, int y = 8, int step = 100){
    win.attach(*img);
    for (int i = 0; i < x; ++i){
        for(int j = 0; j < y; ++j)
        {
            win.wait_for_button();
            img->move(0,step);

        }

        img->move(step,-y*step);
    }

}

void do_drill(){
    Application app;
    Simple_window win{zero_point,800,1000,"ch11_drills"};

    Lines grid;
    set_lines_to_grid(grid);
    win.attach(grid);

    auto diagonal = get_diagonal_and_attach(win);
    //auto images = get_attach_images(3,win);
    unique_ptr<Image> image = get_image("image2.PNG");
    attach_snake_image(win,image);

    win.wait_for_button();
}

}
