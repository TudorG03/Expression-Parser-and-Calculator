#pragma once
#include <fstream>
#include "MenuInputFileOutputScreen.h"

class MenuInputFileOutputFile : public MenuInputFileOutputScreen  //meniul pentru cazul in care user-ul alege input din fisier text si output in alt fisier text
{
private:
	string outputFileName; //numele fisierului in care se vor scrie rezultatele calculelor
	ofstream out; //obiect folosit pentru scrierea in fisierul text
public:
	MenuInputFileOutputFile();

	MenuInputFileOutputFile(string outputFileName);

	void setFileName(); //supradefinirea metodei virtuale din clasa MenuInputFileOutputScreen pentru setarea numelui fisierului in care se vor scrie rezultatele calculelor

	void run(); //supradefinirea metodei virtuale din clasa MenuInputFileOutputScreen care ruleaza meniul in cazul in care user-ul alege input din fisier text si output in alt fisier text
};