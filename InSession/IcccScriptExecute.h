#ifndef __JJC__SCRIPT__EXECUTE__H__
#define __JJC__SCRIPT__EXECUTE__H__

#include <iostream>
#include <vector>
#include <string>
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

int setup_variable(std::string input);

int execute_script(const std::vector<std::string>& tb) {
    SinglyLinkedList<Variable> sll_vars;
    SinglyLinkedList<Variable> sll_stack;

    const int STATE_default  = 0;
    const int STATE_variable = 1;
    const int STATE_print    = 2;

    int current_state = STATE_default;

    for(int i = 0; i < tb.size(); i++) {
        std::string token = tb[i];

        switch(current_state) {
            STATE_default:
                if(token == "VARIABLE") {
                    current_state = STATE_variable;
                } else {
                    std::cerr << "UNKNOWN TOKEN IN DEFAULT STATE: " << token << std::endl;
                    exit(1);
                }
                break;
            STATE_variable:
                setup_variable(token, sll_vars);
                break;
            default:
                break;
        }

    }

}

bool setup_variable(const std::string& input, SinglyLinkedList<Variable>& sll_var) {
    const int STATE_expect_name      = 0;
    const int STATE_expect_value     = 1;
    const int STATE_expect_semicolon = 2;

    static int current_state = STATE_expect_name;
    static std::string var_name;
    static double      var_value;

    switch(current_state) {
        case STATE_expect_name:
            if(sll_var.searchFor(Variable(input, 0.0))) {
                std::cerr << "VARIABLE: " << input << " ALREADY EXISTS" << std::endl;
                exit(1);
            } else {
                var_name = input;
                current_state = STATE_expect_value;
                return false;
            }
            break;
        case STATE_expect_value:
            if(sll_var.searchFor(Variable(input, 0.0))) {
                std::vector<Variable>* vec_ptr = sll_var.getValuesAsVector();

                int s = vec_ptr->size();
                Variable v(input, 0.0);

                for(int i = 0; i < s; i++) {
                    if(vec_ptr->at(i) == v) {
                        var_value = vec_ptr->at(i).data;
                        current_state = STATE_expect_semicolon;
                        delete vec_ptr;
                        return false;
                    }
                }

                std::cerr << "VARIABLE IN LIST, BUT NOT FOUND" << std::endl;
                exit(1);
            } else {
                var_value = std::stod(input);
                current_state = STATE_expect_semicolon;
                return false;
            }
            break;
        case STATE_expect_semicolon:
        default:
            std::cerr << "UNKNOWN STATE IN setup_variable" << std::endl;
            exit(1);
    }

}

#endif // __JJC__SCRIPT__EXECUTE__H__
