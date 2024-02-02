#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "MenuInputFileOutputScreen.h"
#include "Menu.h"
using namespace std;

MenuInputFileOutputScreen::MenuInputFileOutputScreen() : Menu()
{
	filePath = "No path provided!";
	expression = "N/A";
}

MenuInputFileOutputScreen::MenuInputFileOutputScreen(string filePath) : Menu()
{
	this->filePath = filePath;
	expression = "N/A";
}

void MenuInputFileOutputScreen::setFileName()
{
	cout << "\nEnter the path of the file containing the expressions: ";
	string ans;
	cin >> ans;
	filePath = ans;
}

string MenuInputFileOutputScreen::getFilePath()
{
	return filePath;
}

string MenuInputFileOutputScreen::getExpression()
{
	return expression;
}

void MenuInputFileOutputScreen::run()
{
	system("cls");
	setFileName();
	try {
		ifstream f;
		f.open(filePath);
		if (!f.is_open())
			throw invalid_argument("\nFile path specified doesn't exist!\n");
		while (f >> *this)
		{
			Calculator c(expression);
			cout << c;
		}
		f.close();
	}
	catch (invalid_argument& e)
	{
		cout << e.what();
	}
}

ifstream& operator>>(ifstream& f, MenuInputFileOutputScreen& m)
{
	if (f.is_open())
	{
		getline(f, m.expression);
	}
	return f;
}