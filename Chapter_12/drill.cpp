#include "drill_ex.h"

namespace ch12::drill{
class B1{
public:
    virtual void vf() const { std::cout << "B1::vf\n";}
    void f() const { std::cout << "B1::f\n";}

};

class D1 : public B1{
public:
    void vf() const {std::cout << "D1::vf\n";}
    void f() const { std::cout << "D1::f\n";}
};

void virtual_func_drill(){
    B1 b1;
    D1 d1;
    B1& ref_b = d1;

    b1.vf();
    b1.f();

    d1.vf();
    d1.f();

    ref_b.vf();
    ref_b.f();

}
}
