#include "../../header/Stack/ArrayStack.h"
#include "../../header/Card/CardController.h"

namespace ArrayStack
{
    template <class T>
    Stack<T>::Stack() = default;

    template <class T>
    Stack<T>::~Stack() 
    {
        clear();
    }

    template <class T>
    T Stack<T>::pop() 
    {
        return new T;
    }

    template <class T>
    T Stack<T>::top()
    {
        //return _stack.top();
    }

    template <class T>
    void Stack<T>::push(T data) 
    {
        //_stack.push(data);
    }

    template<class T>
    bool Stack<T>::empty() 
    {
        //return _stack.empty();
        return true;
    }

    template<class T>
    int Stack<T>::size() 
    {
        return 0;
        //return _stack.size();
    }

    template<class T>
    void Stack<T>::clear() 
    {
        while (!empty()) 
        {
            //_stack.pop();
        }
    }
}