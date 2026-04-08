
#include "Chapter_14/drill_ex.h"
#include <iostream>


int main(int /*argc*/, char * /*argv*/[])
{
    try{
        ch14::exercises::ex10();
    }catch(std::exception& ex){
        std::cerr << ex.what();
    } catch (...) {
        std::cerr << "Uncaught error";
    }

}
