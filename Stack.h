#pragma once
#include <iostream>
using namespace std;

class Stack
{
private:
	int top;
	const int size;
	double* stack;
public:
	Stack();

	Stack(int size);

	Stack(const Stack& s);

	~Stack();

	Stack& operator=(const Stack& s);

	bool push(double op); //setter pentru top / setter pentru stack

	double pop();

	double getTop();

	double* getStack();

	int getSize();

	bool isEmpty(); // verifica daca stiva este goala

	Stack& operator+=(double num); // adauga o valoare in varful stivei

	double operator--(); // scoate valoarea din varful stivei

	friend ostream& operator<<(ostream& out, Stack s); // afiseaza varful stivei

	friend istream& operator>>(istream& in, Stack& s); // citeste in varful stivei
};