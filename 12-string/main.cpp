#include <iostream>
#include <string>

using namespace std;

int main() {

    string s; // basic_string<char>
    s = "Hello World";

    /*
        oversimplification of std::string

        union std::string {

            struct {
                char flag;
                char buf[15];
            }

            struct {
                char zeropadding[8];
                char* beg;
                char* end;
                char* cap;
            }

        }

        the first structure within the union allows 
        for something called small string optimization 
        or SSO

    */

    return 0;
}
