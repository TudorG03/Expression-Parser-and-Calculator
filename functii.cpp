#include <iostream>
#include <stdlib.h>
#include "functii.h"
#include "BinaryFileCalculator.h"
#include "MenuInputKeyboard.h"
#include "MenuInputFileOutputScreen.h"
#include "MenuInputFileOutputFile.h"
using namespace std;

void stop(BinaryFileCalculator& c)
{
	exit(0);
}

void changeMode(BinaryFileCalculator& c) { cout << "caca\n", system("cls"); }

void binaryFile(BinaryFileCalculator& c)
{
	cin.ignore();
	cin >> c;
	c.serialization();
	cout << c << "\n";
}

void calculateWithLastSavedResult(BinaryFileCalculator& c)
{
	bool valid;
	c.deserialization(valid);
	if (valid)
	{
		string aux;
		if (fabs(c.getResult() - (int)c.getResult()) < 0.01)
			aux = to_string((int)c.getResult());
		else
			aux = c.removeTraillingZeros(c.getResult());
		system("cls");
		cout << "Enter an expression to calculate: " << aux;
		string ans;
		cin >> ans;
		aux += ans;
		BinaryFileCalculator b(aux);
		cout << b << "\n";
		c.setExpression(to_string(b.getResult()));
		c.setResult();
		c.serialization();
	}
}

void displayBinaryFile(BinaryFileCalculator& c)
{
	bool valid;
	c.deserialization(valid);
	if (valid)
	{
		system("cls");
		cout << "The last saved result was: ";
		cout << c.getResult() << "\n";
	}
}

void calculus(BinaryFileCalculator& c)
{
	cin.ignore();
	system("cls");
	cin >> c;
	cout << c << "\n";
	c.serialization();
}

int initCalculator()
{
	string ans;
	do
	{
		cout << "\nWhere do you want the calculator to get the input from (1 = keyboard, 2 = file + output screen, 3 = file + output file, 4 = exit): ";
		cin >> ans;
		system("cls");
		if (ans != "1" && ans != "2" && ans != "3" && ans != "4")
			cout << "Please choose a valid option!\n";
		if (ans == "4")
			exit(0);
	} while (ans != "1" && ans != "2" && ans != "3");
	return stoi(ans);
}

Menu* chooseInputType(int mode)
{
	if (mode == 1)
		return new MenuInputKeyboard;
	else
		if (mode == 2)
			return new MenuInputFileOutputScreen;
		else
			return new MenuInputFileOutputFile;
}