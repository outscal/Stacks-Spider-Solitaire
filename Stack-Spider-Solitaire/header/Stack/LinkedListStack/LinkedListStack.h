#pragma once
#include "../../header/Stack/IStack.h"
#include <forward_list>
#include <cstdio>

namespace Stack
{
    namespace LinkedListStack
    {
        template <class T>
        class Stack : public IStack<T>
        {
        private:
            std::forward_list<T> linked_list_stack;
            int stack_size;

        public:
            Stack();
            ~Stack();

            void push(T data) override;
            T pop() override;
            T peek() override;
            bool isEmpty() override;
            int getSize() override;
            void clear() override;
        };
    }

    namespace LinkedListStack
    {
        template <class T>
        Stack<T>::Stack()
        {
            stack_size = 0;
        }

        template <class T>
        Stack<T>::~Stack()
        {
            clear();
        }

        template <class T>
        void Stack<T>::push(T data)
        {
            linked_list_stack.push_front(data);
            stack_size++;
        }

        template <class T>
        T Stack<T>::pop()
        {
            if (!isEmpty())
            {
                T data = linked_list_stack.front();
                linked_list_stack.pop_front();
                --stack_size;
                return data;
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
                return linked_list_stack.front();
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
            return linked_list_stack.empty();
        }

        template <class T>
        int Stack<T>::getSize()
        {
            return stack_size;
        }

        template <class T>
        void Stack<T>::clear()
        {
            while (!isEmpty())
            {
                pop();
            }

            stack_size = 0;
        }
    }
}