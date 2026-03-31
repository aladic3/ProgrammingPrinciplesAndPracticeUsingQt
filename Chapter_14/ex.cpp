//
// Created by Dmytrenko Kyrylo on 23.03.2026.
//
#include "drill_ex.h"
#include "PPP/GUI_private.h"

namespace ch14::exercises {
    ImageButton::ImageButton(Point xy, int w, int h, const string &label, Callback cb, const string &img_name)  :
      Button(xy, w, h,label, std::move(cb)),
      image(xy,img_name) {
        //image.set_mask({0,0},w,h);
        image.scale(w,h,false);
    }

    void ImageButton::attach(Window &window) {
        Button::attach(window);
        window.attach(image);
    }

    void ImageButton::move(int dx, int dy) {
        Button::move(dx, dy);
        image.move(dx,dy);
    }

    My_window::My_window(Application &application, Point xy, int w, int h, const string &title):
    Simple_window(xy,w,h,title),
    app(&application),
    quit_button(Point{w-60,30},30,20,"quit",[&]{quit();}) {
        attach(quit_button);
    }

    void My_window::quit() {
        this->get_impl().end_button_wait();

        app->quit();
        delete this;
    }

    Checkerboard_window::Checkerboard_window(Application &application, Point xy, int w, int h, const string &title) :
                My_window(application,xy,w,h,title),
                out_box(Point{10, 40}, "Coordinates:"),
                xy_coordinates_input({100,20},50,15,"example:'x,y'. coordinates input:",[this]{input_coordinates();}),
                wh_input({100,50},50,15,"example:'w,h'. sizes input:",[this]{input_size();})
                 {
        this->attach(out_box);
        this->attach(wh_input);
        this->attach(xy_coordinates_input);
        wh_input.hide_buttons();
        wh_input.show();

        xy_coordinates_input.hide_buttons();
        xy_coordinates_input.show();
        create_checkerboard_buttons(Point{100,100});
        create_shapes_buttons(Point{500,200});


    }

    Point Checkerboard_window::get_inputted_xy() const {
        return this->inputted_xy;
    }

    Shape* Checkerboard_window::get_last_shape() const {
        if (this->own_shapes.empty())
            return nullptr;

        return own_shapes.back().get();
    }


    void Checkerboard_window::input_coordinates() {
        if (this->xy_coordinates_input.last_result() != In_box::accepted) {
            this->xy_coordinates_input.clear_last_result();
            return;
        }

        istringstream is(this->xy_coordinates_input.last_string_value());
        int x,y;
        char ch;

        if (!(is >> x >> ch >> y))
            error("Bad input: x,y values");

        this->inputted_xy = {x,y};
    }

    void Checkerboard_window::input_size() {
        if (this->wh_input.last_result() != In_box::accepted) {
            this->xy_coordinates_input.clear_last_result();
            return;
        }

        istringstream is(this->wh_input.last_string_value());
        int w,h;
        char ch;

        if (!(is >> w >> ch >> h))
            error("Bad input: x,y values");

        this->inputted_size = {w,h};

    }

    void Checkerboard_window::create_square() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");

        this->own_shapes.emplace_back(make_unique<Rectangle>(inputted_xy,inputted_size.first,inputted_size.second));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_circle() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");

        this->own_shapes.emplace_back(make_unique<Circle>(inputted_xy,inputted_size.first));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_equilateral_triangle() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");
        using Triangle = ch11::exercises::Right_triangle;

        this->own_shapes.emplace_back(make_unique<Triangle>(inputted_xy,inputted_size.first,inputted_size.second));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_hexagon() {
        if (inputted_xy.x == -1 || inputted_size.first == -1)
            error("must enter coordinates and sizes!");
        using Hexagon = ch11::exercises::Regular_hexagon;

        this->own_shapes.emplace_back(make_unique<Hexagon>(inputted_xy,inputted_size.first));
        attach(*own_shapes.back());
    }

    void Checkerboard_window::create_shapes_buttons(Point origin) {
        Point current = origin;
        int margin = 5;
        int width_button = 50;
        int height_button = 30;

        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Circle",[this]
                        {create_circle();}));
        current.y+=height_button+margin;

        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Triangle",[this]
                        {create_equilateral_triangle();}));
        current.y+=height_button+margin;
        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Hexagon",[this]
                        {create_hexagon();}));
        current.y+=height_button+margin;
        this->checkerboard_buttons.emplace_back(
                    make_unique<Button>(current,width_button,height_button,"Square",[this]
                        {create_square();}));

        for (auto& el : checkerboard_buttons)
            attach(*el);
    }

    void Checkerboard_window::create_checkerboard_buttons(Point origin) {
        Point current = origin;
        int margin = 5;
        int width_button = 50;
        int height_button = 30;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ostringstream name;
                int iterator_2d = j + i*4;

                name << iterator_2d;

                this->checkerboard_buttons.emplace_back(
                    make_unique<ImageButton>(current,width_button,height_button,name.str(),[this,iterator_2d]
                        {press_button_ex3(iterator_2d);}));

                attach(*this->checkerboard_buttons.back()); // attach to window

                current.x += width_button + margin;
            }
            current.x = origin.x;
            current.y += height_button + margin;
        }

    }

    void Checkerboard_window::press_button_ex2(int iterator) {
        checkerboard_buttons[last_index_checkerboard]->get_impl().widget->setStyleSheet("background-color: grey;"); // reset last button

        auto button = &checkerboard_buttons[iterator];
        print_coordinates((*button)->loc);
        (*button)->get_impl().widget->setStyleSheet("background-color: blue;");
        last_index_checkerboard = iterator;
    }

    void Checkerboard_window::press_button_ex3(int iterator) {
        auto& button = *checkerboard_buttons[iterator];
        button.move(randint(-100,100),randint(-100,100));
        print_coordinates(button.loc);
    }


    void Checkerboard_window::print_coordinates(Point p) {
        ostringstream os;
        os << p.x << "," << p.y;
        out_box.data.set_label(os.str());
    }

    Watch_face::Watch_face(Point origin, int radius) :
    properties(origin,radius){
        createClockFace();
        createHourHand();
        createMinuteHand();
        createSecondHand();
        createTickMarks();

        calculate_hour_hand_coordinate();

        update_time_from_std();

        set_minute_hand();
        set_second_hand();
        set_hour_hand();
    }

    void Watch_face::draw_specifics(Painter &painter) const {
        clockFace->draw(painter);
        hourHand->draw(painter);
        minuteHand->draw(painter);
        secondHand->draw(painter);

        for (auto& el : tickMarks)
            el->draw(painter);
    }

    void Watch_face::move(int dx, int dy) {
        clockFace->move(dx,dy);
        hourHand->move(dx,dy);
        minuteHand->move(dx,dy);
        secondHand->move(dx,dy);

        for (auto& el : tickMarks)
            el->move(dx,dy);

    }

    void Watch_face::increment_seconds_by_one() {
        ++properties.current_second;
        if (properties.current_second == 60) {
            properties.current_second = 0;
            ++properties.current_minute;
        }

        if (properties.current_minute == 60) {
            properties.current_minute = 0;
            ++properties.current_hour;
        }

        if (properties.current_hour == 24)
            properties.current_hour = 0;

        if (properties.current_minute % 5 == 0)
            update_time_from_std();

        this->set_hour_hand();
        this->set_minute_hand();
        this->set_second_hand();

    }

    void Watch_face::set_minute_hand(int minutes) {
        if (minutes > 59 || minutes < 0) error("Bad minutes value");
        properties.current_minute = minutes;

        this->minuteHand->set_point(1,tickMarks[minutes]->point(0));
    }

    void Watch_face::set_second_hand(int second) {
        if (second > 59 || second < 0) error("Bad seconds value");
        properties.current_second = second;

        this->secondHand->set_point(1,tickMarks[second]->point(0));
    }

    void Watch_face::set_hour_hand(int hour) {
        if (hour > 23 || hour < 0) error("Bad hours value");
        properties.current_hour = hour;

        hourHand->set_point(1,calculate_hour_hand_coordinate());
    }

    void Watch_face::update_time_from_std() {
        auto now = std::chrono::system_clock::now();
        std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&t_c);

        int h = now_tm->tm_hour;
        int m = now_tm->tm_min;
        int s = now_tm->tm_sec;

        properties.current_minute=m;
        properties.current_second=s;
        properties.current_hour=h;

        /*for (int i = 0; i < 2; ++i)
            this->increment_seconds_by_one();*/


    }

    Point Watch_face::calculate_hour_hand_coordinate() {
        int hour = properties.current_hour;

        hour = hour >= 12 ? hour - 12 : hour;

        int tick_position = hour * 5; // 0 ... 60
        tick_position += properties.current_minute / 12;

        Point edge_point = tickMarks[tick_position]->point(0);

        double t = static_cast<double>(properties.long_hour_hand)/properties.radius;

        return get_segment_coordinate(properties.center,edge_point,t);
    }

    void Watch_face::createClockFace() {
        clockFace = make_unique<Circle>(properties.center,properties.radius);
        clockFace->set_fill_color(properties.face_color);
    }

    void Watch_face::createHourHand() {
        hourHand = make_unique<Line>(properties.center, Point{properties.center.x,properties.center.y-properties.long_hour_hand});
        hourHand->set_color(properties.hour_color);
        hourHand->set_style(Line_style(Line_style::solid,properties.width_hour));
    }

    void Watch_face::createMinuteHand() {
        minuteHand = make_unique<Line>(properties.center, Point{properties.center.x,properties.center.y-properties.long_minute_hand});
        minuteHand->set_color(properties.minute_color);
        minuteHand->set_style(Line_style(Line_style::solid,properties.width_minute));
    }

    void Watch_face::createSecondHand() {
        secondHand = make_unique<Line>(properties.center, Point{properties.center.x,properties.center.y-properties.long_second_hand});
        secondHand->set_color(properties.second_color);
        secondHand->set_style(Line_style(Line_style::solid,properties.width_second));
    }

    void Watch_face::createTickMarks() {

        const Point center_point = properties.center;
        const Point start_point {center_point.x,center_point.y-properties.radius};

        for (int i = 0; i < 60; ++i) {

            const int long_tick = i % 5 ? properties.long_tick : properties.long_tick + 4;
            const int width_tick = i % 5 ? properties.width_tick : properties.width_tick + 2;
            double t = static_cast<double>(properties.radius-long_tick)/properties.radius;

            const double angle = (pi / 30) * i;
            Point current_point_A = get_turn_coordinate(center_point,start_point, angle); // edge
            Point current_point_B = get_segment_coordinate(center_point,current_point_A,t);

            tickMarks.emplace_back(make_unique<Line>(current_point_A,current_point_B));
            tickMarks.back()->set_color(properties.ticks_color);
            tickMarks.back()->set_style(Line_style(Line_style::solid,width_tick));
        }

    }

    void Watch_face::set_minute_hand() {
        this->minuteHand->set_point(1,tickMarks[properties.current_minute]->point(0));
    }

    void Watch_face::set_second_hand() {
        this->secondHand->set_point(1,tickMarks[properties.current_second]->point(0));
    }

    void Watch_face::set_hour_hand() {
        hourHand->set_point(1,calculate_hour_hand_coordinate());
    }

    Point Watch_face::get_turn_coordinate(Point center, Point north, double angle) {
        double dx = north.x - center.x;
        double dy = north.y - center.y;


        int x_new = static_cast<int>(lround(dx * cos(angle) - dy * sin(angle)));
        int y_new =static_cast<int>(lround( dx * sin(angle) + dy * cos(angle)));


        Point result{};
        result.x = center.x + x_new;
        result.y = center.y + y_new;

        return result;
    }

    Point Watch_face::get_segment_coordinate(Point center, Point edge_point, double t) {
        return Point(
            static_cast<int>(lround(center.x + t * (edge_point.x - center.x))),
            static_cast<int>(lround(center.y + t * (edge_point.y - center.y)))
        );

    }

    void Airplane_win::process()  {
       is_wait_ = !is_wait_;
    }

    Airplane::Airplane(Point origin, int radius) {
        const int count_plane_points = 30;
        const int size_airplane = 10;

        for (int i = 0; i < count_plane_points; ++i)
            this->fly_positions.push_back(Watch_face::get_turn_coordinate(origin,Point{origin.x,origin.y-radius},i*pi/(count_plane_points/2)));

        this->airplane = make_unique<Circle>(fly_positions.front(),size_airplane);
        airplane->set_fill_color(Color::blue);

        current_position = fly_positions.begin();


    }

    Shape & Airplane::get_airplane_shape() const{
        return *this->airplane;
    }

    void Airplane::next_fly_position() {
        Point current = *current_position;
        ++current_position;

        if (current_position == fly_positions.end())
            current_position = fly_positions.begin();

        Point next = *current_position;

        int dx = next.x - current.x;
        int dy = next.y - current.y;

        airplane->move(dx,dy);
    }

    Window_ex5::Window_ex5(Application &application, Point xy, int w, int h, const string &title) :
            next_location_button(Point{300,500},default_ww_button,default_hh_button,"next_loc",
                [this]{move_last_shape();}),
            win(application,xy,w,h,title)
    {
        win.attach(next_location_button);
    }

    void Window_ex5::attach(Shape &sh) {
        this->win.attach(sh);
    }

    void Window_ex5::wait_for_button() {
        this->win.wait_for_button();
    }

    void Window_ex5::move_last_shape() {
        auto last_sh = win.get_last_shape();
        Point new_coordinates = win.get_inputted_xy();

        if (last_sh == nullptr || new_coordinates.x == -1)
            return;

        Point current_coordinates = last_sh->point(0);

        int dx = new_coordinates.x - current_coordinates.x;
        int dy = new_coordinates.y - current_coordinates.y;

        last_sh->move(dx,dy);
    }

    void ex1() {
        Application app;
        My_window win{app,zero_point,1000,800,"Ex1"};
        Circle circle{{50,50},30};
        Rectangle rect {zero_point,100,200};
        win.attach(circle);
        win.wait_for_button();

        win.attach(rect);
        win.wait_for_button();

    }

    void ex2_4() {
        Application app;
        Checkerboard_window win{app,zero_point,1000,800,"Ex2"};
        Circle circle{{50,50},30};
        Rectangle rect {zero_point,100,200};
        win.attach(circle);
        win.wait_for_button();

        win.attach(rect);
        win.wait_for_button();
    }

    void ex5() {
        Application app;
        Window_ex5 win{app,zero_point,1000,800,"Ex5"};
        Circle circle{{50,50},30};
        Rectangle rect {zero_point,100,200};
        win.attach(circle);
        win.wait_for_button();

        win.attach(rect);
        win.wait_for_button();
    }

    void ex6() {
        Application app;
        My_window win{app,zero_point,1000,800,"Ex6"};

        Watch_face watch {Point{200,200},100};

        win.attach(watch);

        // ReSharper disable once CppDFAEndlessLoop
        while (true) {
            win.timer_wait(1000);
            watch.increment_seconds_by_one();
            win.draw();
        }
    }

      void ex7() {
        Application app;
        Airplane_win win{zero_point,1000,800,"Ex7"};
        Airplane airplane {Point{200,200},100};

        win.attach(airplane.get_airplane_shape());

        // ReSharper disable once CppDFAEndlessLoop
        while (true) {
            win.timer_wait(1);
            if (!win.is_wait())
                airplane.next_fly_position();
            //win.draw();

        }
    }

    void ex8() {
        ch8::ex14_15::test();
    }

}
