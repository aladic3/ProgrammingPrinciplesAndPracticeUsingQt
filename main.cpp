
#include "Chapter_12/drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch12::exercices::ex_4();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
