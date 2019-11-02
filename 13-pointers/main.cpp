#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

int main() {

    auto l = LL_newLinkedList();

    for(int i = 0; i < 20; i++) {
        LL_addData(l, 3.1415 * i);
    }

    LL_printList(l);

    return 0;
}