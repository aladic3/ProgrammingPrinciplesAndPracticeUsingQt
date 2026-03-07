#include "drill_ex.h"

namespace ch13::drill{

    void validate_age(int age) {
        if (age_range.first > age || age_range.second < age)
            error("Bad age");
    }

    void validate_name(const pair<string,string>& name) {
        validate_name(name.first);
        validate_name(name.second);
    }

    void validate_name(const string& name) {
        constexpr string err_msg {"bad name"};

        if (name.empty()) error(err_msg);

        for (const auto ch : name)
            if (std::ispunct(ch) || isdigit(ch))
                error(err_msg);
    }

    // name first without separator
    istream& operator>> (istream& is, Person& person) {
        int age;
        pair<string,string> name;

        is.exceptions(is.exceptions() | std::ios::failbit | ios::badbit);
        is >> name.first >> name.second >> age;

        person.set_age(age);
        person.set_names(name);

        return is;
    }
     ostream& operator<< (ostream& os, const Person& person) {
        return  os << person.first_name() << ' ' << person.second_name() << ' '
            << person.age() << endl;
    }

    void input_persons_to_vector(vector<Person>& persons, int count_persons) {
        for (int i  = 0; i < count_persons; ++i) {
            Person pp;
            cout << "Enter name and age: ";
            cin >> pp;
            persons.push_back(pp);
        }
    }

    void print_persons_to_vector(const vector<Person>& persons) {
        for (auto& p : persons)
            cout << p;
    }


    void graphing_drill(){
        const std::function<double(double)> one = [](double){return 1;};
        const std::function<double(double)> slope = [](double x){return x*0.5;};
        const std::function<double(double)> square = [](double x){return x*x;};
        const std::function<double(double)> cos = [](double x){return std::cos(x);};
        const std::function<double(double)> slope_cos = [&](double x){return cos(x)+slope(x);};



        constexpr int x_max = 600;
        constexpr int y_max = 600;
        constexpr int xya_length = 400;
        constexpr int xya_scale = 20;
        constexpr int xya_count_notches = xya_length / xya_scale;
        constexpr pair<int,int> range {-10,11}; //min, max
        constexpr int count_points = 400;

        constexpr string xy_axis_label = "1 == 20 pixels";
        constexpr Point cross_point {300,300};
        const Color axes_color {Color::red};

        Application app;
        Simple_window win {zero_point,x_max,y_max,"ch13. Graphing drill"};

        Axis xa {Axis::x,{0,cross_point.y},x_max,xya_count_notches,xy_axis_label};
        Axis ya {Axis::y,{cross_point.x,cross_point.y*2},y_max,xya_count_notches};

        Function f_one {one,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_slope {slope,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_square {square,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_cos {cos,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};
        Function f_slope_cos {slope_cos,range.first,range.second,cross_point,count_points,xya_scale,xya_scale};


        Text label_f_slope {f_slope.point(0),"0.5x"};

        xa.set_color(axes_color);
        ya.set_color(axes_color);
        ya.label.move(-150,200);
        xa.label.move(150,0);

        f_cos.set_color(Color::blue);
        f_slope_cos.set_color(Color::dark_cyan);

        win.attach(f_slope_cos);
        win.attach(f_cos);
        win.attach(label_f_slope);
        win.attach(f_slope);
        win.attach(f_square);
        win.attach(f_one);
        win.attach(xa);
        win.attach(ya);
        win.wait_for_button();
    }
    void class_definition_drill(){
        constexpr pair<string,string> name{"Kirill", "Danielko"};
        constexpr int age = 30;
        vector<Person> persons;

        Person person {name, age};

        cout << person;
        cout << "Enter name and age: ";
        cin >> person;
        cout << person;

        input_persons_to_vector(persons,3);
        print_persons_to_vector(persons);




    }
}
