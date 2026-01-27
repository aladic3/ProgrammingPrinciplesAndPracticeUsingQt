
#include "Chapter_11/try_drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch11::_try::first_try();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
