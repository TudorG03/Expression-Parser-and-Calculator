#include "Token.h"
#include <iostream>
#include <string>
using namespace std;

Token::Token()
{
	type = "N/A";
	value = 0.0f;
	precedence = -2;
}

Token::Token(string type, double value)
{
	this->type = type;
	this->value = value;
	setPrecedence();
}

void Token::setType(string s) //tipuri posibile de token-uri
{
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
	if (s == "NUM" || s == "[" || s == "]" || s == "(" || s == ")" || s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "#")
	{
		type = s;
	}
	else
		cout << "Invalid token type\n";
}

string Token::getType()
{
	return type;
}

void Token::setValue(double v)
{
	if (type == "NUM")
		value = v;
}

double Token::getValue()
{
	return value;
}

void Token::setPrecedence() // -2 = obiect gol; -1 = numar; 0 - 3 = paranteze; 4 - 6 = operatii matematice
{
	if (type == "NUM")
		precedence = -1;
	else
		switch (type[0])
		{
		case '[':
			precedence = 0;
			break;
		case '(':
			precedence = 1;
			break;
		case ')':
			precedence = 2;
			break;
		case ']':
			precedence = 3;
			break;
		case '+':
		case '-':
			precedence = 4;
			break;
		case '*':
		case '/':
			precedence = 5;
			break;
		case '^':
		case '#':
			precedence = 6;
			break;
		default:
			precedence = -2;
			break;
		}
}

int Token::getPrecedence()
{
	return precedence;
}

Token::operator int() // intoarce precedence
{
	return precedence;
}

Token::operator string() // intoarce type
{
	return type;
}

Token::operator double() // intoarce value
{
	return value;
}

ostream& operator<<(ostream& out, const Token& t)
{
	out << "Token type: " << t.type << "\n" << "Token priority: " << t.precedence << "\n";
	if (t.type == "NUM")
		out << "Token value: " << t.value << "\n";
	return out;
}

istream& operator>>(istream& in, Token& t)
{
	string tt;
	cout << "Enter token type: ";
	in >> tt;
	for (int i = 0; i < tt.length(); i++)
		tt[i] = toupper(tt[i]);
	t.setType(tt);
	if (tt == "NUM")
	{
		cout << "Enter token value: ";
		double val;
		in >> val;
		t.setValue(val);
	}
	t.setPrecedence();
	return in;
}