
#include "Chapter_13/drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch13::drill::class_definition_drill();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
