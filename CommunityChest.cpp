#include "CommunityChest.h"



CommunityChest::CommunityChest():Card()
{
	instruction = nullptr;
}
CommunityChest::CommunityChest(char*ins,int type,int t):Card(type,t)
{
	instruction = new char[strlen(ins) + 1];
	strcpy_s(instruction, strlen(ins) + 1, ins);
}

void CommunityChest::print()
{
	cout << "Chest card: " << instruction << endl;
}

int CommunityChest::getownership()
{
	return 0;
}

CommunityChest::~CommunityChest()
{
	if (instruction != nullptr)
		delete[]instruction;
}
