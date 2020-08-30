#include "Chance.h"



Chance::Chance() :Card()
{
	instruction = nullptr;
}

Chance::Chance(char* ins, int type,int t) : Card(type,t)
{
	instruction = new char[strlen(ins) + 1];
	strcpy_s(instruction, strlen(ins) + 1, ins);
}

void Chance::print()
{
	cout <<"Chance card: "<<instruction << endl;
}

int Chance::getownership()
{
	return 0;
}

Chance::~Chance()
{
	if (instruction != nullptr)
		delete[]instruction;
}
