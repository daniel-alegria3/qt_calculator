
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
string Stack<Elem>::dump(void) {
    string text = "";
    for (Node<Elem> *n = top->next; n != NULL; n = n->next) {
        text += to_string(n->value) + "\n";
    }
    return text;
}

