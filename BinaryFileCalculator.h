#pragma once
#include "Calculator.h"
using namespace std;

class BinaryFileCalculator : public Calculator //adauga in plus fata de clasa Calculator optiunea de a salva rezultate in fisiere binare
{
private:
	string binaryFileName; //numele fisierului binar
public:
	BinaryFileCalculator();

	BinaryFileCalculator(string expr);

	BinaryFileCalculator(string expr, string binaryFileName);

	void setBinaryFileName(); //setter pentru numele fisierului binar

	void serialization(); //scrierea rezultatului curent in fisierul binar

	void deserialization(bool& valid); //extragerea ultimului rezultat din fisierul binar
};