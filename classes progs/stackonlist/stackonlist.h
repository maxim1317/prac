#ifndef HG_STACKONLIST_H
#define HG_STACKONLIST_H

#include <ostream>
#include <string>
#include <stdexcept>

template<class T>
struct Node{
    Node(const T v): value(v){}
    bool operator==(const Node& t){
        return (value == t.value && prev == t.prev);
    }
    T value = 0;
    Node * prev = nullptr;
};

template<class T>
class StackOnlist{
public:
    StackOnlist() = default;
    StackOnlist(const StackOnlist<T>& sol){
        head = sol.head;
    }
    StackOnlist<T>& operator= (const StackOnlist<T>& sol){
        head = sol.head;
        return *this;
    }

    void push(Node<T>& n){
        if(existsInStack(n)){
            return;
        }
        n.prev = head;
        head = &n;
    }

    void pop() {
        head = head->prev;
    }
    Node<T> top() const {
        return *head;
    }

    std::ostream& writeTo(std::ostream& ostrm) const {
        Node<T> * a = head;
        while (a != nullptr){
            ostrm << a->value << " ";
            a = a->prev;
        }
        return ostrm; 
    }
private:
    Node<T> * head = nullptr;

    bool existsInStack(const Node<T>& n){
        Node<T> * a = head;
        while(a != nullptr){
            if(*a == n){
                return true;
            }
            a = a->prev;
        }
        return false;
    }
};

template<class T>
inline std::ostream& operator<< (std::ostream& ostrm, const StackOnlist<T>& sol){
    return sol.writeTo(ostrm);
}

#endif