#pragma once
#include "../../header/Stack/ArrayStack/ArrayStack.h"
#include <cstdio>

namespace Stack
{
    namespace ArrayStack
    {
        template <class T>
        Stack<T>::Stack()
        {
            top = 0;
        }

        template <class T>
        Stack<T>::~Stack()
        {
            clear();
        }

        template <class T>
        void Stack<T>::push(T data)
        {
            if (top < max_size)
            {
                array_stack[top++] = data;
            }
            else
            {
                printf("Stack Overflow \n");
            }
        }

        template <class T>
        T Stack<T>::pop()
        {
            if (!isEmpty())
            {
                return array_stack[--top];
            }
            else
            {
                printf("Stack Underflow \n");
                return nullptr;
            }
        }

        template <class T>
        T Stack<T>::peek()
        {
            if (!isEmpty())
            {
                return array_stack[top - 1];
            }
            else
            {
                printf("Stack Underflow \n");
                return nullptr;
            }
        }

        template <class T>
        bool Stack<T>::isEmpty()
        {
            return top == 0;
        }

        template <class T>
        int Stack<T>::getSize()
        {
            return top;
        }

        template <class T>
        void Stack<T>::clear()
        {
            while (!isEmpty())
            {
                delete(pop());
            }
        }
    }
}