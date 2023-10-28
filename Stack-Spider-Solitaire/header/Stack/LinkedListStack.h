#pragma once
#include <cstdio>
#include <forward_list>

namespace LinkedListStack
{
	template <class T>
	class Stack
	{
	  private:
		std::forward_list<T> linked_list_stack;
		int stack_size;

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
} // namespace LinkedListStack

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
		if (!empty())
		{
			T data = linked_list_stack.front();
			linked_list_stack.pop_front();
			--stack_size;
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
		return stack_size;
	}

	template <class T>
	void Stack<T>::clear()
	{
		while (!empty())
		{
			pop();
		}

		stack_size = 0;
	}

	template <class T>
	inline bool Stack<T>::search(T data)
	{
		for (auto iterator = linked_list_stack.begin(); iterator != linked_list_stack.end(); ++iterator)
		{
			if (data == *(iterator))
				return true;
		}

		return false;
	}
} // namespace LinkedListStack