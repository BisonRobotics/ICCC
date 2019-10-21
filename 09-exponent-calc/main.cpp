#include <iostream>
#include <string>

#define DO_EXPONENT

using namespace std;

int main(int argc, char* argv[]) {

    /*
        argv[0] == name of program
        argv[1] == base
        argv[2] == exponent
    */

    if(argc != 3) {
        cout << "provide a base and exponent\n";
        return 0;
    }

    double base = stod(argv[1]);
    int    exp  = stoi(argv[2]);
 
 #ifdef DO_EXPONENT
    double result = 1.0;
    for(int i = 0; i < exp; i++) {
        result *= base;
    }
#else
    double result = 0.0;
    for(int i = 0; i < exp; i++) {
        result += base;
    }
#endif

    cout << result << endl;

}