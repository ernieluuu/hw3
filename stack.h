#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

/*inherited privately because we want the functionality of the stack
to be dictated by us, otherwise it would not be a stack.*/

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private Vector
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};


#endif