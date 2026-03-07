#ifndef DRILL_EX_H
#define DRILL_EX_H
#include <utility>

#include "../base.h"

namespace ch13::drill{
    constexpr pair age_range {0,150};

    void validate_age(int);
    void validate_name(const pair<string,string>&);
    void validate_name(const string&);

    struct Person {
        Person()= default;
        Person(const pair<string,string>& nn, int aa) : nname(nn), aage(aa)
            {validate_age(aa), validate_name(nn);}

        [[nodiscard]] const string& first_name() const { return nname.first;}
        [[nodiscard]]const string& second_name() const { return nname.second;}
        [[nodiscard]] int age() const {return aage;}

        void set_names(const pair<string,string>& nn) { validate_name(nn); nname = nn;}
        void set_age(int a) { validate_age(a); aage = a;}
    private:
        pair<string,string> nname;
        int aage = 0;
    };

    istream& operator>> (istream& is, Person& person);
    ostream& operator<< (ostream& os, const Person& person);

    void graphing_drill();
    void class_definition_drill();
}


#endif // DRILL_EX_H
