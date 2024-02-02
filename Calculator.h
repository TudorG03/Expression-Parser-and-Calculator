#pragma once
#include "Parser.h"
#include <iostream>
#include <string>
using namespace std;

class Calculator
{
private:
	string expression;
	Parser p;
	double result;
	bool validExpression;
public:
	Calculator();

	Calculator(string expression);

	void setExpression(string expr);

	string getExpression();

	bool getValidExpression();

	double setResult();

	double getResult();

	double calculate(double a, double b, char op);

	string removeTraillingZeros(double result);

	bool operator>(Calculator c);

	bool operator>(double num);

	bool operator<(Calculator c);

	bool operator<(double num);

	void operator()();

	friend class BinaryFileCalculator;
	friend ostream& operator<<(ostream& out, Calculator c);
	friend istream& operator>>(istream& in, Calculator& c);
};