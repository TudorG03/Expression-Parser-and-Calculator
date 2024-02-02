#pragma once
#include <unordered_map>
#include "BinaryFileCalculator.h"

class Option //gestionarea unei optiuni individuale din meniu
{
private:
	string name; //numele functiei (optiunii) din meniu
	unordered_map<int, void (*)(BinaryFileCalculator&)> menuOptions; //asocierea pointer-ului la functia efectiva cu o cheie
public:
	Option();

	Option(int key, void(*func)(BinaryFileCalculator&), string name); //initializarea unui obiect cu datele efective

	void displayOption(); //afisarea numelui optiunii

	void runOption(int key, BinaryFileCalculator& c); //rularea optiunii pe baza cheii
};