
#include "Cards.h"
#pragma once

class CommunityChest :
	public Card
{
	char* instruction;
public:
	CommunityChest();
	CommunityChest(char* ins,int type,int t);
	void print();
	int getownership();
	~CommunityChest();
};

