#pragma once

#include <cstddef>
#include <string>
using namespace std;

/* typedef double Elem; */

template <typename Elem>
class Node
{
private:
public:
    Elem value;
    Node *next;

    Node (void);
    Node (Elem value, Node *next);
    Node (Node *next);
};


template <typename Elem>
class Stack
{
private:
    Node<Elem> *top;

public:
    Stack();
    void push(Elem elem);
    Elem pop(void);
    Elem peek(void);
    bool is_empty(void);
    void empty(void);
    string dump(void);
    size_t length(void);
    Elem get(size_t index);
};

/* #include "stack.cpp" */

template <typename Elem>
Node<Elem>::Node (void) {}

template <typename Elem>
Node<Elem>::Node (Elem value, Node<Elem> *next) {
    this->value = value;
    this->next = next;
}

template <typename Elem>
Node<Elem>::Node (Node<Elem> *next) {
    this->next = next;
}


template <typename Elem>
Stack<Elem>::Stack() {
    this->top = new Node<Elem>(NULL);
}

template <typename Elem>
void Stack<Elem>::push(Elem elem) {
    top->next = new Node<Elem>(elem, top->next);
}

template <typename Elem>
Elem Stack<Elem>::pop(void) {
    Node<Elem> *del = top->next;
    Elem value = del->value;
    top->next = del->next;
    free(del);
    return value;
}

template <typename Elem>
Elem Stack<Elem>::peek(void) {
    return top->next->value;
}

template <typename Elem>
bool Stack<Elem>::is_empty(void) {
    return top->next == NULL;
}

template <typename Elem>
void Stack<Elem>::empty(void) {
    Node<Elem> *temp = top->next;
    Node<Elem> *del;
    while ((del = temp) != NULL) {
        temp = del->next;
        free(del);
    }
    top->next = NULL;
}

template <typename Elem>
string Stack<Elem>::dump(void) {
    string text = "";
    for (Node<Elem> *n = top->next; n != NULL; n = n->next) {
        text += to_string(n->value) + "\n";
    }
    return text;
}

template <typename Elem>
size_t Stack<Elem>::length(void)
{
    Node<Elem> *node = top->next;
    size_t count = 0;
    while (node != NULL) {
        ++count;
        node = node->next;
    }
    return count;
}

template <typename Elem>
Elem Stack<Elem>::get(size_t index)
{
    if ( index >= length()) {
        // errno = ?
        return 0;
    }

    Node<Elem> *n = top->next;
    while ( n != NULL && index-- > 0) {
        n = n->next;
    }
    return n->value;
}

