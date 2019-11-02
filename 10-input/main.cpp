#include <iostream>

using namespace std;

/*

    Loop through forever
        input integer
        
        if integer == EXIT
            exit program

        input word

        print word integer number of times

*/

int main() {

    string inputa, inputb;

    for(;;) {
    
        cin >> inputa;

        if(inputa == "EXIT")
            return 0;

        int iters = stoi(inputa);
        cin >> inputb;

        for(int i = 0; i < iters; i++) {
            cout << inputb << ' ';
        }
        cout << endl;

    }

    return 0;
}