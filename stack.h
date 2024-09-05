#pragma once
#include <cstddef>
#include <string>
using namespace std;

template <class Elem>
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


template <class Elem>
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
    string dump(void);
};

