//
// Created by Dmytrenko Kyrylo on 20.08.2026.
//

#ifndef PROGRAMMING_QT_GAME_GUI_H
#define PROGRAMMING_QT_GAME_GUI_H
#include "Chapter_11/try_drill_ex.h"
#include "base.h"
#include <vector>
#include <span>
#include <set>

#include "game.h"
//#include "PPP/Simple_window.h"

namespace ch18::game_gui
{
    inline int dm = 50; // default margin
    inline int ds = 30; // default size

    constexpr int boxes_x = 100;
    constexpr int boxes_y = 20;




    struct Room : Shape
    {
        Room(Point center, int room_number, int size);
        void move(int dx, int dy) override;
        void set_number(int n);

    private:

        void draw_specifics(Painter& painter) const override;
        ch11::exercises::Regular_hexagon room_shape;
        Out_box r_number;
    };



    struct Cave_map : Shape
    {
        Cave_map(Point center, int antagonist_room_number, vector<int> next_rooms);
        void update(int antagonist_room_number, vector<int> next_rooms);

    private:
        Room r1;
        Room r2;
        Room r3;
        Room antagonist_r;
    };

    struct Game_window : Simple_window {

        Game_window(game::Game&);


    private:
        void create_buttons();
        void input_callback();
        std::vector<int> shooting_input_process();

        game::Game& engine;
        string last_input_string;


        Out_box game_info;
        Out_box last_input;
        Out_box game_msg;
        In_box input;
        Menu action_choice;

    };
}

#endif //PROGRAMMING_QT_GAME_GUI_H
