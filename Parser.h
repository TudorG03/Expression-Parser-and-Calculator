#pragma once
#include "Lexer.h"
#include <iostream>
using namespace std;

class Parser
{
private:
	Lexer l;
	string expression;
	string postfix;
	static int parserCount; // folosesc variabila pentru a contoriza numarul de calcule facute de utilizator pe parcursul unei exceutii a programului
public:
	Parser();

	Parser(string expression);

	void setExpression(string expr);

	string getExpression();

	string getPostfix();

	string setPostfix();

	int getOperatorPrecedence(char op);

	int convertOperatorToCode(string op);

	char convertCodeToOperator(int code);

	int stackSize();

	void checkTokens();

	static int getParserCount();

	bool operator!();

	bool operator==(string expr);

	friend class Calculator;
	friend ostream& operator<<(ostream& out, Parser p);
	friend istream& operator>>(istream& in, Parser& p);
};

