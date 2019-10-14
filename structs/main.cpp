#include <iostream>
#include <string>
using namespace std;

struct Person {
    int age;
    unsigned int year_of_birth;
    string name;
};

void print_person(Person p) {

    cout << "Name: " << p.name << endl;
    
    cout << "Age:  " << p.age  << endl;
    
    cout << "Year of birth: " 
        << p.year_of_birth << endl; 

    cout << endl << endl;

}

int main() {

    Person p0;

    p0.age           = 24;
    p0.year_of_birth = 1995;
    p0.name          = "Joey Cluett";

    print_person(p0);

}
