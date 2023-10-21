#pragma once
#include <forward_list>
#include <cstdio>

namespace LinkedListStack
{
    template <class T>
    class Stack
    {
    private:
        std::forward_list<T> linked_list_stack;

    public:
        Stack();
        ~Stack();

        void push(T data);
        T pop();
        T peek();
        bool empty();
        int size();
        void clear();
    };
}

namespace LinkedListStack
{
    template <class T>
    Stack<T>::Stack() { }

    template <class T>
    Stack<T>::~Stack()
    {
        clear();
    }

    template <class T>
    void Stack<T>::push(T data)
    {
        linked_list_stack.push_front(data);
    }

    template <class T>
    T Stack<T>::pop()
    {
        if (!empty())
        {
            T data = linked_list_stack.front();
            linked_list_stack.pop_front();
            return data;
        }
        else
        {
            printf("Stack is empty \n");
            return nullptr;
        }
    }

    template <class T>
    T Stack<T>::peek()
    {
        if (!empty())
        {
            return linked_list_stack.front();
        }
        else
        {
            printf("Stack is empty \n");
            return nullptr;
        }
    }

    template <class T>
    bool Stack<T>::empty()
    {
        return linked_list_stack.empty();
    }

    template <class T>
    int Stack<T>::size()
    {
        return linked_list_stack.size();
    }

    template <class T>
    void Stack<T>::clear()
    {
        while (!empty())
        {
            pop();
        }
    }
}