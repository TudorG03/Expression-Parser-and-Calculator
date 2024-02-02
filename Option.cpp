#include <iostream>
#include <unordered_map>
#include "Option.h"
#include "BinaryFileCalculator.h"
using namespace std;

Option::Option() = default;

Option::Option(int key, void(*func)(BinaryFileCalculator&), string name)
{
	this->name = name;
	menuOptions[key] = func;
}

void Option::displayOption()
{
	cout << name;
}

void Option::runOption(int key, BinaryFileCalculator& c)
{
	menuOptions[key](c);
}