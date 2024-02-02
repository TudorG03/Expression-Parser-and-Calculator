#pragma once
#include <unordered_map>
#include "BinaryFileCalculator.h"
#include "Option.h"

class Menu //clasa abstracta din care s-a derivat fiecare tip de meniu
{
public:
	unordered_map<int, Option> menuOptions; //asocierea obiectelor de tip Option cu o cheie
	BinaryFileCalculator cfb; //obiect folosit la calcule si stocarea rezultatelor in fisiere binare

	Menu();

	BinaryFileCalculator getCfb(); //getter

	void addOption(int key, void(*func)(BinaryFileCalculator&), string name); //initializarea unui obiect de tip Option si apelarea setter-ului pentru unordered_map

	void setMenuOptions(int key, Option opt); //adaugarea unei optiuni in unordered_map

	virtual void run() = 0; //functie pur virtuala responsabila cu rularea meniului
};