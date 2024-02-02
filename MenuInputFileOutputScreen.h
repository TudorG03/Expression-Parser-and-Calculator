#pragma once
#include "Menu.h"

class MenuInputFileOutputScreen : public Menu //meniul pentru cazul in care user-ul alege input din fisier text si output pe ecran
{
private:
	string filePath; //numele si/sau calea fisierului din care se citesc expresiile
	string expression; //expresia curenta extrasa din fisierul text
public:
	MenuInputFileOutputScreen();

	MenuInputFileOutputScreen(string filePath);

	virtual void setFileName(); //metoda virtuala care permite setarea numelui fisierului text din care se vor citi expresiile

	string getFilePath(); //getter

	string getExpression(); //getter

	virtual void run(); //metoda virtuala si supradefinita din clasa Menu care ruleaza meniul in cazul in care user-ul alege input din fisier text si output pe ecran

	friend ifstream& operator>>(ifstream& f, MenuInputFileOutputScreen& m); //supraincarcarea operatorului de citire pentru citirea din fisier text
};