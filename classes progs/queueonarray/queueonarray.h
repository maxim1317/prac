#ifndef HG_QUEUEONARRAY_H
#define HG_QUEUEONARRAY_H

#include <string>
#include <stdexcept>
#include <ostream>

class QueueOnArray{
public:
    QueueOnArray() = default;
    QueueOnArray(const QueueOnArray& qoa);
    QueueOnArray& operator=(const QueueOnArray& qoa);

    QueueOnArray(const int size);

    ~QueueOnArray();

    void push(const int);
    void pop();
    int top() const;

    void resize(const int newSize);

    std::string toString() const;
    std::ostream& writeTo(std::ostream& os) const;
private:
    int size = 0;
    int * array = nullptr;
    int head = 0;
    int tail = 0; 

    void defragment();
};

inline std::ostream& operator<<(std::ostream& os, const QueueOnArray q){
    return q.writeTo(os);
}

#endif