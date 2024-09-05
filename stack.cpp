#include "stack.h"

template <class Elem>
Node<Elem>::Node (void) {}

template <class Elem>
Node<Elem>::Node (Elem value, Node *next) {
    this->value = value;
    this->next = next;
}

template <class Elem>
Node<Elem>::Node (Node *next) {
    this->next = next;
}


template <class Elem>
Stack<Elem>::Stack() {
    this->top = new Node<Elem>(NULL);
}

template <class Elem>
void Stack<Elem>::push(Elem elem) {
    top->next = new Node(elem, NULL);
}

template <class Elem>
Elem Stack<Elem>::pop(void) {
    Elem value = top->next->value;
    Node<Elem> *del = top->next;
    top->next = top->next->next;
    free(del);
    return value;
}

template <class Elem>
Elem Stack<Elem>::peek(void) {
    return top->next->value;
}

template <class Elem>
bool Stack<Elem>::is_empty(void) {
    return top->next == NULL;
}

template <class Elem>
string Stack<Elem>::dump(void) {
    string text = "";
    for (Node<Elem> *n = top->next; n != NULL; n = n->next) {
        text += n->value + "\n";
    }
    return text;
}

