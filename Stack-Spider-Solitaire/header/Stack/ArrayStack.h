#pragma once

namespace ArrayStack
{
    template <class T>
    class Stack
    {
    private:
        //std::stack<T> _stack;

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