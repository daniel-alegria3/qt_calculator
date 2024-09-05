#pragma once
#include <cstddef>
#include <string>
using namespace std;

class Node
{
private:
public:
    double value;
    Node *next;

    Node (void);
    Node (double value, Node *next);
    Node (Node *next);
};


class Stack
{
private:
    Node *top;

public:
    Stack();
    void push(double elem);
    double pop(void);
    double peek(void);
    bool is_empty(void);
    string dump(void);
};

