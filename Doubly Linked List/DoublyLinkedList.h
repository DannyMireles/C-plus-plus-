#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}
    DoublyLinkedList(T); //CREATE A NODE OF TYPE T!!
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    void print();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
    void copy(const DoublyLinkedList<T>&);
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& doublyLLSource) { // copy constructor 
    Node<T>*curSource = doublyLLSource.head;
    Node<T>*cur = nullptr;
    while (curSource != nullptr) {
        Node<T>* newNode = new Node<T>(curSource->data);
        if (head == nullptr) { //list is empty
            head = newNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            //cur = newNode; //cur becomes newNode regardless of where it goes
        }
        else { //list is NOT empty
            cur->next = newNode;
            newNode->prev = cur;
            newNode->next = nullptr;
            //cur = newNode;
        }
        //since cur is set to newNode regardless, we can pull it outside of the if and else statements.
        //cur->prev = cur;
        cur = newNode;
        tail = newNode;
        //curSource->prev = curSource;
        curSource = curSource->next;
    }
    this->sz = doublyLLSource.sz;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) {
    Node<T>* newNode = new Node<T>(data);
    // this is a constructor so there's only one node in the list. Both head and tail point to the same object.
    head = newNode;
    tail = newNode;
    sz = 1;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& doublyLLSource) : head(nullptr), tail(nullptr), sz(0) {
    copy(doublyLLSource);
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
const T& DoublyLinkedList<T>::front() const { //this function ensures a const reference to be returned. It promises that the object returned HAS NOT and CANNOT be changed.
    return *head;
}

template<typename T>
T& DoublyLinkedList<T>::front() {
    return head->data;
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
    return *tail;
}

template<typename T>
T& DoublyLinkedList<T>::back() {
    return tail->data;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T data) {
    //std::cout << "push_back called" << std::endl;
    Node<T>* newNode = new Node<T>(data);
    Node<T>* cur = tail;
    //std::cout << "set cur to tail" << std::endl;
    if (sz == 0 || cur == nullptr) { //list is empty
        head = newNode;
        //std::cout << "set head to newNode" << std::endl;
        /*head->prev = nullptr;
        head->next = nullptr;
        sz++;
        return;*/
    }
    //else, the list is not empty.
    //cur->next = newNode; this might be the cause of a segfault (11:59 AM 11/20) ** Confirmed cause **
    newNode->prev = cur;
    //std::cout << "newNode->prev set to cur" << std::endl;
    newNode->next = nullptr;
    //std::cout << "newNode->next set to nullptr" << std::endl;
    if (cur != nullptr) { //list wasn't empty
        cur->next = newNode;
    }
    tail = newNode;
    //std::cout << "tail set to newNode" << std::endl;
    sz++;
    return;
}

template<typename T>
void DoublyLinkedList<T>::push_front(T data) {
    Node<T>* newNode = new Node<T>(data);
    Node<T>* cur = head;
    if (sz == 0 || cur == nullptr) {
        tail = newNode;
    }
    newNode->next = cur;
    newNode->prev = nullptr;
    if (cur != nullptr) { //if the list wasn't empty to begin with
        cur->prev = newNode;
    }
    head = newNode;
    sz++;
    return;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (sz == 0) {
        return;
    }
    if (tail->prev != nullptr) { //list size is greater than one
        Node<T>* cur = tail->prev;
        Node<T>* targetNode = tail;
        cur->next = nullptr;
        delete targetNode;
        tail = cur;
        sz--;
        return;
    }
    else { //list only has one object, head==tail
        Node<T>* targetNode = tail;
        delete targetNode;
        head = nullptr;
        tail = nullptr;
        sz--;
        return;
    }
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (sz == 0) {
        return;
    }
    if (head->next != nullptr) { //list size is greater than one
        Node<T>* cur = head->next;
        Node<T>* targetNode = head;
        cur->prev = nullptr;
        delete targetNode;
        head = cur;
        sz--;
        return;
    }
    else { //list only has one object, head==tail
        Node<T>* targetNode = head;
        delete targetNode;
        head = nullptr;
        tail = nullptr;
        sz--;
        return;
    }
}

//////////////////////////////////////////////////////////////////////////////
//  *check size AND the value of given idx, exit function if needed         //
//  *check if the index is the index of the head, and handle that if needed //
//  *check if the index is the index of the tail, and handle that if needed //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
void DoublyLinkedList<T>::erase(unsigned int idx) {
    //std::cout << "erase() called" << std::endl;
    while (sz != 0 && idx >= 0 && idx < sz) {
        if (idx == 0) {
            pop_front();
            return;
        }
        if (idx == sz-1) {
            pop_back();
            return;
        }
        Node<T>* targetNode = head;
        //std::cout << "targetNode assigned to head" << std::endl;
        //traverse to the node at position idx, starting from the head
        for (unsigned int i = 0; i < idx; ++i) {
            //std::cout << "traversing to idx..." << std::endl;
            targetNode = targetNode->next;
            //std::cout << "targetNode currently at index: " << i << std::endl;
        }
        //std::cout << "done traversing" << std::endl;
        if (targetNode->next != nullptr) {
            /* need to change the node after targetNode's prev pointer to the one before targetNode */
            targetNode->next->prev = targetNode->prev;
            //std::cout << "targetNode was not last node. Prev pointer of following node now points to node before targetNode" << std::endl;
        }
        if (targetNode->prev != nullptr) {
            /* change the node before targetNode's next pointer to point to the one after targetNode */
            targetNode->prev->next = targetNode->next;
            //std::cout << "targetNode was not first node. Next pointer of node before targetNode now points to node following targetNode" << std::endl;
        }
        delete targetNode;
        sz--;
        return;
        //std::cout << "sz decremented" << std::endl;
    }
}

template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int idx) {
    while (sz != 0 && idx >= 0 && idx < sz) {
        if (idx == 0) {
            push_front(data);
            return;
        }
        Node<T>* newNode = new Node<T>(data);
        Node<T>* targetNode = head;
        for (unsigned int i = 0; i < idx; ++i) {
            targetNode = targetNode->next;
        }
        newNode->next = targetNode;
        newNode->prev = targetNode->prev;
        targetNode->prev->next = newNode;
        targetNode->prev = newNode;
        sz++;
        return;
    }
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* delNode = nullptr;
    while (head != nullptr) {
        delNode = head;
        head = head->next;
        delete delNode;
    }
    head = nullptr;
    tail = nullptr;
    sz = 0;
}

template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

template <typename T>
void DoublyLinkedList<T>::print() {
  Node<T>* cur = head;
  while (cur != nullptr) {
    std::cout << cur->data << " ";
    cur = cur->next;
  }
  std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs) {
    if (lhs.sz != rhs.sz) {
        return false;
    }
    Node<T>* lNode = lhs.head;
    Node<T>* rNode = rhs.head;
    while (lNode->next != nullptr && rNode->next != nullptr) {
        if (lNode->data != rNode->data) {
            return false;
        }
        lNode = lNode->next;
        rNode = rNode->next;
    }
    delete lNode; 
    delete rNode;
    return true;
}

template<typename T> 
bool operator!=(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs) {
    return !(lhs == rhs);
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& src) { //copy assignment
    if (this != &src) {
        clear();
        copy(src);
    }
    return *this;
}

#endif
