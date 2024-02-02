#include "Stack.h"
#include <stdexcept>
#include <iostream>
using namespace std;

Stack::Stack() : size(10)
{
	top = -1;
	stack = new double[size];
}

Stack::Stack(int size) : size(size)
{
	stack = new double[size];
	top = -1;
}

Stack::Stack(const Stack& s) : size(s.size)
{
	this->top = s.top;
	if (s.stack != nullptr)
	{
		this->stack = new double[s.size];
		for (int i = 0; i < size; i++)
			stack[i] = 1.0 * s.stack[i];
	}
	else
	{
		this->stack = nullptr;
	}
}

Stack::~Stack()
{
	if (stack != nullptr)
	{
		delete[] stack;
		stack = nullptr;
	}
}

Stack& Stack::operator=(const Stack& s)
{
	if (this != &s)
	{
		if (stack != nullptr)
		{
			delete[] stack;
			stack = nullptr;
		}

		this->top = s.top;
		if (s.stack != nullptr)
		{
			this->stack = new double[size];
			int mini = (size < s.size) ? size : s.size;
			for (int i = 0; i < mini; i++)
			{
				stack[i] = 1.0 * s.stack[i];
			}
		}
		else
		{
			this->stack = nullptr;
		}
	}
	return *this;
}

bool Stack::push(double op)
{
	if (top >= size - 1)
	{
		throw invalid_argument("Stack Overflow!");
	}
	stack[++top] = op;
	return true;
}

double Stack::pop()
{
	if (top < 0)
	{
		throw invalid_argument("Stack Underflow!");
	}
	return stack[top--];
}

double Stack::getTop()
{
	if (top < 0)
	{
		throw invalid_argument("Stack is empty!");
	}
	return stack[top];
}

double* Stack::getStack()
{
	if (top >= 0)
	{
		double* aux = new double[top + 1];
		for (int i = 0; i <= top; i++)
			aux[i] = stack[i];
		return aux;
	}
	else
		return nullptr;
}

int Stack::getSize()
{
	return size;
}

bool Stack::isEmpty()
{
	return top < 0;
}

Stack& Stack::operator+=(double num)
{
	bool aux = push(num);
	return *this;
}

double Stack::operator--()
{
	return pop();
}

ostream& operator<<(ostream& out, Stack s)
{
	try
	{
		out << "The stack's top is: " << s.getTop() << endl;
		return out;
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what();
	}
}

istream& operator>>(istream& in, Stack& s)
{
	try
	{
		double num;
		cout << "Push a number onto the stack: ";
		in >> num;
		bool aux = s.push(num);
		return in;
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what();
	}
}