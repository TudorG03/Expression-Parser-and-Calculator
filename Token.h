#pragma once
#include <string>
using namespace std;

class Token
{
private:
	string type;
	double value;
	int precedence;
public:
	Token();

	Token(string type, double value);

	void setType(string s);

	string getType();

	void setValue(double v);

	double getValue();

	void setPrecedence();

	int getPrecedence();

	explicit operator int();

	explicit operator string();

	explicit operator double();

	friend ostream& operator<<(ostream&, const Token&);
	friend istream& operator>>(istream&, Token&);
};
