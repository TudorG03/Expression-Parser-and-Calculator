#include <iostream>
#include <stdlib.h>
#include <string>
#include "MenuInputKeyboard.h"
#include "Menu.h"
using namespace std;

MenuInputKeyboard::MenuInputKeyboard() : Menu() {}

void MenuInputKeyboard::run()
{
	string in;
	while (true)
	{
		cout << "\n======================================";
		cout << "\nChoose an option:\n\n";
		for (auto it = menuOptions.begin(); it != menuOptions.end(); it++)
		{
			cout << it->first << ": ";
			it->second.displayOption();
			cout << "\n";
		}
		cout << "======================================\n\n";
		cout << "Your option: ";
		cin >> in;
		char digit = in[0];
		if (in.length() == 1 && isdigit(digit))
		{
			int option = stoi(in);
			if (option == 1)
				break;
			if (menuOptions.find(option) != menuOptions.end())
				menuOptions[option].runOption(option, cfb);
			else
			{
				system("cls");
				cout << "\nInvalid Option!\n";
			}
		}
		else
		{
			system("cls");
			cout << "\nInvalid Option!\n";
		}
	}
}