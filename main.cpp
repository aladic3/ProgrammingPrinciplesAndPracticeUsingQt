
#include "chapter_18/game_gui.h"
#include <iostream>
#include <QApplication>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch18::play_game();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    } catch (...) {
        std::cerr << "Uncaught error";
    }

}
