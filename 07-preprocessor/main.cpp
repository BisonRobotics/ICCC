// any statement starting with # is a preprocessor directive
// preprocessor directives are evaluated before the program is fully parsed

#include <iostream>

// notice here that we include this file twice
// preprocessor directives prevent it from 
// actually being included twice
#include "main.h"
#include "main.h"

using namespace std;

int main() {

    cout << pi << endl;
    cout << mult_pi(3) << endl;



    return 0;
}



