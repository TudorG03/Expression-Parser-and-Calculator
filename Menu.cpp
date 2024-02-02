#include <unordered_map>
#include "Menu.h"
#include "BinaryFileCalculator.h"
#include "Option.h"
#include "functii.h"
using namespace std;

Menu::Menu()
{
	addOption(0, stop, "Exit Calculator");
	addOption(1, changeMode, "Change input mode");
}

BinaryFileCalculator Menu::getCfb()
{
	return cfb;
}

void Menu::addOption(int key, void(*func)(BinaryFileCalculator&), string name)
{
	Option opt(key, func, name);
	setMenuOptions(key, opt);
}

void Menu::setMenuOptions(int key, Option opt)
{
	menuOptions[key] = opt;
}
