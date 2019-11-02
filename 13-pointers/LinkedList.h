#pragma once

#include <iostream>

// create a linked list of double

struct LinkedListNode {
    LinkedListNode* next;
    double d;
};

LinkedListNode* LLN_newLinkedListNode(double d = 0.0) {
    auto lln = new LinkedListNode;
    lln->d = d;
    lln->next = (LinkedListNode*)0x00;
    return lln;
}

struct LinkedList {

    LinkedListNode* head;
    LinkedListNode* tail;

};

void LL_printList(LinkedList* l) {
    auto ptr = l->head;

    while(ptr != 0x00) {
        std::cout 
                << "      "
                << (void*)ptr << " : " 
                << ptr->d << std::endl;
    
        ptr = ptr->next; // advance to next node
    }
}

LinkedList* LL_newLinkedList(void) {
    auto l = new LinkedList;
    l->head = (LinkedListNode*)0x00;
    l->tail = (LinkedListNode*)0x00;
    return l;
}

void LL_addData(LinkedList* l, double d) {

    if(l->head == 0x00) {
        
        l->head = LLN_newLinkedListNode(d);
        l->tail = l->head;
    
    }
    else {

        l->tail->next = LLN_newLinkedListNode(d);
        l->tail = l->tail->next;

    }

}
