#include "Lexer.h"
#include "Token.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Lexer::Lexer()
{
	text = new char[1];
	text[0] = '\0';
	position = -1;
	currentChar = '\0';
	tokens = nullptr;
	size = 0;
}

Lexer::Lexer(string text)
{
	this->text = new char[text.length() + 1];
	strcpy_s(this->text, text.length() + 1, text.c_str());
	position = -1;
	currentChar = '\0';
	tokens = nullptr;
	size = 0;
	++(*this);
	setTokens();
}

Lexer::Lexer(const Lexer& l)
{
	if (l.text != nullptr)
	{
		text = new char[strlen(l.text) + 1];
		strcpy_s(text, strlen(l.text) + 1, l.text);
	}
	else
	{
		text = new char[1];
		text[0] = '\0';
	}
	position = l.position;
	currentChar = l.currentChar;
	if (l.tokens != nullptr)
	{
		size = l.size;
		tokens = new Token[size];
		for (int i = 0; i < size; i++)
			tokens[i] = l.tokens[i];
	}
	else
	{
		tokens = nullptr;
		size = 0;
	}
}

Lexer::~Lexer()
{
	if (text != nullptr)
	{
		delete[] text;
		text = nullptr;
	}

	if (tokens != nullptr)
	{
		delete[] tokens;
		tokens = nullptr;
	}
}

Lexer& Lexer::operator=(const Lexer& l)
{
	if (this != &l)
	{
		if (text != nullptr)
		{
			delete[] text;
			text = nullptr;
		}

		if (tokens != nullptr)
		{
			delete[] tokens;
			tokens = nullptr;
		}

		if (l.text != nullptr)
		{
			text = new char[strlen(l.text) + 1];
			strcpy_s(text, strlen(l.text) + 1, l.text);
		}
		else
		{
			text = new char[1];
			text[0] = '\0';
		}
		position = l.position;
		currentChar = l.currentChar;
		if (l.tokens != nullptr)
		{
			size = l.size;
			tokens = new Token[size];
			for (int i = 0; i < size; i++)
				tokens[i] = l.tokens[i];
		}
		else
		{
			tokens = nullptr;
			size = 0;
		}
	}
	return *this;
}

void Lexer::previousCharacter()
{
	position--;
	if (position >= 0)
		currentChar = text[position];
	else
		position++;
}

void Lexer::nextCharacter()
{
	position++;
	currentChar = position < strlen(text) ? text[position] : '\0';
}

void Lexer::setText(string expr)
{
	if (text != nullptr)
	{
		delete[] text;
		text = nullptr;
	}

	text = new char[expr.length() + 1];
	strcpy_s(text, expr.length() + 1, expr.c_str());

	Lexer aux(text);

	*this = aux;
}

char* Lexer::getText()
{
	return text;
}

void Lexer::setPosition(int pos)
{
	if (pos >= 0 && pos < strlen(text))
	{
		position = pos;
		currentChar = text[pos];
	}
}

int Lexer::getPosition()
{
	return position;
}

char Lexer::getCurrentChar()
{
	return currentChar;
}

void Lexer::setTokens() // creez un vector cu obiecte de tip token pentru parsarea expresiei
{
	size = 0;
	bool valid = true, numExists = false;
	Token* aux = nullptr;
	Token t1;
	for (int i = 0; i < strlen(text) && !numExists; i++)
		if (isdigit(text[i]))
			numExists = true;
	if (!numExists)
	{
		cout << "The expression needs at least a number!\n";
		valid = false;
	}
	while (currentChar != '\0' && valid)
	{
		string s;
		s = currentChar + '\0';
		if (isdigit(currentChar) || currentChar == '.')
		{
			numExists = true;
			Token t("NUM", constructNumber(valid));
			t1 = t;
		}
		else
			switch (currentChar)
			{
			case '[':
			case '(':
			case ')':
			case ']':
			case '*':
			case '/':
			case '^':
			case '#':
			{
				Token t(s, 0);
				t1 = t;
				break;
			}
			case '+':
			case '-':
			{
				Token t;
				if (!isUnary())
				{
					Token aux(s, 0);
					t = aux;
				}
				else
				{
					++(*this);
					double num = constructNumber(valid);
					num = (s == "+") ? (1.0) * num : (-1.0) * num;
					Token aux("NUM", num);
					t = aux;
				}
				t1 = t;
				break;
			}
			case ' ':
			{
				break;
			}
			default:
			{
				valid = false;
				cout << "Illegal character: " << currentChar << "\n";
				break;
			}
			}
		if (!size) //pentru primul token
		{
			tokens = new Token[++size];
			tokens[0] = t1;
		}
		else //pentru restul
		{
			if (currentChar != ' ')
			{
				aux = new Token[++size];
				for (int i = 0; i < size - 1; i++)
					aux[i] = tokens[i];
				aux[size - 1] = t1;
				if (tokens != nullptr)
					delete[] tokens;
				tokens = new Token[size];
				for (int i = 0; i < size; i++)
					tokens[i] = aux[i];
				if (aux != nullptr)
				{
					delete[] aux;
					aux = nullptr;
				}
			}
		}
		++(*this);
	}
	if (!valid) //daca exista caracter invalid atunci dezaloc vectorul de tokeni
	{
		size = 0;
		delete[] tokens;
		tokens = nullptr;
	}
}

Token* Lexer::getTokens()
{
	if (tokens != nullptr)
	{
		Token* t = new Token[size];
		for (int i = 0; i < size; i++)
			t[i] = tokens[i];
		return t;
	}
	return nullptr;
}

bool Lexer::isUnary() // pentru + si - verific daca este operator unar sau binar
{
	if (!position)
		return true;
	previousCharacter();
	char prev = currentChar;
	++(*this);
	++(*this);
	char next = currentChar;
	previousCharacter();
	if (!isdigit(prev) && isdigit(next) && prev != ')' && prev != ']')
		return true;
	return false;
}

double Lexer::constructNumber(bool& valid) //construiesc numar din caractere succesive
{
	string num;
	int dotCount = 0;

	while (isdigit(currentChar) || currentChar == '.')
	{
		if (currentChar == '.')
			if (dotCount == 1)
			{
				/*cout << "Ignoring everything after the second dot. The number added is: " << num << "\n";
				while (isdigit(currentChar) || currentChar == '.')
				{
					++(*this);
				}*/
				cout << "At least a number contains multiple dots!\n";
				valid = false;
				break;
			}
			else
				dotCount++;
		num += currentChar;
		++(*this);
	}
	previousCharacter();
	return stod(num);
}

void Lexer::removeWhiteSpaces(string& expr) //elimin spatiile albe din expresie
{
	string rez;
	for (int i = 0; i < expr.length(); i++)
		if (expr[i] != ' ')
			rez += expr[i];
	expr = rez;
}

Token Lexer::operator[](int pos) //accesez direct elemente din vectorul tokens
{
	if (pos >= 0 && pos < strlen(text))
		return tokens[pos];
	Token t;
	return t;
}

Lexer& Lexer::operator++() // ma deplasez pe urmatorul caracter din text
{
	nextCharacter();
	return *this;
}

ostream& operator<<(ostream& out, Lexer l)
{
	for (int i = 0; i < l.size; i++)
	{
		out << (string)l[i] << " ";
		if ((string)l[i] == "NUM")
			out << "\b:" << (double)l[i] << " ";
	}
	out << "\n";
	return out;
}

istream& operator>>(istream& in, Lexer& l)
{
	string expr;
	cout << "Enter an expression: ";
	in >> expr;
	Lexer aux(expr);
	l = aux;
	return in;
}