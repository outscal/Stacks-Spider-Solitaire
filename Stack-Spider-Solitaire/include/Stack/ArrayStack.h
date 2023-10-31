#pragma once
#include <array>
#include <cstdio>

namespace ArrayStack
{
	template <class T>
	class Stack
	{
	  private:
		static const int max_size = 200;

		std::array<T, max_size> array_stack;
		int top;

	  public:
		Stack();
		~Stack();

		void push(T data);
		T pop();
		T peek();
		bool empty();
		int size();
		void clear();
		bool search(T data);
	};
} // namespace ArrayStack

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
			printf("Stack is full \n");
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
			printf("Stack is empty \n");
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
			printf("Stack is empty \n");
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
			pop();
		}
	}

	template <class T>
	inline bool Stack<T>::search(T data)
	{
		for (auto iterator = array_stack.begin(); iterator != array_stack.end(); ++iterator)
		{
			if (data == *(iterator))
				return true;
		}

		return false;
	}
} // namespace ArrayStack