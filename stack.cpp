#include "stack.h"

Node::Node (void) {}

Node::Node (Elem value, Node *next) {
    this->value = value;
    this->next = next;
}

Node::Node (Node *next) {
    this->next = next;
}


Stack::Stack() {
    this->top = new Node(NULL);
}

void Stack::push(Elem elem) {
    top->next = new Node(elem, top->next);
}

Elem Stack::pop(void) {
    Elem value = top->next->value;
    Node *del = top->next;
    top->next = top->next->next;
    free(del);
    return value;
}

Elem Stack::peek(void) {
    return top->next->value;
}

bool Stack::is_empty(void) {
    return top->next == NULL;
}

string Stack::dump(void) {
    string text = "";
    for (Node *n = top->next; n != NULL; n = n->next) {
        text += to_string(n->value) + "\n";
    }
    return text;
}

