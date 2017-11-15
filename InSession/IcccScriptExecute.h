#ifndef __JJC__SCRIPT__EXECUTE__H__
#define __JJC__SCRIPT__EXECUTE__H__

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

// hold variables and need a stack
#include <InSession/IcccSinglyLinkedList.h>

struct Variable {
    std::string name;
    double data;

    Variable(void) { ; }
    Variable(const std::string& name, double data) {
        this->name = name;
        this->data = data;
    }

    friend bool operator==(const Variable& lhs, const Variable& rhs) {
        if(lhs.name == rhs.name)
            return true;
        return false;
    }
};

bool setup_variable(const std::string& input, SinglyLinkedList<Variable>& sll_var);
bool print_command(const std::string& input, SinglyLinkedList<Variable>& sll_var);

int execute_script(const std::vector<std::string>& tb) {
    SinglyLinkedList<Variable> sll_vars;
    SinglyLinkedList<Variable> sll_stack;

    const int STATE_default  = 0;
    const int STATE_variable = 1;
    const int STATE_print    = 2;

    int current_state = STATE_default;

    for(int i = 0; i < tb.size(); i++) {
        std::string token = tb[i];

        //std::cout << current_state << ' ' << token << std::endl;

        switch(current_state) {
            case STATE_default:
                std::cout << "=== state default\n";
                if(token == "VARIABLE") {
                    std::cout << "=== changing state to STATE_variable\n";
                    current_state = STATE_variable;
                } else if(token == "PRINT") {
                    std::cout << "=== changing state to STATE_print\n";
                    current_state = STATE_print;
                } else {
                    std::cerr << "UNKNOWN TOKEN IN DEFAULT STATE: " << token << std::endl;
                    exit(1);
                }
                break;
            case STATE_variable:
                if(setup_variable(token, sll_vars))
                    current_state = STATE_default;
                break;
            case STATE_print:
                if(print_command(token, sll_vars))
                    current_state = STATE_default;
                break;
            default:
                std::cerr << "=== unknown state in primary state machine\n";
                exit(1);
                break;
        }

    }

}

bool print_command(const std::string& input, SinglyLinkedList<Variable>& sll_var) {
    if(input == ";")
        return true;

    Variable var(input, 0.0);
    double var_value;

    if(sll_var.searchFor(var)) {
        std::vector<Variable>* vars = sll_var.getValuesAsVector();

        for(Variable v : (*vars)) {
            if(var == v) {
                var_value = v.data;
                break;
            }
        }

        std::cout << var_value;

        delete vars;
    } else if(input[0] == '"') {
        bool special_char = false;
        for(int i = 1; i < input.length()-1; i++) {
            if(special_char) {
                switch(input[i]) {
                    case 'n':
                        std::cout << std::endl; break;
                    case 't':
                        std::cout << '\t'; break;
                    case 's':
                        std::cout << ' '; break;
                    case '\\':
                        std::cout << '\\';
                    default:
                        std::cerr << "unknown escape character encountered: " << input[i] << std::endl;
                        exit(1);
                        break;
                }
                special_char = false;
            } else if(input[i] == '\\') {
                special_char = true;
            } else {
                std::cout << input[i];
            }
        }
    } else {
        std::cout << std::stod(input);
    }

    return false;
}

bool setup_variable(const std::string& input, SinglyLinkedList<Variable>& sll_var) {
    const int STATE_expect_name      = 0;
    const int STATE_expect_value     = 1;
    const int STATE_expect_semicolon = 2;

    static int current_state = STATE_expect_name;

    // stuff for variables
    static std::string var_name;
    static double      var_value;

    switch(current_state) {
        case STATE_expect_name:
            {
                Variable var(input, 0.0);
                if(sll_var.searchFor(var)) {
                    std::cerr << "VARIABLE: " << input << " ALREADY EXISTS" << std::endl;
                    exit(1);
                } else {
                    var_name = input;
                    current_state = STATE_expect_value;
                    return false;
                }
            }
            break;
        case STATE_expect_value:
            {
                Variable var(input, 0.0);
                if(sll_var.searchFor(var)) {
                    std::vector<Variable>* vars = sll_var.getValuesAsVector();

                    for(Variable v : (*vars)) {
                        if(var == v) {
                            std::cout << "=== Variable with same name found\n";
                            var_value = v.data;
                        }
                    }

                    delete vars;
                    current_state = STATE_expect_semicolon;
                    return false;
                } else {
                    var_value = std::stod(input);
                    current_state = STATE_expect_semicolon;
                    return false;
                }
            }
            break;
        case STATE_expect_semicolon:
            if(input != ";") {
                std::cerr << "SEMI-COLON EXPECTED: " << input << std::endl;
                exit(1);
            }
            current_state = STATE_expect_name;

            sll_var.addHead(Variable(var_name, var_value));

            {
                std::vector<Variable>* vars = sll_var.getValuesAsVector();
                for(Variable v : (*vars)) {
                    std::cout << "=== new variable: " << v.name << " : " << v.data << std::endl;
                }
            }

            return true;
        default:
            std::cerr << "UNKNOWN STATE IN setup_variable" << std::endl;
            exit(1);
    }

}

#endif // __JJC__SCRIPT__EXECUTE__H__
