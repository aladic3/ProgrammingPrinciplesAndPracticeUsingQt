
#include "Chapter_11/try_drill_ex.h"
//#include "Chapter_10/Ex1_4.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch11::exercises::ex11();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
