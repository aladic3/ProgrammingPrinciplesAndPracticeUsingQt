
#include "Chapter_13/drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch13::exercises::ex_6_9();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
