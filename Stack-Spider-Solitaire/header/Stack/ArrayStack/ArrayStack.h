#pragma once
#include "../../header/Stack/IStack.h"
#include <array>
#include <cstdio>

namespace Stack
{
    namespace ArrayStack
    {
        template <class T>
        class Stack : public IStack<T>
        {
        private:
            static const int max_size = 200;

            std::array<T, max_size> array_stack;
            int top;

        public:
            Stack();
            ~Stack();

            void push(T data) override;
            T pop() override;
            T peek() override;
            bool empty() override;
            int size() override;
            void clear() override;
        };
    }

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
            if (!empty())
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
            if (!empty())
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
        bool Stack<T>::empty()
        {
            return top == 0;
        }

        template <class T>
        int Stack<T>::size()
        {
            return top;
        }

        template <class T>
        void Stack<T>::clear()
        {
            while (!empty())
            {
                delete(pop());
            }
        }
    }
}