#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack() = default;
    ~Stack() = default;

    void push(const T& item);
    void pop();
    T top() const;
    bool isEmpty() const;

private:
    std::vector<T> items;
};

template <typename T>
void Stack<T>::push(const T& item) {
    items.push_back(item);
}

template <typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    items.pop_back();
}

template <typename T>
T Stack<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return items.back();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return items.empty();
}

#endif // STACK_H