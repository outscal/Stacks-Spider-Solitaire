#pragma once
#include <stack>

namespace ArrayStack
{
    template <class T>
    class Stack
    {
    private:
        std::stack<T> _stack;

    public:
        Stack();
        ~Stack();

        T pop();
        T top();
        void push(T data);
        bool empty();
        int size();
        void clear();
    };

}

namespace ArrayStack
{
    template <class T>
    Stack<T>::Stack()
    {
        _stack = std::stack<T>();
    }

    template <class T>
    Stack<T>::~Stack()
    {
        clear();
    }

    template <class T>
    T Stack<T>::pop()
    {
        if (empty()) return nullptr;

        T temp = _stack.top();
        _stack.pop();
        return temp;
    }

    template <class T>
    T Stack<T>::top()
    {
        return _stack.top();
    }

    template <class T>
    void Stack<T>::push(T data)
    {
        _stack.push(data);
    }

    template<class T>
    bool Stack<T>::empty()
    {
        return _stack.empty();
    }

    template<class T>
    int Stack<T>::size()
    {
        return _stack.size();
    }

    template<class T>
    void Stack<T>::clear()
    {
        while (!empty())
        {
            _stack.pop();
        }
    }
}