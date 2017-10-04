#ifndef __ICCC__SINGLY__LINKED__LIST__H__
#define __ICCC__SINGLY__LINKED__LIST__H__

template<typename T>
class SinglyLinkedList {
private:
    struct ListNode {
        ListNode(T data, ListNode* next) {
            this->data = data;
            this->next = next;
        }
        T data;
        ListNode* next;
    };

    ListNode* head = 0;
    int list_size = 0; // start with no nodes

public:
    // add a node to the beginning of the linked list
    void addHeadNode(T data) {
        head = new ListNode(data, head);
        list_size++;
    }

    // remove a node from the beginning of the list
    bool removeHeadNode(T* data = 0) {
        if(list_size) {
            ListNode* tmp = head->next;
            if(data)
                *data = head->data;
            delete head;
            head = tmp;
            list_size--;
            return true;
        }
        return false;
    }
};

#endif // __ICCC__SINGLY__LINKED__LIST__H__
