#pragma once
#include "Token.h"
#include <iostream>
using namespace std;

class Lexer
{
public:
	char* text;
	int position;
	char currentChar;
	Token* tokens;
	int size;
public:
	Lexer();

	Lexer(string text);

	Lexer(const Lexer& l);

	~Lexer();

	Lexer& operator=(const Lexer& l);

	void previousCharacter();

	void nextCharacter();

	void setText(string expr);

	char* getText();

	void setTokens();

	void setPosition(int pos);

	int getPosition();

	char getCurrentChar();

	Token* getTokens();

	bool isUnary();

	double constructNumber(bool& valid);

	static void removeWhiteSpaces(string& expr);

	Token operator[](int pos);

	Lexer& operator++();

	friend class Parser;
	friend ostream& operator<<(ostream&, Lexer);
	friend istream& operator>>(istream&, Lexer&);
};