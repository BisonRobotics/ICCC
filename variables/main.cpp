#include <iostream>

int main(void) {

    int a;
    a = -321;
    float f = 3.14159265f;
    unsigned int b = 465838;
    double d = 1e400;

    long int L = 0L;
    unsigned long int Lu = 1L;

    short int s; // 
    unsigned short int us; 

    char c; // -128 to 127
    unsigned char uc; // 0 to 255

    std::cout << 
        a << std::endl << 
        f << std::endl << 
        d << std::endl;


    return 0;
}
