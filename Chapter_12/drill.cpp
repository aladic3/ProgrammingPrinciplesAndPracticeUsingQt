#include "drill_ex.h"

namespace ch12::drill{
class B1{
public:
    virtual void vf() const { std::cout << "B1::vf\n";}
    void f() const { std::cout << "B1::f\n";}
    virtual void pvf() const =0;

};

class D1 : public B1{
public:
    void vf() const {std::cout << "D1::vf\n";}
    void f() const { std::cout << "D1::f\n";}
    void pvf() const {std::cout << "D1::pvf\n";}
};

class D2 : public D1 {
public:
    void pvf() const {std::cout << "D2::pvf\n";}
};

class B2 {
    virtual void pvf2() const = 0;

public:
    void pvf() {pvf2();}
};

class D21 : public B2, B1 {
    std::string str = "D21";

    void pvf2() const override {std::cout << std::format("{}::pvf from B2\n",str);}

public:
    void pvf() const override {std::cout << std::format("{}::pvf from B1\n",str);}
    void f(){pvf2();}

};

class D22 : public B2 {
    int field = 10;
    void pvf2() const override {std::cout << std::format("D22::pvf from B2. Field: {}\n",field);}

public:
    void f(){pvf2();}
};

void f(B2& arg){
    arg.pvf();
}

void virtual_func_drill(){
    //B1 b1;
    D1 d1;
    B1& ref_b = d1;
    D2 d2;
    D21 d21;
    D22 d22;


    f(d21);
    f(d22);
    d21.f();
    d21.pvf();

    d22.f();

    //b1.vf();
    //b1.f();

    d1.vf();
    d1.f();

    ref_b.vf();
    ref_b.f();
    ref_b.pvf();

    d2.f();
    d2.vf();
    d2.pvf();

}
}
