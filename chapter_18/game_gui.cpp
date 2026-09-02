//
// Created by Dmytrenko Kyrylo on 21.08.2026.
//

#include "game_gui.h"

#include "PPP/GUI.h"

namespace ch18::game_gui
{


    Room::Room(Point center, int room_number, int size) :  room_shape(center,size),
    r_number(center, to_string(room_number))
    {
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

    void Cave_map::update(int antagonist_room_number, const vector<int>&  next_rooms)
    {
        antagonist_r.set_number(antagonist_room_number);
        r1.set_number(next_rooms[0]);
        r2.set_number(next_rooms[1]);
        r3.set_number(next_rooms[2]);
    }

    Game_window::Game_window(game::Game& e) : Simple_window(zero_point,width_display_default,high_display_default,
                                 "hunt on wumpus"),
                                engine(e),
                                 game_info(Point{boxes_x + 200, boxes_y}, "game_info:"),
                                last_input(Point{boxes_x + 200, boxes_y-20}, "last_input:"),
                                game_msg(Point{boxes_x + 200, boxes_y+20}, "game_msg:"),
                                 input(Point{boxes_x, boxes_y},
                                       default_ww_button, default_hh_button,
                                       "input and press \"Enter\":", [this]() { input_callback(); }),
                                 action_choice(Point{boxes_x, boxes_y + default_hh_button * 2},
                                               default_ww_button, default_hh_button, Menu::Kind::vertical,
                                               "choice")
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


    }

    void Game_window::create_buttons()
    {
        std::function<void()> shooting = [this]()
        {
            game_msg.put("shoot?");
            this ->engine.shoot_antagonist(shooting_input_process());
        };

        action_choice.attach(make_unique<Button>(Point{100,100},0,0,"shoot",[=]{shooting();}));
    }


    void Game_window::input_callback()
    {
        if (input.last_result() == In_box::accepted) {
            last_input_string = input.last_string_value();
            last_input.put(last_input_string);
        }



        input.clear_last_result();
    }

    std::vector<int> Game_window::shooting_input_process() // TODO test
    {
        if (engine.get_arrow_capacity() == 0) {
            game_msg.put("You can't shooting, capacity arrows is 0! But you can move)");
            return std::vector<int>{};
        }


       game_msg.put("Enter how much rooms arrow must reached (less then 5)");

        while (last_input_string.empty())
            this->timer_wait(500);


          int count_rooms_reaching = [&]()
        {
                std::istringstream is (last_input_string);
                int result;
                is >> result;
                last_input_string.clear();
                return result;
        }.operator()();



       std::vector<int> trace(count_rooms_reaching);

        game_msg.put("Inputting trace...");
        this->timer_wait(500);
        for (int i = 0; i < count_rooms_reaching; ++i) {
               game_msg.put(std::format("Enter trace[{}]",i));

               // TODO infinity loop... mb "wait for button"
                while (last_input_string.empty())
                    this->timer_wait(500);

                std::istringstream is (last_input_string);
               is >> trace[i];
                last_input_string.clear();

         }

        return trace;
    }
}
