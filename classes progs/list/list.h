#ifndef HG_LIST_H
#define HG_LIST_H

#include <string>
#include <iostream>


class Node{
public:
    Node() = default;
    ~Node() = default;
    Node(const int v): value(v) {}
    Node& operator=(const Node& n){
        value = n.value;
        return *this;
    }

    int getValue() const {return value;}
    void setValue(int v) { value = v;}

    void setNext(Node * n) { next = n;}

    std::string toString() const {return std::to_string(value);}
private:
    int value = 0;
    Node * next = nullptr;
};

class List{
public:
    List() = default;
    ~List();
    List(const int size);
    List& operator=(const List& l);

    void addNode(int ind, Node * n);

    std::string toString() const;
    void adresses() const;
private:
    int size = 0;
    Node ** nodes = nullptr;
    Node * head = nullptr;
    Node * tail = nullptr;
};

#endif