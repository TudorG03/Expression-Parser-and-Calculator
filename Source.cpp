//Gheorghiu Calin Tudor - grupa 1055
//Nota: exista un fisier text cu numele expressions.txt care contine toate expresiile de evaluat din cerintele proiectului (faza 1 + faza 2) pentru testarea functionalitatii de citire din fisiere text
#include <iostream>
#include <string>
#include "Menu.h"
#include "Calculator.h"
#include "functii.h"
using namespace std;


int main(int argc, char** argv)
{
	//Main Faza 1
	//exemple de utilizare (putem alege oricare din urmatoarele metode)

	//Calculator c("1 + 1"); // putem transmite expresii prin constructorul cu parametri 
	//cout << c; // putem afisa rezultatul

	//c.setExpression("1 + 2"); // putem transmite expresii prin setter 
	//cout << c; // putem afisa rezultatul

	//cin >> c; // putem transmite expresii prin citire de la tastatura 
	//cout << c; // putem afisa rezultatul

	//cout << "S-au efectuat " << Parser::getParserCount() << " calcule.\n\n"; // putem afisa cate calcule s-au efectuat

	//c(); // putem sa facem calcule consecutive pana cand se introduce exit (se afiseaza si numarul de calcule efectuate la final implicit)

	//Main Faza 2
	Calculator c;
	if (argv[1]) //argumentul trebuie introdus intre ghilimele pentru a fi interpretat ca string
	{
		c.setExpression(argv[1]);
		cout << c;
		return 0;
	}

	while (true)
	{
		Menu* m;
		m = chooseInputType(initCalculator());
		m->addOption(2, calculus, "Calculate");
		m->addOption(3, calculateWithLastSavedResult, "Calculate using last result");
		//m->addOption(4, binaryFile, "Save result in binary file");
		m->addOption(4, displayBinaryFile, "Show last result from binary file");
		m->run();
	}
	return 0;
}