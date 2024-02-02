#pragma once
#include "Menu.h"

void stop(BinaryFileCalculator& c); //opreste executia programului

void changeMode(BinaryFileCalculator& c); //comuta interfata la meniul principal unde user-ul poate schimba sursa input-ului

void binaryFile(BinaryFileCalculator& c); //adauga rezultatul curent in fisierul binar

void calculateWithLastSavedResult(BinaryFileCalculator& c); //permite user-ului sa introduca o expresie de la tastatura care vine cu rezultatul salvat anterior preintrodus, rezultatul fiind afisat pe ecran

void displayBinaryFile(BinaryFileCalculator& c); //afiseaza pe ecran ultimul rezultat salvat in fisierul binar

void calculus(BinaryFileCalculator& c); //permite user-ului sa introduca o expresie de la tastatura, rezultatul fiind afisat pe ecran

int initCalculator(); //meniul principal al aplicatiei care permite user-ului sa aleaga sursa input-ului

Menu* chooseInputType(int mode); //functie care asociaza pointerului la Menu un obiect derivat din Menu pe baza alegerii unei optiuni din meniul principal

