#include <iostream>

#define DEFAULT_SIZE 10

using std::cout;
using std::endl;

template <typename T>
class stack
{
private:
	int top, max_size;
	T* arr;

public:
	stack();
	stack(int);
	void push(T);
	T pop();
	T peek();
	bool empty() { return (top < 0); }
	void print();
};

template <typename T>
stack<T>::stack()
{
	max_size = DEFAULT_SIZE;
	arr = new T[max_size];
	top = -1;
}

template <typename T>
stack<T>::stack(int size)
{
	max_size = size;
	arr = new T[max_size];
	top = -1;
}

template <typename T>
void stack<T>::push(T item)
{
	if (top == max_size - 1) {
		T* new_arr = new T[max_size * 2];
		for (int i = 0; i <= top; i++)
			new_arr[i] = arr[i];
		delete arr;
		arr = new_arr;
		max_size *= 2;
	}
	arr[++top] = item;
}

template <typename T>
T stack<T>::pop()
{
	return arr[top--];
}

template <typename T>
T stack<T>::peek()
{
	return arr[top];
}

template <typename T>
void stack<T>::print()
{
	cout << "[ ";
	for (int i = 0; i <= top; i++)
		cout << arr[i] << " ";
	cout << "]" << endl;
}