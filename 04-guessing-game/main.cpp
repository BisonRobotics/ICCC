#include <iostream>
#include <unistd.h>

using namespace std;

int main() {

    srand(time(NULL));
    int r = rand() % 32;

    while(true) {

        int guess;
        cin >> guess;

        if(guess == r) {
            cout << "You guessed it!\n";
            return 0;
        }
        else if(guess < r) {
            cout << "Your guess is too low!\n";
        }
        else {
            cout << "Your guess is too high!\n";
        }
    }

    return 0;
}


/*

    preprocessor stuff
    byte padding
    access modifiers
    methods

*/
