#ifndef __ICCC__SINGLY__LINKED__LIST__
#define __ICCC__SINGLY__LINKED__LIST__

#include <iostream>

// always use a primtive
template<typename T>
struct Node {
    T data;
    Node* next;

    Node(T data, Node* next) {
        this->data = data;
        this->next = next;
    }
};

template<typename T>
class SinglyLinkedList {
private:
    Node<T>* head = 0;

public:
    SinglyLinkedList(void) { ; }

    SinglyLinkedList(T data) {
        head = new Node<T>(data, head);
    }

    ~SinglyLinkedList(void) {
        std::cout << "Destructor called" << std::endl;
        while(head != NULL) {
            Node<T>* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    void print(void) {
        Node<T>* tmp = head;

        int i = 0;
        while(tmp != NULL) {
            std::cout << i << ": " << tmp->data << std::endl;
            tmp = tmp->next;
            i++;
        }
    }

    // remove head
    bool decapitate(T* t) {
        if(head != NULL) {
            Node<T>* tmp = head->next;
            *t = head->data;
            delete head;
            head = tmp;
            return true;
        }
        return false;
    }

    void addHead(T data) {
        head = new Node<T>(data, head);
    }

};

#endif // __ICCC__SINGLY__LINKED__LIST__
