//
// Created by Dmytrenko Kyrylo on 21.08.2026.
//

#include "game_gui.h"

#include "PPP/GUI.h"

namespace ch18::game_gui
{


    Room::Room(Point center, int room_number, int size) :  room_shape(center,size),
    r_number(center, "")
    {
        r_number.put(room_number);
    }

    void Room::move(int dx, int dy)
    {
        room_shape.move(dx,dy);
        r_number.move(dx,dy);
        //Shape::move(dx, dy);
    }

    void Room::set_number(int n)
    {
        r_number.put(n);
    }

    void Room::set_game_over()
    {
        this->r_number.put("hell");
        this->set_color(Color::dark_red);
        this->r_number.set_color(Color::dark_yellow);
        this->set_fill_color(Color::red);
    }

    void Room::draw_specifics(Painter& painter) const
    {
        room_shape.draw_specifics(painter);
        r_number.draw_specifics(painter);
    }



    Cave_map::Cave_map(Point center, int antagonist_room_number, const vector<int>& next_rooms) :
     r1(Point{center.x + dm,center.y + dm}, next_rooms[0],ds),
     r2(Point{center.x - dm,center.y + dm},next_rooms[1],ds),
     r3(Point{center.x,center.y - dm}, next_rooms[2],ds),
    antagonist_r(center,antagonist_room_number,ds)   {}

    void Cave_map::draw_specifics(Painter& painter) const
    {
        this->antagonist_r.draw(painter);
        this->r1.draw(painter);
        this->r2.draw(painter);
        this->r3.draw(painter);
    }

    void Cave_map::update(int antagonist_room_number, const vector<int>&  next_rooms)
    {
        if (antagonist_room_number == game::hell_room.number_this)
            return antagonist_r.set_game_over();


        antagonist_r.set_number(antagonist_room_number);

        r1.set_number(next_rooms[0]);
        r2.set_number(next_rooms[1]);
        r3.set_number(next_rooms[2]);

    }

    Game_window::Game_window(game::Game& e) : Simple_window(zero_point,width_display_default,high_display_default,
                                 "hunt on wumpus"),
    engine(e),
    map(Point{500,500},engine.get_antagonist_room_number(),engine.get_next_antagonist_rooms()),
    game_info(Point{boxes_x + 200, boxes_y}, "game_info:"),
    last_input(Point{boxes_x + 200, boxes_y-20}, "last_input:"),
    game_msg(Point{boxes_x + 200, boxes_y+20}, "game_msg:"),
    input(Point{boxes_x, boxes_y},default_ww_button, default_hh_button,"input and press \"Enter\":", [this]() { input_callback(); }),
    action_choice(Point{boxes_x, boxes_y + default_hh_button * 2},default_ww_button, default_hh_button, Menu::Kind::vertical,"choice")
    {
        attach(input);
        input.hide_buttons();
        input.show();
        create_buttons();
        action_choice.show();
        attach(action_choice);
        attach(game_info);
        attach(last_input);
        attach(game_msg);
        attach(map);
        update_info();

    }

    void Game_window::clear_last_input()
    {
        last_input_string.clear();
        last_input.put("");
    }

    std::string string_from_vector(const std::vector<int>& vec)
    {
        std::string result;

        for (int a : vec)
            result.append(std::format("{} ", a));
        return result;
    }

    void Game_window::create_buttons()
    {
        std::function<void()> shooting = [this]()
        {
            game_msg.put("shoot?");
            std::vector<int> trace = this->engine.shoot_antagonist(shooting_input_process());

            update_map();
            update_info(std::format("Shot rooms: {}",string_from_vector(trace)));
        };

        std::function<void()> moving = [this]()
        {
            game_msg.put("moove...");
            if (!engine.move_antagonist(moving_input_process()))
                return game_msg.put("Moving to this number impossible");

            update_map();
            update_info();
        };

        action_choice.attach(make_unique<Button>(Point{100,100},0,0,"shoot",[=]{shooting();}));
        action_choice.attach(make_unique<Button>(Point{100,100},0,0,"moove",[=]{moving();}));
    }


    void Game_window::input_callback()
    {
        if (input.last_result() == In_box::accepted) {
            last_input_string = input.last_string_value();
            last_input.put(last_input_string);
        }



        input.clear_last_result();
    }

    void Game_window::update_map()
    {
        map.update(engine.get_antagonist_room_number(),engine.get_next_antagonist_rooms());
    }

    void Game_window::update_info(const std::string& additional_info)
    {
        std::string feeling;
        for (const std::string& el : engine.get_next_rooms_info_from_antagonist())
            feeling += std::format("{} ",el);
        game_info.put(std::format("{}. Arrow cap: {} ",engine.get_string_of_alive_mobs(), engine.get_arrow_capacity()));
        game_msg.put(feeling + " " + additional_info);

    }

    std::vector<int> Game_window::shooting_input_process() // TODO test
    {
        std::vector<int> empty_vector{};
        if (engine.get_arrow_capacity() == 0) {
            game_msg.put("You can't shooting, capacity arrows is 0! But you can move)");
            return empty_vector;
        }

        std::istringstream is (last_input_string);
        int temp;
        is >> temp;
        const int size_v = temp;

        if (size_v < 1 || size_v > 5)
            return empty_vector;

        std::vector<int> result;
        result.reserve(size_v);

        while (is >> temp)
            result.push_back(temp);

        if (static_cast<int>(result.size()) != size_v)
            return empty_vector;

        clear_last_input();
        return result;

    }

    int Game_window::moving_input_process()
    {
        if (last_input_string.empty()) return -1;

        std::istringstream is (last_input_string);
        int temp;
        is >> temp;
        clear_last_input();
        return temp;
    }
}
