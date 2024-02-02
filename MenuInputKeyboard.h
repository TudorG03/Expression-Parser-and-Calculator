#pragma once
#include "Menu.h"

class MenuInputKeyboard : public Menu //meniul pentru cazul in care user-ul alege input de la tastatura
{
public:
	MenuInputKeyboard(); //apeleaza constructorul din Menu

	void run(); //supradefinirea functiei run din Menu care ruleaza meniul pentru cazul in care user-ul alege input de la tastatura
};