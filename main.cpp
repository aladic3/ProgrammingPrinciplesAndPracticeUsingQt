//#include "Chapter_10/drill.h"
#include "Chapter_10/Ex1_4.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ex1_4::ex12_13(0.5,1.5,1,2);
    }catch(std::exception& ex){
        std::cerr << ex.what();
    }

}
