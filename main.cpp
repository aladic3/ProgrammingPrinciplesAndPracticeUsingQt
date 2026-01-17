//#include "Chapter_10/drill.h"
#include "Chapter_10/Ex1_4.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ex1_4::ex3();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
