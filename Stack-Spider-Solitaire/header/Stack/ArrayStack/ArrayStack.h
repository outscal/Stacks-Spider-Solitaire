#pragma once
#include "../../header/Stack/IStack.h"
#include <array>

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
            bool isEmpty() override;
            int getSize() override;
            void clear() override;
        };
    }
}