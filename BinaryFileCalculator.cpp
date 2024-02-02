#include <iostream>
#include <string>
#include <fstream>
#include "BinaryFileCalculator.h"
#include "Calculator.h"
using namespace std;

BinaryFileCalculator::BinaryFileCalculator() : Calculator()
{
	binaryFileName = "Name not entered";
}

BinaryFileCalculator::BinaryFileCalculator(string expr) : Calculator(expr)
{
	binaryFileName = "Name not entered";
}

BinaryFileCalculator::BinaryFileCalculator(string expr, string binaryFileName) : Calculator(expr)
{
	this->binaryFileName = binaryFileName;
}


void BinaryFileCalculator::setBinaryFileName()
{
	if (binaryFileName == "Name not entered")
	{
		string name;
		cout << "Enter the name of the binary file (.bin is automatically added): ";
		cin >> name;
		name += ".bin";
		binaryFileName = name;
	}
}

void BinaryFileCalculator::serialization()
{
	setBinaryFileName();
	ofstream f(binaryFileName, ios::binary | ios::app);
	double result = getResult();
	f.write((char*)&result, sizeof(result));
	f.close();
}

void BinaryFileCalculator::deserialization(bool& valid)
{
	valid = true;
	ifstream f(binaryFileName, ios::binary);
	if (f.is_open())
	{
		int size = sizeof(double);
		f.seekg(-size, ios::end);
		double result;
		f.read((char*)&result, sizeof(result));
		this->result = result;
	}
	else
	{
		system("cls");
		cout << "The binary file doesn't exist\n";
		valid = false;
	}
}