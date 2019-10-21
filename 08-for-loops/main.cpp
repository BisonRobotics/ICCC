#include <iostream>

using namespace std;

int main() {


    for(
            int i = 0, j = 0; 
            i < 10; 
            i++, j+=2) {

        cout << i << ' ' << j << endl;

    }

    return 0;
}