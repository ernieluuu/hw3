#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

/*inherited privately because we want the functionality of the stack
to be dictated by us, otherwise it would not be a stack.*/

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
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

/*does the below code need to come before the #endif?*/

/*because it is a vector, we can just call push_back, etc. on the
stack itself, no need to define members_*/
template<typename T>
inline Stack<T>::Stack()
{
	// TODO?
}

template<typename T>
inline Stack<T>::~Stack()
{
	// TODO?
}

template<typename T>
inline bool Stack<T>::empty() const
{
	return this->std::vector<T>::empty();
}

template<typename T>
inline size_t Stack<T>::size() const
{
	return this->std::vector<T>::size();
}

template<typename T>
inline void Stack<T>::push(const T& item)
{
	this->push_back(item);
}

template<typename T>
inline void Stack<T>::pop()
{
	if (this->empty())
	{
		throw std::underflow_error("called pop on an empty stack");
	}
	this->pop_back();
}

/*for my implementation, the top of the stack will be at the back of the vector
because otherwise the push and pop front functions would be O(n)
compared to O(1) for push and pop back.*/
template<typename T>
inline const T& Stack<T>::top() const
{
	if (this->empty())
	{
		throw std::underflow_error("called top on an empty stack");
	}
	return this->back();
}