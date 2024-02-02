#include <iostream>
#include <stdlib.h>
#include "MenuInputFileOutputFile.h"
using namespace std;

MenuInputFileOutputFile::MenuInputFileOutputFile() : MenuInputFileOutputScreen()
{
	outputFileName = "rezultate.txt";
}

MenuInputFileOutputFile::MenuInputFileOutputFile(string outputFileName) : MenuInputFileOutputScreen()
{
	this->outputFileName = outputFileName;
}

void MenuInputFileOutputFile::setFileName()
{
	cout << "Enter the name for the text file that will store the results (.txt automatically added): ";
	string name;
	cin >> name;
	name += ".txt";
	outputFileName = name;
}

void MenuInputFileOutputFile::run()
{
	system("cls");
	MenuInputFileOutputScreen::setFileName();
	try {
		ifstream f;
		ofstream f1;
		f.open(getFilePath());
		if (!f.is_open())
			throw invalid_argument("\nFile path specified doesn't exist!\n");
		setFileName();
		f1.open(outputFileName);
		while (f >> *this)
		{
			Calculator c(getExpression());
			f1 << c;
		}
		f.close();
		f1.close();
	}
	catch (invalid_argument& e)
	{
		cout << e.what();
	}
}