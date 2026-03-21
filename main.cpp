
#include "Chapter_14/drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch14::drill::drill();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
