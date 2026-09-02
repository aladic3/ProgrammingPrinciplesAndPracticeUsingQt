//
// Created by Dmytrenko Kyrylo on 02.09.2026.
//

#include <QApplication>

#include "game_gui.h"
#include "game.h"

namespace ch18
{
    void play_game()
    {
        Application app;
        ch18::game::Game engine;
        ch18::game_gui::Game_window gui(engine);

        gui.wait_for_button();
    }
}
