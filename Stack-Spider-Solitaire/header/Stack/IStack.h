#pragma once

namespace Stack
{
    template <typename T>
    class IStack
    {
    public:
        virtual void push(T data) = 0;
        virtual T pop() = 0;
        virtual T peek() = 0;
        virtual bool isEmpty() = 0;
        virtual int getSize() = 0;
        virtual void clear() = 0;
        virtual ~IStack() { }
    };
}