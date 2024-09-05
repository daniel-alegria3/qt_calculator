#pragma once
#include <cstddef>
#include <string>
using namespace std;

typedef double Elem;

class Node
{
private:
public:
    double value;
    Node *next;

    Node (void);
    Node (Elem value, Node *next);
    Node (Node *next);
};


class Stack
{
private:
    Node *top;

public:
    Stack();
    void push(Elem elem);
    Elem pop(void);
    Elem peek(void);
    bool is_empty(void);
    string dump(void);
};

