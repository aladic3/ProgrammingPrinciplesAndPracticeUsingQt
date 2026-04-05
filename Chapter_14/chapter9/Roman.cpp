//
// Created by Dmytrenko Kyrylo on 07.01.2026.
//


#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "try_drill.h"

namespace ch9::ex21_22 {
    class Roman;
    struct Roman_helper;



    int roman_ch_to_int(char ch) {
        ch = static_cast<char>(std::toupper(ch));

        for (auto& pair: Roman_helper::basic_values)
            if (ch == pair.first)
                return pair.second;

        error("bad char when translate one char to roman int");
        return 999999;
    }

    char roman_int_to_ch(int r) {
        for (auto& pair: Roman_helper::basic_values)
            if (r == pair.second)
                return pair.first;

        error("bad int when translate one int to roman char");
        return 0;
    }

    bool is_good_subtraction(char current_roman, char last_roman) {
        auto current_roman_int = roman_ch_to_int(current_roman);
        auto last_roman_int = roman_ch_to_int(last_roman);
        auto ratio = current_roman_int / last_roman_int;

        // subtraction rules
        if (last_roman_int < current_roman_int && ratio != 10 && ratio != 5)
                return false;
        if (last_roman_int < current_roman_int && Roman_helper::non_repeatable_romans.find(last_roman) != string::npos)
                return false;

        return true;
    }

    bool is_good_repeating(char last_roman, char current_roman, int& count_repeat) {
        if (last_roman == current_roman && Roman_helper::non_repeatable_romans.find(current_roman) == string::npos)
            ++count_repeat;
        else if (last_roman == current_roman && Roman_helper::non_repeatable_romans.find(current_roman) != string::npos)
            return false;
        else
            count_repeat = 1;

        if (count_repeat > 3) // rule repeat max 3
            return false;

        return true;
    }

    bool is_roman(char current_roman) {
        if (Roman_helper::all_possible_romans.find(current_roman) == string::npos) // is roman
            return false;
        return true;
    }

    bool is_valid_roman_str(const std::string& roman_str) {
        int count_repeat = 1;
        char last_roman = roman_str.front();

        for (auto current_roman : roman_str.substr(1)) {
            current_roman = static_cast<char>(std::toupper(current_roman)); //normalized_current

            if (!is_roman(current_roman) || !is_good_repeating(last_roman,current_roman,count_repeat) ||
                !is_good_subtraction(current_roman,last_roman))
                    return false;

            last_roman = current_roman;
        }

        return true;
    }
    bool is_valid_roman_int(int roman_int) {
        return roman_int < 4000 && roman_int > 0;
    }
    int roman_str_to_int(const std::string& roman_str) {
        auto overall_roman = 0;
        auto current_roman_int = roman_ch_to_int(roman_str[0]);
        int next_roman_int = 0;

        for (auto el: roman_str.substr(1)) {
            next_roman_int = roman_ch_to_int(el);

            if (current_roman_int < next_roman_int)
                overall_roman -= current_roman_int;
            else
                overall_roman += current_roman_int;

            current_roman_int = next_roman_int;
        }

        overall_roman += current_roman_int;

        if (roman_int_to_str(overall_roman) != roman_str)
            error("bad input str roman!");

        return overall_roman;
    }
    std::string roman_int_to_str(int input_roman_int) {
        std::string result;
        int ra = input_roman_int;

        if (!is_valid_roman_int(ra))
            error("bad input int in roman translate");

        while (ra > 0)
            for (auto& roman_pair: Roman_helper::basic_values) {
                int diff_lower = Roman_helper::non_repeatable_romans.find(roman_pair.first) != string::npos
                                 ? roman_pair.second / 5: roman_pair.second / 10;
                int ratio = ra / roman_pair.second;
                int remainder = roman_pair.second % ra ;

                if (ratio > 0) {
                    ra-=roman_pair.second;
                    result+=roman_pair.first;
                    break;
                }

                if (remainder <= diff_lower && roman_pair.second / ra == 1) {
                    ra -= roman_pair.second - diff_lower;
                    result += roman_int_to_ch(diff_lower);
                    result += roman_pair.first;
                    break;
                }

            }

        return result;
    }

    bool is_inputted_by_string(const std::string& i_string, Roman& roman) {
        std::istringstream is {i_string};

        std::string input_str;
        is >> input_str;


        if (is_valid_roman_str(input_str)) {
            roman.set_roman_str(input_str);
            return true;
        }


        return false;
    }

    bool is_inputted_by_int(const std::string& i_string, Roman& roman){
        std::istringstream is {i_string};
        int possible_input_int;

        if (is >> possible_input_int) {
            roman.set_roman_int(possible_input_int);
            return true;
        }

        return false;
    }


    std::istream& operator>>(std::istream& is, Roman& roman) {
        std::string input;
        is >> input;

        // set operation in conditions
        if (is_inputted_by_int(input,roman) ||
            is_inputted_by_string(input,roman) )
                return is;

        is.clear(std::ios::failbit);
        return is;
    }
    std::ostream& operator<<(std::ostream& os, const Roman& roman) {
        return os << roman.get_roman_str();
    }

    void Roman::set_roman_int(int roman_int_local) {
        this->roman_str = roman_int_to_str(roman_int_local);
        this->roman_int = roman_int_local;

    }

    void Roman::set_roman_str(const std::string &roman_str_local) {
        if (!is_valid_roman_str(roman_str_local))
            error("bad string roman");

        this->roman_int = roman_str_to_int(roman_str_local);
        this->roman_str = roman_str_local;
    }

    void test() {

        std::cout << "Testing good values:\n";
        for (std::pair<std::string,int>& el : test::Roman_test_helper::good_romans_2) {
            try {
                Roman r{el.first};
                Roman ri{el.second};
                if (ri.get_roman_str() != el.first)
                    error("must be " + el.first + " but:" + ri.get_roman_str());

                if (r.get_roman_int() != el.second)
                    error("must be good");

                std::cout << "PASS: " << r << "\t" << r.get_roman_int() << '\t' << ri << '\t' << ri.get_roman_int() << '\n';
            } catch (std::exception& ex) {
                std::cerr << ex.what();
            }
        }


            std::cout << "Testing bad values:\n";
            for (std::string& el: test::Roman_test_helper::bad_romans_2)
                try {
                    Roman r{el};
                    throw test::Bad_exception {std::format("must be bad, but not for el:{}\t{}",r.get_roman_str(),
                                                           r.get_roman_int())};
                } catch (std::exception&) {
                    std::cout << std::format("PASS: '{}' \n", el);
                } catch (test::Bad_exception& ex) {
                    std::cerr << ex.what();
                }

        std::cout << "Testing inputting values:\n";
        for (std::pair<std::string,int>& el : test::Roman_test_helper::good_romans_2)
            try {
                Roman r1{};
                Roman r2{};
                std::istringstream is_str {el.first};
                std::istringstream is_int {std::format("{}",el.second)};

                is_str >> r1;
                is_int >> r2;
                if (r2.get_roman_str() != el.first)
                    error("must be " + el.first + " but:" + r2.get_roman_str());

                if (r1.get_roman_int() != el.second)
                    error("must be good");

                std::cout << std::format("PASS: {}\t{}\n", el.first, el.second);
            } catch (std::exception& ex) {
                std::cerr << ex.what();
            }




    }
}
