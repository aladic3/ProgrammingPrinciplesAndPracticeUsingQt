
#include "Chapter_11/try_drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch11::drill::do_drill();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
