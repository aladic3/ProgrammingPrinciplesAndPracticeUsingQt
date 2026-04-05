//
// Created by Dmytrenko Kyrylo on 30.10.2025.
//
/*
grammars:
    calculation:
        list_of_statement
        statement
        print <-- after this ability to assign will be true in each time
        quit
        help

    help:
        "help"

    list_of_statement:
        statement-print-statement-print etc.

    statement:
        expression
        let declaration
        const declaration


    print:
        constexpr char print
        string print_key

    quit:
        constexpr char quit
        string quit_key";

    declaration:
        variable = expression //assert new value


    variable:
        string name


    expression:
        term
        expression + - term

    term:
        postfix
        term / * % postfix

    postfix:
        primary
        postfix !


    primary:
        number
        declaration
        variable
        + - primary
        parentheses
        sqrt parentheses
        pow ( primary , integer )

    parentheses:
        ( expression )
        { expression )

    number:
        float
 */

#include "calculator.h"

#include <fstream>
#include <sstream>

#include "chapter9/try_drill.h"
#include "PPP/std_lib_facilities.h"

class Variable;
class Token_stream;
const std::string input_prompt = "> ";
const std::string result_prompt = "= ";

std::ostream* os_global;
std::istream* is_global;
std::ifstream ifs_global;
std::ofstream ofs_global;


constexpr char quit_kind = 'q';
constexpr char print_kind = ';';
constexpr char number_kind = '8';
constexpr char roman_kind = 'r';
constexpr char let_kind = 'L';
constexpr char name_kind = 'N';
constexpr char square_root_kind = 'R';
constexpr char pow_kind = 'P';
constexpr char nothing_kind = '0';
//constexpr char space_kind = ' ';
constexpr char new_line_kind = '\n';
constexpr char const_kind = 'C';
constexpr char help_kind = 'h';
constexpr char file_read_kind = 'f';
constexpr char file_write_kind = 'F';
constexpr char file_name_kind = 'n';

const std::string const_key = "const";
const std::string quit_key = "exit";
const std::string print_key = "print";
const std::string declarationKey = "let";
const std::string square_root_key = "sqrt";
const std::string pow_key = "pow";
const std::string help_key = "help";
const std::string file_read_key = "from";
const std::string file_write_key = "to";

const std::string help_prompt = "The program implements an interactive calculator (REPL) that reads expressions\n"
        "from std::cin, evaluates them, and prints the result. It supports integer\n"
        "numbers, variables (mutable and const), the operations +, -, *, /, % (modulo via \n"
        "fmod), the postfix factorial !, the square root sqrt(...), integer exponentiation \n"
        "pow(x, i), round and curly brackets (...) and {...}, variable assignment, the \n"
        "keywords let and const, an exit command, and result output.\n";


double expression(Token_stream &ts);

Variable &declaration(Token_stream &ts);

bool is_integer(double val) {
    return (val - static_cast<int>(val)) == 0;
}

class Token {
public:
    char kind_of_token; // can be: q, ;, (, ), {, }, +, -, /, *, 8 (number)
    double value = 0;
    ch9::ex21_22::Roman roman{};
    std::string name;

    Token() : kind_of_token() {
    } //default
    Token(char ch, ch9::ex21_22::Roman& r) : kind_of_token{ch}, roman(r){}
    Token(char ch) : kind_of_token{ch} {
    } //operation, quit, print
    Token(char ch, double val) : kind_of_token{ch}, value{val} {
    }

    Token(std::string str, char ch) : kind_of_token{ch}, name{std::move(str)} {
    }
};

class Variable {
private:
    std::string name;
    double value = 0;
    bool is_constant;

public:
    Variable(std::string n) : name(std::move(n)), is_constant(false) {
    }

    Variable(std::string n, double v) : name(std::move(n)), value(v), is_constant(false) {
    }

    Variable(std::string n, bool constant) : name(std::move(n)), is_constant(constant) {
    }

    Variable(std::string n, double v, bool constant) : name(std::move(n)), value(v), is_constant(constant) {
    }

    Variable() {
    }


    Variable &setValue(double val) {
        if (is_constant) error("this is constant");
        value = val;
        return *this;
    }

    Variable &set_constant_type() {
        this->is_constant = true;
        return *this;
    }

    double getValue() const { return value; }
    void setName(std::string n) { name = n; }
    std::string getName() { return name; }
};


class Token_stream {
public:
    void putback(Token t);

    Token get();
    Token get_file_name();

    void clean_mess();



private:


    static bool is_can_be_in_variable_name(char input);

    static Token translate_keyword_to_token(const std::string &name);

    bool is_full = false;
    Token buffer;
};

Token Token_stream::get_file_name() {
    if (is_full) {
        is_full = false;
        return buffer;
    }

    char input = 0;

    if (!(is_global->get(input)))
        error("Bad input in Token_stream::get(). std::cin error!");

    while (std::isspace(input) && input != new_line_kind) // omit spaces
        is_global->get(input);

    is_global->putback(input);
    std::string file_name;
    *is_global >> file_name;


    return Token{file_name, file_name_kind};


}

Token Token_stream::translate_keyword_to_token(const std::string &name) {
    if (name == declarationKey)
        return Token{let_kind};

    if (name == square_root_key)
        return Token{square_root_kind};

    if (name == pow_key)
        return Token{pow_kind};

    if (name == print_key)
        return Token{print_kind};

    if (name == quit_key)
        return Token{quit_kind};

    if (name == const_key)
        return Token{const_kind};

    if (name == help_key)
        return Token{help_kind};

    if (name == file_read_key)
        return Token{file_read_kind};

    if (name == file_write_key)
        return Token{file_write_kind};

    return Token{nothing_kind};
}

void Token_stream::clean_mess() {
    if (is_full && buffer.kind_of_token == print_kind) {
        is_full = false;
        return;
    }
    is_full = false;

    is_global->clear();
    char skip = 0;
    while (skip != print_kind && skip != new_line_kind)
        is_global->get(skip);
}


bool Token_stream::is_can_be_in_variable_name(char input)
// can be char include in variable name?
{
    if (!std::isalpha(input) && !std::isdigit(input) && input != '_') //if not in alphabet or not number or _
        return false;

    return true;
}


void Token_stream::putback(Token t) {
    if (is_full) error("Buffer is full!");

    buffer = t;
    is_full = true;
}


Token Token_stream::get() {
    if (is_full) {
        is_full = false;
        return buffer;
    }

    char input = 0;
    is_global->get(input);
    if (is_global->eof())
        return Token{quit_kind};

    if (is_global->fail()) {
        is_global->clear();
        *is_global >> input;

        if (is_global->eof())
            return Token{quit_kind};

        error("Bad input in Token_stream::get(). std::cin error!");
        throw;
    }
    while (std::isspace(input) && input != new_line_kind) // omit spaces
        is_global->get(input);

    switch (input) {
        case print_kind: // for print and exit
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '{':
        case '}':
        case '!':
        case '%':
        case '=':
        case ',':
            return Token{input};

        case new_line_kind: //possibility print after press enter
            return Token{print_kind};

        //case '.': //if double input
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            is_global->putback(input);
            double value;
            *is_global >> value;

            if (!is_integer(value)) error("Must be integer");

            return Token{number_kind, value};
        }

        case 'I': case 'V': case 'X': case 'L': case 'D':
        case 'M': case 'C': {
            ch9::ex21_22::Roman r;

            std::string roman_name;
            roman_name += input;

            while (is_global->get(input) && isalpha(input)) {
                roman_name += input;
            }

            is_global->putback(input);

            std::istringstream is_for_roman{roman_name};

            is_for_roman >> r;

            return Token{roman_kind,r};
        }


        default: {
            std::string variable_name;
            variable_name += input;

            if (variable_name == "#") // allow let with this symbol (drill)
                return translate_keyword_to_token(declarationKey);

            if (!std::isalpha(input) && input != '_') error("Bad input in Token_stream::get()!");


            while (is_global->get(input) && is_can_be_in_variable_name(input)) {
                variable_name += input;
            }

            is_global->putback(input);

            Token result_translate = translate_keyword_to_token(variable_name);

            if (result_translate.kind_of_token != nothing_kind)
                return result_translate;

            return Token{variable_name, name_kind};
        }
    }
}


class VariableTable {
private:
    Variable null_buffer{};
    std::vector<Variable> var_table;


    Variable &get_var_from_table(const std::string &name);

    bool possibility_to_assign;

public:
    Variable &get_null_variable();

    VariableTable() : possibility_to_assign(true) {
    }

    void set_unability_to_assign();

    bool is_can_declaration() const;

    void set_ability_to_assign();

    bool is_declared(const std::string &name);

    double get_value_from_table(const std::string &name);

    Variable &add_variable_to_table(const std::string &name, double value);

    Variable &add_const_variable_to_table(const std::string &name, double value);

    Variable &change_variable_in_table(const std::string &name, double value);

    Variable &try_declaration_without_declKey(Token &token, Token_stream &ts);
};

Variable &VariableTable::get_null_variable() {
    return null_buffer;
}


Variable &VariableTable::try_declaration_without_declKey(Token &token, Token_stream &ts) {
    Variable &result = this->null_buffer; // declaration not success, we return null object

    char input = ts.get().kind_of_token;


    set_unability_to_assign();


    if (input == '=') {
        std::cin.putback(input);
        ts.putback(token);

        result = declaration(ts);;
    } else
        std::cin.putback(input);


    return result;
}


void VariableTable::set_unability_to_assign() {
    possibility_to_assign = false;
}


bool VariableTable::is_can_declaration() const
// this function assign possibility_to_assign to false value
// because assigning value ability must be one time in first part of expression,
// not anymore
{
    return possibility_to_assign;
}

void VariableTable::set_ability_to_assign() {
    possibility_to_assign = true;
}


double VariableTable::get_value_from_table(const std::string &name) {
    return get_var_from_table(name).getValue();
}


bool VariableTable::is_declared(const std::string &name) {
    for (Variable &element: var_table) {
        if (name == element.getName()) return true;
    }

    return false;
}

Variable &VariableTable::get_var_from_table(const std::string &name) {
    for (Variable &var: var_table) {
        if (var.getName() == name) return var;
    }

    error("Not existing var with name: " + name);
    return null_buffer;
}

Variable &VariableTable::add_variable_to_table(const std::string &name, double value) {
    if (is_declared(name))
        error("Variable is also declared! You can create with another name!");

    return var_table.emplace_back(name, value);
}

Variable &VariableTable::add_const_variable_to_table(const std::string &name, double value) {
    return add_variable_to_table(name, value).set_constant_type();
}


Variable &VariableTable::change_variable_in_table(const std::string &name, double value) {
    return get_var_from_table(name).setValue(value);
}

bool is_multiply_double_max_min_limit(double left, double right) {
    return std::abs(left) > std::numeric_limits<double>::max() / std::abs(right);
}

bool is_factorial_ull_limit(unsigned long long left, int right) {
    return left > std::numeric_limits<unsigned long long>::max() / right;
}


//Token_stream ts(std::cin); // provides get() and pullback
VariableTable variable_table;


unsigned long long factorial(const double value) {
    int result = 1;

    if (!is_integer(value)) error("must be integer value!");
    if (value < 0) error("Minus factorial not exist!");
    if (value <= 1) return result;

    for (int i = 2; i <= value; ++i) {
        if (is_factorial_ull_limit(result, i))
            error("Overflow factorial result");

        result *= i;
    }

    return result;
}

double parentheses(Token &token, Token_stream &ts) {
    switch (token.kind_of_token) {
        case '(': {
            double result = expression(ts);

            token = ts.get();
            if (token.kind_of_token != ')') error("Must be ( expression )!");

            return result;
            break;
        }
        case '{': {
            double result = expression(ts);


            token = ts.get();
            if (token.kind_of_token != '}') error("Must be { expression }!");

            return result;
            break;
        }

        default:
            error("Must be ( expression ) or { expression }");
    }
    return 0;
}

double pow_statement(Token_stream &ts) {
    // pow (x,i) mean "multiply x with itself i times. i - integer"
    Token token = ts.get();
    switch (token.kind_of_token) {
        case '(': {
            double x = expression(ts);

            token = ts.get();

            if (token.kind_of_token != ',') error("comma (',') expected");

            token = ts.get();

            if (token.kind_of_token != number_kind) error("number expected");

            int power = static_cast<int>(token.value);

            token = ts.get();

            if (token.kind_of_token != ')') error("Must be ( expression )!");

            return std::pow(x, power);

            break;
        }

        default:
            error("Must be ( expression ) ");
    }

    return 0;
}

double primary(Token_stream &ts) {
    Token token = ts.get();
    double result = 0;

    // assigning can be only if first name_kind and after this name must be '=', another we can't do this
    if (token.kind_of_token != name_kind && variable_table.is_can_declaration())
        variable_table.set_unability_to_assign();

    switch (token.kind_of_token) {
        case '-':
            result = -primary(ts);
            break;
        case '+':
            result = primary(ts);
            break;
        case roman_kind:
            result = token.roman.get_roman_int();
            break;
        case number_kind:
            result = token.value;
            break;

        case name_kind: {
            if (variable_table.is_can_declaration()) {
                Variable &result_assigning = variable_table.try_declaration_without_declKey(token, ts);

                if (&result_assigning != &variable_table.get_null_variable()) {
                    // if assigning success
                    return result_assigning.getValue();
                }
            }

            result = variable_table.get_value_from_table(token.name);
            break;
        }

        case '(':
        case '{':
            result = parentheses(token, ts);
            break;

        case square_root_kind: {
            token = ts.get(); // need for parentheses function. after sqrt_kind token must be ( expr ).
            double res_parentheses = parentheses(token, ts);

            if (res_parentheses < 0)
                error("Negative can't be in square root operation");

            result = std::sqrt(res_parentheses);
            break;
        }

        case pow_kind:
            result = pow_statement(ts);
            break;


        default:
            ts.putback(token);
            error("primary expected");
            break;
    }


    return result;
}

double postfix(Token_stream &ts) {
    double result = primary(ts);
    Token token = ts.get();

    for (; token.kind_of_token == '!'; token = ts.get()) {
        result = factorial(result);
    }

    ts.putback(token);
    return result;
}


double term(Token_stream &ts) {
    // deal with * and /
    double left = postfix(ts);
    Token token = ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '%': {
                double right = postfix(ts);

                if (right == 0) error("Divide (%) by zero!");

                left = std::fmod(left, right);
                break;
            }
            case '/': {
                double right = postfix(ts);

                if (right == 0) error("Divide by zero!");

                left /= right;
                break;
            }


            case '*': {
                double right = postfix(ts);

                if (is_multiply_double_max_min_limit(left, right))
                    error("Multiplication limit fault.");

                left *= right;
                break;
            }

            default:
                ts.putback(token);
                return left;
        }
        token = ts.get();
    }
}

double expression(Token_stream &ts) {
    // deal with + and -
    double left = term(ts);
    Token token = ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '+':
                left += term(ts);
                break;

            case '-':
                left -= term(ts);
                break;


            default:
                ts.putback(token);

                return left;
        }
        token = ts.get();
    }
}

Variable &declaration(Token_stream &ts) {
    Token token = ts.get();
    Variable *result = &variable_table.get_null_variable();

    switch (token.kind_of_token) {
        case name_kind: {
            const std::string name = token.name;

            token = ts.get();

            if (token.kind_of_token != '=') error("Symbol '=' expected");

            double value = expression(ts);

            if (variable_table.is_declared(name))
                result = &variable_table.change_variable_in_table(name, value);
            else
                result = &variable_table.add_variable_to_table(name, value);

            break;
        }
        default:
            error("name expected");
    }

    return *result;
}

std::ofstream get_file_output_stream(Token_stream& ts) {
    Token token = ts.get_file_name();


    switch (token.kind_of_token) {
        case file_name_kind: {
            return ch9::open_output_stream(token.name);

        }
        default:
            error("name expected");
            throw;
    }

}

std::ifstream get_file_input_stream(Token_stream& ts) {
    Token token = ts.get_file_name();


    switch (token.kind_of_token) {
        case file_name_kind: {
            return  ch9::open_input_stream(token.name);

        }
        default:
            error("name expected");
            throw;
    }


}

double statement(Token_stream &ts) {
    Token token = ts.get();

    switch (token.kind_of_token) {
        case let_kind: {
            return declaration(ts).getValue();
        }

        case const_kind: {
            return declaration(ts).set_constant_type().getValue();
        }

        case file_read_kind: {
            ifs_global = get_file_input_stream(ts);
            is_global = &ifs_global;
            return 0;
        }
        case file_write_kind: {
            ofs_global = get_file_output_stream(ts);
            os_global = &ofs_global;
            return 0;
        }


        default:
            ts.putback(token);
            return expression(ts);
    }
}

void calculate_once(std::istream &input_stream, std::ostream& output_stream) {
    is_global = &input_stream;
    os_global = &output_stream;
    Token_stream ts {};

    try {
        variable_table.add_const_variable_to_table("pi", 3.1415926535);
        variable_table.add_const_variable_to_table("e", 2.7182818284);
    } catch (...) {}

    Token token{};

    double left = 0;


    while (input_stream)
        try {
            //std::cout << input_prompt;
            // *os_global << input_prompt;

            token = ts.get();
            variable_table.set_ability_to_assign();

            while (token.kind_of_token == print_kind)
                token = ts.get();

            if (token.kind_of_token == quit_kind)
                return;



            ts.putback(token);

            left = statement(ts);

            *os_global << result_prompt << left; // ch9::ex21_22::Roman{static_cast<int>(left)}
        } catch (std::exception &exception) {
            std::cerr << exception.what();
            ts.clean_mess();
        }
}

void calculation(std::istream &input_stream, std::ostream& output_stream) {
    is_global = &input_stream;
    os_global = &output_stream;
    Token_stream ts {};

    try {
        variable_table.add_const_variable_to_table("pi", 3.1415926535);
        variable_table.add_const_variable_to_table("e", 2.7182818284);
    } catch (...) {}

    Token token{};

    double left = 0;
    *os_global << "Welcome to simple calculator.\n"
            "Please enter expressions using integer numbers.\n"
            "For help, enter 'help'." << std::endl;


    while (input_stream)
        try {
            //std::cout << input_prompt;
             *os_global << input_prompt;

            token = ts.get();
            variable_table.set_ability_to_assign();

            while (token.kind_of_token == print_kind)
                token = ts.get();

            if (token.kind_of_token == help_kind) {
                 *os_global << help_prompt;
                continue;
            }
            if (token.kind_of_token == quit_kind)
                return;



            ts.putback(token);

            left = statement(ts);

        *os_global << result_prompt << left << std::endl; // ch9::ex21_22::Roman{static_cast<int>(left)}
        } catch (std::exception &exception) {
            std::cerr << exception.what();
            ts.clean_mess();
        }
}
