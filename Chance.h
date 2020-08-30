#pragma once
#include"Cards.h"
class Chance :
	public Card
{
	char* instruction;
public:
	Chance();
	Chance(char* ins,int type, int t);
	void print();
	int getownership();
	~Chance();
};

