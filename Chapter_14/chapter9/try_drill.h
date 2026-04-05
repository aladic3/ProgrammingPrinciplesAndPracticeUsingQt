//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//

#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <string>

#include "PPP/std_lib_facilities.h"

namespace ch9 {
    [[nodiscard]] std::ofstream open_output_stream(const std::string& file_name);
    [[nodiscard]] std::ifstream open_input_stream(const std::string& file_name);
}

namespace ch9::ex21_22 {
    class Roman;

    struct Roman_helper {
        inline static const std::vector<std::pair<char,int>> basic_values{
                {'M',1000},
                {'D',500},
                {'C', 100},
                {'L', 50},
                {'X', 10},
                {'V', 5},
                {'I', 1}
        };
        static constexpr std::string non_repeatable_romans {"VLD"};
        static constexpr  std::string all_possible_romans {"VLDIXCM"};
        inline static const std::vector<std::pair<char,std::string>> subtractions_rules{
                {'I',"XV"},
                {'X',"LC"},
                {'C',"DM"}
        };
    };


    bool is_inputted_by_int(const std::string& i_string, Roman& roman);
    bool is_inputted_by_string(const std::string& i_string, Roman& roman);
    bool is_good_subtraction(char current_roman, char last_roman);
    bool is_good_repeating(char last_roman, char current_roman, int& count_repeat);
    bool is_roman(char current_roman);
    int roman_ch_to_int(char ch);
    char roman_int_to_ch(int r);
    bool is_valid_roman_str(const std::string& roman_str);
    bool is_valid_roman_int(int roman_int);
    int roman_str_to_int(const std::string& roman_str);
    std::string roman_int_to_str(int roman_int);

    std::istream& operator>>(std::istream& is, Roman& roman);
    std::ostream& operator<<(std::ostream& os, const Roman& roman);

    void test();

    class Roman {
    public:
        Roman()= default;
        Roman(const std::string& roman_str):roman_str(roman_str) {
            if (!is_valid_roman_str(roman_str))
                error("Bad string roman:"+roman_str);

            roman_int = roman_str_to_int(roman_str);
        }
        Roman(int roman_int):roman_int(roman_int) {
            roman_str = roman_int_to_str(roman_int);
        }

        [[nodiscard]] const std::string& get_roman_str()const {return roman_str;}
        [[nodiscard]] int get_roman_int() const {return roman_int;}
        void set_roman_str(const std::string& roman_str_local);
        void set_roman_int(int roman_int_local);

    private:
        std::string roman_str{"I"};
        int roman_int = 1;
    };
}

namespace ch9::test {
    class Bad_exception{
    public:
        Bad_exception(const std::string&  message):str(message + '\n'){}

        std::string what() { return str;}

    private:
        std::string str;
    };

    struct Roman_test_helper {
        inline static std::vector<std::pair<std::string,int>> good_romans_2 = {
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"VI", 6},
        {"IX", 9},
        {"X", 10},
        {"XI", 11},
        {"XIV", 14},
        {"XV", 15},
        {"XIX", 19},
        {"XX", 20},
        {"XL", 40},
        {"XLIV", 44},
        {"XLIX", 49},
        {"L", 50},
        {"LVIII", 58},
        {"LX", 60},
        {"XC", 90},
        {"XCIV", 94},
        {"XCIX", 99},
        {"C", 100},
        {"CXL", 140},
        {"CL", 150},
        {"CD", 400},
        {"CDXLIV", 444},
        {"D", 500},
        {"DXC", 590},
        {"CM", 900},
        {"CMXC", 990},
        {"M", 1000},
        {"MCM", 1900},
        {"MCMXL", 1940},
        {"MCMXC", 1990},
        {"MCMXCIV", 1994},
        {"MM", 2000},
        {"MMXXIII", 2023},
        {"MMXL", 2040},
        {"MMCD", 2400},
        {"MMCM", 2900},
        {"MMM", 3000},
        {"MMMCM", 3900},
        {"MMMCMXC", 3990},
        {"MMMCMXCV", 3995},
        {"MMMCMXCIX", 3999},
        {"D", 500},
        {"L", 50},
        {"V", 5}
    };

        inline static std::vector<std::string> bad_romans_2 = {
        // запрещённые повторы
        "IIII",
        "VV",
        "LL",
        "DD",
        "MMMM",

        // неправильные вычитания
        "IL",
        "IC",
        "ID",
        "IM",
        "VX",
        "XD",
        "XM",
        "LC",
        "LD",
        "DM",

        // двойное / цепное вычитание
        "IIV",
        "IIX",
        "XXC",
        "CCM",

        // нарушение канонической структуры
        "MCMC",
        "CMC",
        "CMCM",
        "XCX",
        "IXI",
        "IXX",

        // некорректные формы чисел
        "VIV",
        "LIL",
        "DCD",
        "VIIII",
        "LXXXX",
        "DCCCC",

        // мусор / не-римские
        "ABC",
        "A",
        "X1V",
        "MCMXCI!",
        "",
        " ",
        " I",
        "I ",
        "X V",

        // прочие некорректные
        "IMX",
        "MXM",
        "DDM",
        "IIIV"
    };


        inline static std::vector<std::pair<std::string, int>> good_romans = {

        {"MMMCMXCIX", 3999},
        {"V", 5},
        {"MCM", 1900},
        {"MM", 2000},
        {"L", 50},
        {"LVIII", 58},
        {"VI", 6},
        {"D", 500},


        {"IX", 9},
        {"X", 10},
        {"XIV", 14},
        {"XV", 15},
        {"XIX", 19},
        {"XX", 20},
        {"IV", 4},
        {"XL", 40},
        {"XLIV", 44},
        {"XLIX", 49},

        {"III", 3},

        {"XC", 90},
        {"XCIV", 94},
        {"C", 100},
        {"CD", 400},
        {"CDXLII", 442},

        {"I", 1},
        {"II", 2},
        {"CM", 900},
        {"CMXLIV", 944},
        {"M", 1000},
        {"MCMXCIV", 1994},
        {"MMXXIV", 2024},

    };

        inline static std::vector<std::string> bad_romans = {
        "IIV",
        "XXC",      // неправильный порядок
        "MCMC",     // повтор вычитательной конструкции
        "IIII",     // > 3 повторов I
        "VV",       // V нельзя повторять
        "LL",       // L нельзя повторять
        "DD",       // D нельзя повторять
        "VX",       // нельзя вычитать V
        "IL",       // I нельзя вычитать из L
        "IC",       // I нельзя вычитать из C
        "ID",       // запрещено
        "IM",       // запрещено
        "XM",       // X нельзя вычитать из M
        "XD",       // X нельзя вычитать из D
        "LC",       // L не участвует в вычитании
        "DM",       // D не участвует в вычитании

        "DDM",      // повтор D + порядок
        "MMMM",     // > 3999
        "ABC",      // мусор
        "",         // пустая строка
    };
    };

}
