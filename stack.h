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
};

#include "stack.cpp"

