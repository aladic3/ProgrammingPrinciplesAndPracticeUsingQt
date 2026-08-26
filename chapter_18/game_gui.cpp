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



    Cave_map::Cave_map(Point center, int antagonist_room_number, vector<int> next_rooms) :
     r1(Point{center.x + dm,center.y + dm}, next_rooms[0],ds),
     r2(Point{center.x - dm,center.y + dm},next_rooms[1],ds),
     r3(Point{center.x,center.y - dm}, next_rooms[2],ds),
    antagonist_r(center,antagonist_room_number,ds)   {}

    void Cave_map::update(int antagonist_room_number, vector<int> next_rooms)
    {
        antagonist_r.set_number(antagonist_room_number);
        r1.set_number(next_rooms[0]);
        r2.set_number(next_rooms[1]);
        r3.set_number(next_rooms[2]);
    }

    Game_window::Game_window() : Simple_window(zero_point,width_display_default,high_display_default,
                                 "hunt on wumpus"),
                                 game_info(Point{boxes_x - 100, boxes_y}, "TODO"),
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
        /*create_buttons();
        menu.show();
        update_out_box();*/
    }


    void Game_window::input_callback()
    {
        if (input.last_result() == In_box::accepted) {
            last_input_string = input.last_string_value();
        }

        input.clear_last_result();
    }
}
