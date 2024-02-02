#include "Parser.h"
#include "Stack.h"
#include "Lexer.h"
#include <iostream>
using namespace std;

Parser::Parser()
{
	expression = "N/A";
	postfix = "";
}

Parser::Parser(string expression)
{
	Lexer::removeWhiteSpaces(expression);
	this->expression = expression;
	Lexer aux(this->expression);
	l = aux;
	checkTokens();
	postfix = setPostfix();
}

void Parser::setExpression(string expr)
{
	Parser aux(expr);
	*this = aux;
}

string Parser::getExpression()
{
	return expression;
}

string Parser::getPostfix()
{
	return postfix;
}

string Parser::setPostfix() // construiesc forma postfixata a expresiei
{
	if (l.size > 0)
	{
		try
		{
			Stack stack(stackSize());
			for (int i = 0; i < l.size; i++)
			{
				if ((string)l[i] == "NUM")
				{
					postfix += to_string((double)l[i]);
					postfix += ' ';
				}
				else
					if ((string)l[i] == "[" || (string)l[i] == "(")
						stack += convertOperatorToCode((string)l[i]);
					else
						if ((string)l[i] == ")")
						{
							while (stack.getTop() != convertOperatorToCode("("))
							{
								postfix += convertCodeToOperator(--stack);
								postfix += ' ';
							}
							--stack;
						}
						else
							if ((string)l[i] == "]")
							{
								while (stack.getTop() != convertOperatorToCode("["))
								{
									postfix += convertCodeToOperator(--stack);
									postfix += ' ';
								}
								--stack;
							}
							else
							{
								if (stack.isEmpty())
									stack += convertOperatorToCode((string)l[i]);
								else
									if ((int)l[i] > getOperatorPrecedence(convertCodeToOperator(stack.getTop())))
										stack += convertOperatorToCode((string)l[i]);
									else
									{
										while (!stack.isEmpty() && (int)l[i] <= getOperatorPrecedence(convertCodeToOperator(stack.getTop())))
										{
											postfix += convertCodeToOperator(--stack);
											postfix += ' ';
										}
										stack += convertOperatorToCode((string)l[i]);
									}
							}
			}
			while (!stack.isEmpty())
			{
				postfix += convertCodeToOperator(--stack);
				postfix += ' ';
			}
		}
		catch (const invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
		Parser::parserCount++;
		return postfix;
	}
	return "";
}

int Parser::getOperatorPrecedence(char op)
{
	int code = 0;
	if (op == '[')
		code = 0;
	if (op == '(')
		code = 1;
	if (op == ')')
		code = 2;
	if (op == ']')
		code = 3;
	if (op == '+')
		code = 4;
	if (op == '-')
		code = 4;
	if (op == '*')
		code = 5;
	if (op == '/')
		code = 5;
	if (op == '^')
		code = 6;
	if (op == '#')
		code = 6;
	return code;
}

int Parser::convertOperatorToCode(string op)
{
	int code = 0;
	if (op == "[")
		code = 1;
	if (op == "(")
		code = 2;
	if (op == ")")
		code = 3;
	if (op == "]")
		code = 4;
	if (op == "+")
		code = 5;
	if (op == "-")
		code = 6;
	if (op == "*")
		code = 7;
	if (op == "/")
		code = 8;
	if (op == "^")
		code = 9;
	if (op == "#")
		code = 10;
	return code;
}

char Parser::convertCodeToOperator(int code)
{
	char op = '\0';
	switch (code)
	{
	case 1:
		op = '[';
		break;
	case 2:
		op = '(';
		break;
	case 3:
		op = ')';
		break;
	case 4:
		op = ']';
		break;
	case 5:
		op = '+';
		break;
	case 6:
		op = '-';
		break;
	case 7:
		op = '*';
		break;
	case 8:
		op = '/';
		break;
	case 9:
		op = '^';
		break;
	case 10:
		op = '#';
		break;
	}
	return op;
}

int Parser::stackSize() // calculez marimea pe care trebuie sa i-o atribui stivei atunci cand postfixez expresia
{
	int s = 0;
	for (int i = 0; i < l.size; i++)
		if ((int)l[i] != 2 && (int)l[i] != 3 && (int)l[i] != -1)
			s++;
	return s;
}

void Parser::checkTokens() // fac validari logice pe expresie
{
	bool valid = true;
	if (l.size > 0)
	{
		int lsb, lrb, rsb, rrb, pre;
		lsb = lrb = rsb = rrb = 0;
		if ((int)l[l.size - 1] == 0 || (int)l[l.size - 1] == 1 || (int)l[0] == 2 || (int)l[0] == 3 || (int)l[0] == 5 || (int)l[0] == 6 || (int)l[l.size - 1] == 4 || (int)l[l.size - 1] == 5 || (int)l[l.size - 1] == 6)
			valid = false;
		if ((int)l[0] == 0)
			lsb++;
		if ((int)l[0] == 1)
			lrb++;
		for (int i = 1; i < l.size - 1 && valid; i++)
		{
			if (lsb < rsb || lrb < rrb)
				valid = false;
			pre = (int)l[i];
			if (pre == 4 || pre == 5 || pre == 6)
			{
				if ((string)l[i - 1] == "[" || (string)l[i - 1] == "(" || (int)l[i - 1] >= 4)
					valid = false;
				if ((string)l[i + 1] == "]" || (string)l[i + 1] == ")" || (int)l[i + 1] >= 4)
					valid = false;
			}
			if (pre == 0)
				lsb++;
			if (pre == 1)
				lrb++;
			if (pre == 2)
				rrb++;
			if (pre == 3)
				rsb++;
		}
		if ((int)l[l.size - 1] == 2)
			rrb++;
		if ((int)l[l.size - 1] == 3)
			rsb++;
		if (lsb != rsb || lrb != rrb)
			valid = false;
	}
	if (!valid)
	{
		cout << "Invalid expression!\n";
		delete[] l.tokens;
		l.tokens = nullptr;
		l.size = 0;
	}
}

int Parser::getParserCount()
{
	return Parser::parserCount;
}

bool Parser::operator!() // verific daca exista expresia postfixata
{
	return postfix.length() > 0;
}

bool Parser::operator==(string expr) // verific daca expresia postfixata este postfixarea unei expresii date
{
	Lexer::removeWhiteSpaces(expr);
	Parser aux(expr);
	if (postfix == aux.getPostfix())
		return true;
	return false;
}

ostream& operator<<(ostream& out, Parser p)
{
	if (!p)
		out << "The original expression was: " << p.getExpression() << "\nThe postfixed expression is: " << p.getPostfix() << "\n";
	else
		out << "The postfixed expression couldn't be calculated!\n";
	return out;
}

istream& operator>>(istream& in, Parser& p)
{
	string expr;
	cout << "Enter an expression: ";
	in >> expr;
	Parser aux(expr);
	p = aux;
	return in;
}

int Parser::parserCount = 0;