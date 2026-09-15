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

namespace ch18
{
    void play_game();
}

namespace ch18::game_gui
{
    inline int dm = 50; // default margin
    inline int ds = 30; // default size

    constexpr int boxes_x = 200;
    constexpr int boxes_y = 100;

    struct Room_meta
    {
        Room_meta(game::Room* r);
        game::Room* room;
        int number;
        Color color = Color::black;
        std::string msg;
    };


    struct Room : Shape
    {
        Room(Point center, int room_number, int size);
        void move(int dx, int dy) override;
        void set_number(int n);
        void set_inscription(const Room_meta&);
        void set_game_over();

    private:

        void draw_specifics(Painter& painter) const override;
        ch11::exercises::Regular_hexagon room_shape;
        Out_box r_number;
    };





    struct Cave_map : Shape
    {
        Cave_map(Point center, game::Antagonist* a);
        void draw_specifics(Painter& painter) const override;
        void update();

    private:
        Room r1;
        Room r2;
        Room r3;
        Room antagonist_shape_room;
        game::Antagonist* antagonist_;
    };

    struct Game_window : Simple_window {

        Game_window(game::Game&);


    private:
        void clear_last_input();
        void create_buttons();
        void input_callback();
        void update_map();
        void update_info(const std::string& additional_info = "");
        std::vector<int> shooting_input_process();
        int solo_number_input_process();

        game::Game& engine;
        string last_input_string;

        Cave_map map;
        Out_box game_info;
        Out_box last_input;
        Out_box game_msg;
        In_box input;
        Menu action_choice;

    };
}

#endif //PROGRAMMING_QT_GAME_GUI_H
