#include "drill_ex.h"

namespace ch12::exercices {

void Face::draw_specifics(Painter& painter) const{
    painter.draw_ellipse(center(),radius,radius);
    left_eye.draw_specifics(painter);
    right_eye.draw_specifics(painter);
    mouth.draw_specifics(painter);
}

void Face::move(int x, int y){
    Circle::move(x,y);
    left_eye.move(x,y);
    right_eye.move(x,y);
    mouth.move(x,y);
    redraw();
}

Face::Face(Point p, int rr) : Circle(p,rr),
                                eye_size(static_cast<int>(lround(rr*0.1))), radius(rr),
                                left_eye(p,eye_size), right_eye(p,eye_size),
                                eyes_accomodation(p,eye_size*5){
        using namespace ch11::exercises::ex_3;

        Point leye_pos = ne(eyes_accomodation);
        Point reye_pos = nw(eyes_accomodation);
        Point mouth_xy = s(eyes_accomodation);
        Point leye_dxy {leye_pos.x-left_eye.center().x,
                       leye_pos.y-left_eye.center().y};
        Point reye_dxy {reye_pos.x-right_eye.center().x,
                       reye_pos.y-right_eye.center().y};

        this->left_eye.move(leye_dxy.x,leye_dxy.y);
        this->right_eye.move(reye_dxy.x,reye_dxy.y);
        this->mouth.move(mouth_xy.x,mouth_xy.y);

}

void Face::make_frowny_mouth(){
    using namespace ch11::exercises::ex_3;
    mouth.add(se(eyes_accomodation));
    mouth.add(sw(eyes_accomodation));
}

void Face::make_smiley_face(){
    using namespace ch11::exercises::ex_3;
    mouth.add(se(eyes_accomodation));
    mouth.add(s(eyes_accomodation));
    mouth.add(sw(eyes_accomodation));
}

void Striped_rectangle::make_striped_lines(int margin){
    int y_start = this->point(0).y;
    int y_end = y_start + this->height();
    int x_start = this->point(0).x;
    int x_end = x_start + this->width();

    for(int y_iterator = y_start; y_iterator < y_end; y_iterator+=margin){
        Point first {x_start,y_iterator};
        Point last {x_end,y_iterator};
        lines.add(first,last);
    }
}

Striped_rectangle::Striped_rectangle(Point x, Point y) : Rectangle(x,y){
    make_striped_lines(5);
}

Striped_rectangle::Striped_rectangle(Point xy, int ww, int hh) : Rectangle(xy,ww,hh){
    make_striped_lines(5);
};

void Striped_rectangle::move(int x, int y){
    Rectangle::move(x,y);
    lines.move(x,y);
}

void Striped_rectangle::draw_specifics(Painter& painter) const{
    Rectangle::draw_specifics(painter);
    lines.draw_specifics(painter);
}

vector<pair<Point,Point>> get_coordinates_stripe_circle(Point center, int radius,
                                                         int margin = 5){
    vector<pair<Point,Point>> result;
    const int y_start = center.y - radius;
    const int y_end = center.y + radius;

    for (int y = y_start; y < y_end; y+=margin){
        int dy = y - center.y;
        double half_width = sqrt(radius*radius - dy*dy);
        int x_left = static_cast<int>(lround(center.x - half_width));
        int x_right = static_cast<int>(lround(center.x + half_width));

        Point left_point {x_left,y};
        Point right_point {x_right, y};

        result.push_back({left_point,right_point});
    }

    return result;
}

Striped_circle::Striped_circle(Point p, int r) : Circle(p, r){
    int margin = 15;
    auto lines_coordinates = get_coordinates_stripe_circle(p,r,margin);

    for (auto& line : lines_coordinates) {
        lines.add(line.first,line.second);
    }
}

void Striped_circle::draw_specifics(Painter& painter) const{
    Circle::draw_specifics(painter);
    lines.draw_specifics(painter);
}

Point calc_inersection(const pair<Point,Point>& line1,
                                const pair<Point,Point>& line2){
    Point result;
    double t = 0;
    int dx1 = line1.second.x - line1.first.x;
    int dy1 = line1.second.y - line1.first.y;

    int dx2 = line2.second.x - line2.first.x;
    int dy2 = line2.second.y - line2.first.y;

    Point d1 {dx1,dy1};
    Point d2 {dx2,dy2};
    Point r1 {line1.first.x,line1.first.y};
    Point r2 {line2.first.x,line2.first.y};

    double delta = d1.y * d2.x - d1.x * d2.y;

    if (delta == 0){
        cout << "delta == 0";
        return {};
    }

    t = (r2.x - r1.x) * (-d2.y) - (r2.y - r1.y) * (-d2.x);
    t /= delta;

    result.x = static_cast<int>(lround(r1.x + t * d1.x));
    result.y = static_cast<int>(lround(r1.y + t * d1.y));

    return result;
}



void sort_lines_by_x(vector<pair<Point,Point>>& poly_lines) { //bubble method
    for (size_t i = 0; i < poly_lines.size() - 1; ++i)
        for (size_t j = i+1; j < poly_lines.size(); ++j) {
            auto& a = poly_lines[i];
            auto& b = poly_lines[j];

            if (a.first.x > b.first.x)
                std::swap(a,b);
        }
}

void arrange_lines_by_x_coordinate(vector<pair<Point,Point>>& poly_lines){
    // first point must be always lowest by x
    for (auto& line : poly_lines)
        if (line.second.x < line.first.x)
            swap(line.first,line.second);


    sort_lines_by_x(poly_lines);
}

void sort_points_by_x(vector<Point>& points) { //bubble method
    for (size_t i = 0; i < points.size() - 1; ++i)
        for (size_t j = i+1; j < points.size(); ++j) {
            auto& a = points[i];
            auto& b = points[j];

            if (a.x > b.x)
                std::swap(a,b);
        }
}

void sort_points_by_y(vector<Point>& points) { //bubble method
    for (size_t i = 0; i < points.size() - 1; ++i)
        for (size_t j = i+1; j < points.size(); ++j) {
            auto& a = points[i];
            auto& b = points[j];

            if (a.y > b.y)
                std::swap(a,b);
        }
}

pair<int,int> get_min_max_x(vector<Point>& points){
    sort_points_by_x(points);
    return {points.front().x, points.back().x};
}

pair<int,int> get_min_max_y(vector<Point>& points){
    sort_points_by_y(points);
    return {points.front().y, points.back().y};
}

void init_points_and_lines(std::initializer_list<Point>& p, vector<Point>& points,
                       vector<pair<Point,Point>>& poly_lines){
    if (p.size() < 3)
        error("can't create striped closed polyline");

    poly_lines.push_back({*p.begin(),*(p.end()-1)});
    points.push_back(*p.begin());

    for (auto it = p.begin()+1; it != p.end(); ++it){
        poly_lines.push_back({*(it-1),*it});
        points.push_back(*it);
    }
}

vector<pair<Point,Point>> calculate_striped_lines_coordinates_poly(std::initializer_list<Point>& p,
                                                                    int margin = 5){
    pair<int,int> min_max_x {0,0};
    pair<int,int> min_max_y {0,0};

    vector<pair<Point,Point>> result;
    vector<pair<Point,Point>> poly_lines;
    vector<Point> points;

    init_points_and_lines(p,points,poly_lines);
    //arrange_lines_by_x_coordinate(poly_lines);

    min_max_x = get_min_max_x(points);
    min_max_y = get_min_max_y(points);

    for (int y = min_max_y.first; y < min_max_y.second; y+=margin){
        pair<Point,Point> y_line {{min_max_x.first,y},{min_max_x.second,y}};
        Point ignored_point{0, 0};
        vector<int> intersections_for_this_y;// {0};

        for (auto& poly_line : poly_lines){
            if(!line_segment_intersect(poly_line.first, poly_line.second,
                                        y_line.first,y_line.second, ignored_point)){
                continue;
            }

            int x_intersection = calc_inersection(poly_line,y_line).x;

            intersections_for_this_y.push_back(x_intersection);

        }

       const size_t start = intersections_for_this_y.size() % 2  == 0 ? 1
                    : intersections_for_this_y.front() == intersections_for_this_y[1]
                    ? 2 : 1;

        for (size_t i = start; i < intersections_for_this_y.size(); i+=2){
            int first_x = intersections_for_this_y[i-1];
            int second_x = intersections_for_this_y[i];

            if (first_x == second_x)
                continue;

            Point first {first_x,y};
            Point second {second_x,y};

            result.push_back({first,second});
        }
    }

    return result;
}

Striped_closed_polyline::Striped_closed_polyline(std::initializer_list<Point> p) :
    Closed_polyline(p){
    auto stiped_lines_coordinates = calculate_striped_lines_coordinates_poly(p);

    for (auto& line_coordinates : stiped_lines_coordinates)
        this->lines.add(line_coordinates.first, line_coordinates.second);

}

void Striped_closed_polyline::draw_specifics(Painter& painter) const {
    Closed_polyline::draw_specifics(painter);
    lines.draw_specifics(painter);
}


struct Corners {
    Corners(int ww, int hh, Point p, int size_corner) : size_corner(size_corner){
        ltop_p.first = p;
        ltop_p.second = p;
        ltop_p.first.x += size_corner;
        ltop_p.second.y += size_corner;

        rtop_p.first = p;
        rtop_p.second = p;
        rtop_p.first.x += ww - size_corner;
        rtop_p.second.x += ww;
        rtop_p.second.y += size_corner;

        llow_p.first = p;
        llow_p.second = p;
        llow_p.first.y += hh - size_corner;
        llow_p.second.x += size_corner;
        llow_p.second.y += hh;

        rlow_p.first.y = llow_p.first.y;
        rlow_p.first.x = rtop_p.second.x;
        rlow_p.second.x = rtop_p.first.x;
        rlow_p.second.y = llow_p.second.y;
    }

    pair<Point,Point> ltop_p, rtop_p, llow_p, rlow_p;
    const int size_corner;
};

/*    f     f
 *  o x --- x o
 * sx         xs
 *  |         |
 *  |         |
 *  |         |
 * fx         xf
 *  o x --- x o
 *    s     s
 */


Rounded::Rounded(Point p, int ww, int hh){
    const int size_corner = 20; //pixel

    Corners corners(ww,hh,p,size_corner);

    sides.add(corners.ltop_p.first,corners.rtop_p.first);
    sides.add(corners.rtop_p.second,corners.rlow_p.first);
    sides.add(corners.rlow_p.second,corners.llow_p.second);
    sides.add(corners.ltop_p.second,corners.llow_p.first);

    //int count_circle_px = pi*size_corner*2;
    vector<Point> r_p {{corners.ltop_p.first.x,corners.ltop_p.first.y + size_corner},
                      {corners.rtop_p.first.x,corners.rtop_p.first.y + size_corner},
                      {corners.rlow_p.first.x - size_corner,corners.rlow_p.first.y},
                      {corners.llow_p.first.x + size_corner,corners.llow_p.first.y}};

    rounded_corners.push_back(make_unique<Arc>(r_p[0],
                                               size_corner,size_corner,
                                               90,90));
    rounded_corners.push_back(make_unique<Arc>(r_p[1],
                                               size_corner,size_corner,
                                               0,90));
    rounded_corners.push_back(make_unique<Arc>(r_p[2],
                                               size_corner,size_corner,
                                               270,90));
    rounded_corners.push_back(make_unique<Arc>(r_p[3],
                                               size_corner,size_corner,
                                               180,90));
}

void Rounded::draw_specifics(Painter& painter) const {
    sides.draw_specifics(painter);

    for(auto& corner : rounded_corners)
        corner->draw_specifics(painter);
}

void Rounded::move(int x, int y) {
    sides.move(x,y);

    for(auto& corner : rounded_corners)
        corner->move(x,y);
}

void create_board(vector<unique_ptr<Shape>>& shapes, Point pp, int size_board ){
    const int count_rect = 8;
    const int ww = size_board / count_rect;

    for (int i = 0; i < count_rect; ++i){
        for(int j = 0; j < count_rect; ++j){
            Point location = pp;

            location.x += size_board/count_rect * j;
            location.y += size_board/count_rect * i;

            shapes.push_back(make_unique<Rectangle>(location,ww,ww));

            const int last_index = shapes.size();
            const int offset = i % 2;
            Color col = (i*count_rect + j + offset) % 2 == 0 ? Color::black : Color::yellow;
            shapes[last_index-1]->set_fill_color(col);

            std::cout << "index: " << i << " " << j
                      << " coord: " << location.x << " " << location.y << endl;
        }
    }
}

void create_checkers(Vector_ref<Shape>& shapes, int size_board){
    const int count_rect = static_cast<int>(sqrt(shapes.size()));
    const int size_rect = size_board / count_rect;
    const int size_checker = static_cast<int>(lround(size_rect / 2 * 0.8));

    for (int i = 0; i < count_rect; ++i)
        for (int j = 0; j < count_rect; ++j){
            const int current_rect_index = i*count_rect + j;

            if (shapes[current_rect_index].fill_color().as_int() != Color::black)
                continue;

            Point current_coord = shapes[current_rect_index].point(0);
            current_coord.x += size_rect / 2;
            current_coord.y += size_rect / 2;

            shapes.push_back(make_unique<Circle>(current_coord,size_checker));
            const int last_el_ind = shapes.size() - 1;
            shapes[last_el_ind].set_fill_color(Color::blue);
        }
}

void create_checker_on_last_rect(vector<unique_ptr<Shape>>& shapes, int size_board, Color color){
    const int count_rect = static_cast<int>(sqrt(shapes.size()));
    const int size_rect = size_board / count_rect;
    const int size_checker = static_cast<int>(lround(size_rect / 2 * 0.8));


    Point current_coord = shapes[shapes.size()-1]->point(0);
    std::cout << "index: last"
              << " coord: " << current_coord.x << " " << current_coord.y << endl;

    current_coord.x += size_rect / 2;
    current_coord.y += size_rect / 2;

    shapes.push_back(make_unique<Circle>(current_coord,size_checker));
    const int last_el_ind = shapes.size() - 1;
    shapes[last_el_ind]->set_fill_color(color);

    std::cout << "index: last"
              << " coord: " << current_coord.x << " " << current_coord.y << endl;



}

Group::Group(bool is_checkers, Point pp, int size_board) : size_board(size_board){
    if (!is_checkers)
        return;

    create_board(shapes,pp,size_board);
    //create_checkers(shapes,size_board);
    create_checker_on_last_rect(shapes,size_board,Color::white);
}

void Group::move_checker_left(){
    const int count_rect = static_cast<int>(sqrt(shapes.size()));
    const int size_rect = size_board / count_rect;

    const int checker_index = shapes.size() - 1;
    shapes[checker_index]->move(-size_rect,-size_rect);
}
void Group::move_checker_right(){
    const int count_rect = static_cast<int>(sqrt(shapes.size()));
    const int size_rect = size_board / count_rect;

    const int checker_index = shapes.size() - 1;
    shapes[checker_index]->move(+size_rect,-size_rect);
}

void Group::move(int dx, int dy){
    for(auto& el : this->shapes)
        el->move(dx,dy);
}
void Group::draw_specifics(Painter& painter) const{
    for(auto& el : this->shapes)
        el->draw(painter);
}

Pseudo_window::Pseudo_window(Point pp, int ww, int hh, const string label){

    const int radius_button = 5;
    const int size_top_field = 20;

    this->elements.add_shape(make_unique<Rounded>(pp,ww,hh));
    this->elements.add_shape(make_unique<Text>(Point{pp.x + 3*ww/4, pp.y + 4}, label));


    this->elements.add_shape(make_unique<Circle>(Point{pp.x + 15, pp.y + radius_button + 5}, radius_button));
    this->elements.set_fill_color_last_el(Color::red);

    this->elements.add_shape(make_unique<Circle>(Point{pp.x + 30, pp.y + radius_button + 5}, radius_button));
    this->elements.set_fill_color_last_el(Color::yellow);

    this->elements.add_shape(make_unique<Circle>(Point{pp.x + 45, pp.y + radius_button + 5}, radius_button));
    this->elements.set_fill_color_last_el(Color::green);


    this->elements.add_shape(make_unique<Line>(Point{pp.x,pp.y+size_top_field}, Point{pp.x+ww,pp.y+size_top_field}));

    this->elements.add_shape(make_unique<Image>(Point{pp.x + 10, pp.y + size_top_field*2}, "image2.PNG"));


}

void Pseudo_window::move(int dx, int dy){
    elements.move(dx,dy);
}

void Pseudo_window::draw_specifics(Painter& painter) const{
    elements.draw_specifics(painter);
}

void Binary_tree::move(int dx, int dy){
    if (levels == 0) return;

    node_shape->move(dx,dy);
    label_node->move(dx,dy);

    if (levels == 1) return;

    lr_lines->move(dx,dy);
    left_node->move(dx,dy);
    right_node->move(dx,dy);
}

void Binary_tree::draw_specifics(Painter& painter) const {
    if (levels == 0) return;

    node_shape->draw(painter);
    label_node->draw_specifics(painter);

    if (this->levels == 1) return;

    lr_lines->draw_specifics(painter);
    left_node->draw_specifics(painter);
    right_node->draw_specifics(painter);
}


Binary_tree::Binary_tree(size_t ll, const string& label, Point p,
                         const Node_shape_factory& node_factory) : levels(ll) {
    int step_xy = default_size_node * 2;
    if (ll == 0)
        return;


    label_node = make_unique<Text>(p,label);
    node_shape = node_factory.create_node(p,default_size_node);

    if (ll == 1) return;

    Point left {p.x - step_xy, p.y + step_xy};
    Point right {p.x + step_xy, p.y + step_xy};

    lr_lines = make_unique<Lines>(initializer_list<Point>{p,left,p,right});

    left_node = make_unique<Binary_tree>(levels-1,label,left,node_factory);
    right_node = make_unique<Binary_tree>(levels-1,label,right,node_factory);
}


void ex_1(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex1. "};

    Smiley sm (zero_point,21);
    sm.set_color(Color::white);

    Frowny fr (zero_point,50);
    fr.set_color(Color::dark_green);
    fr.move(100,100);



    win.attach(sm);
    win.attach(fr);
    win.wait_for_button();
}

void ex_4(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex4. Immobile circle"};

    Immobile_Circle imc {zero_point,32};
    imc.set_fill_color(Color::dark_blue);


    win.attach(imc);
    win.wait_for_button();
}

void ex_5(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex5. Striped_rectangle"};

    Striped_rectangle s_rec {{100,100}, {200,200}};
    s_rec.set_color(Color::white);

    win.attach(s_rec);
    win.wait_for_button();
}

void ex_6(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex6. Striped_circle"};

    Striped_circle s_cir {{200,200},100};
    s_cir.set_color(Color::white);

    win.attach(s_cir);
    win.wait_for_button();
}

void ex_7(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex6. Striped_polyline"};

    Striped_closed_polyline scp {{100,400},{200,150},{300,550},{350,50},{550,300}};
    Striped_closed_polyline scp1 {
        {250,250},{350,200},{450,250},{400,350},{300,350}
    };
    Striped_closed_polyline scp2 {
        {100,100},{200,80},{300,120},{320,200},{220,240},{120,180}
    };
    Striped_closed_polyline scp3 {
        {150,400},{250,300},{350,420},{300,500},{200,470}
    };

    Striped_closed_polyline scp4 {
        {500,100},{650,100},{650,250},{575,200},{500,250}
    };
    Striped_closed_polyline scp5 {
        {50,50},{750,80},{700,500},{400,580},{100,450}
    };
    Striped_closed_polyline scp6 {
        {400,100},{450,250},{600,250},{475,350},
        {525,500},{400,400},{275,500},{325,350},
        {200,250},{350,250}
    };
    Striped_closed_polyline scp7 {
        {700,400},{730,420},{710,450},{680,440}
    };
    Striped_closed_polyline scp8 {
        {100,550},{200,520},{300,560},{400,530},
        {500,570},{600,540},{700,580}
    };
    Striped_closed_polyline scp9 {
        {600,300},{750,450},{550,500}
    };
    Striped_closed_polyline scp10 {
        {300,150},{450,120},{520,200},{480,280},
        {520,360},{400,420},{300,350},{260,250}
    };

win.attach(scp4);

win.attach(scp1);
win.attach(scp2);

win.attach(scp3);
  //win.attach(scp5);

  win.attach(scp6);
   win.attach(scp7);
    win.attach(scp8);
    win.attach(scp9);
   // win.attach(scp10);
  win.attach(scp);
    win.wait_for_button();
}

void ex_8(){

    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex8. Regular octagon"};

    Octagon oct {{200,200}, 100};
    oct.set_color(Color::white);
    oct.move(100,100);
    oct.set_fill_color(Color::green);

    win.attach(oct);
    win.wait_for_button();
}

void ex_9(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex9. Rounded"};

    Rounded rounded ({300,200},300,150);
    rounded.move(50,100);
    rounded.set_color(Color::blue);


    win.attach(rounded);
    win.wait_for_button();
}

void ex_10(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex10. class Box"};

    Box box {{300,100}, 300, 50};
    box.move(100,0);
    box.set_fill_color(Color::blue);

    win.attach(box);
    win.wait_for_button();

}

void ex_11(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex11. class Group"};

    Group gr{true};
    gr.move_checker_left();
    gr.move_checker_right();


    gr.add_shape(make_unique<Rounded>(Point{300,200},300,150));
    win.attach(gr);
    win.wait_for_button();

}

void ex_12(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex12. Pseudo_window"};

    Pseudo_window ps {{20,20}, 800, 600, "Pseudo_win"};
    ps.move(300,500);

    win.attach(ps);
    win.wait_for_button();

}

void ex_13(){
        Application app;
        Simple_window win {zero_point,1920,1080,"ch12_ex13. Binary_tree class"};

        Circle_node_factory c;
        Binary_tree bin {8,"l",zero_point,c};
        bin.move(100,-50);


        win.attach(bin);
        win.wait_for_button();

}

void ex_14(){
    Application app;
    Simple_window win {zero_point,1920,1080,"ch12_ex14. Binary_tree class"};

    Circle_node_factory c;
    Rectangle_node_factory r;
    Triangle_node_factory t;

    Binary_tree bin {8,"v2",zero_point,c};
    Binary_tree bin_r {5,"v2", {800,100},r};
    Binary_tree bin_t {8, "triangle", {1000,100},t};

    bin.move(100,-50);


    win.attach(bin);
    win.attach(bin_r);
    win.attach(bin_t);
    win.wait_for_button();
}
}
