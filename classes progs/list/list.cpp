#include "list.h"

List::List(const int size_){
    size = size_;
    nodes = new Node*[size];
    for(std::ptrdiff_t i = 0; i < size; i++){
        nodes[i] = new Node(0);
    }
    head = nodes[0];
    tail = nodes[0];
}

List::~List(){
    delete[] nodes;
}


std::string List::toString() const{
    std::string str = "";
    for(std::ptrdiff_t i = 0; i < size; i++){
        str += nodes[i]->toString();
        str += " ";
    }
    return str;
}

void List::adresses() const {
    for(std::ptrdiff_t i = 0; i < size; i++){
        std::cout << nodes[i] << std::endl;
    }
}

List& List::operator=(const List& l){
    size = l.size;
    
    nodes = new Node*[size];
    for(std::ptrdiff_t i = 0; i < size; i++){
        (*nodes[i]).setValue((*l.nodes[i]).getValue());// = (*l.nodes[i]).getValue();
    }

}

void List::addNode(int ind, Node * n){
    Node ** temp = new Node*[size];
    for(std::ptrdiff_t i = 0; i < size; i++){
        temp[i] = nodes[i];
    }
    delete[] nodes;
    size += 1;
    nodes = new Node*[size];
    for(std::ptrdiff_t i = 0; i < size; i++){
        nodes[i] = temp[i];
    }
    nodes[ind] = n;
    nodes[ind - 1]->setNext(n);
    n->setNext(nodes[ind]);
}