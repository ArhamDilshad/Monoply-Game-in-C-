#include"places.h"
#include"Player.h"
#include"Cards.h"
#include"Chance.h"
#include"CommunityChest.h"
#include<ctime>
#pragma once
class Monopoly
{
	int totalplayers;
	places**place;
	Player** players;
	Card** chance;
	Card** communitychest;
	int bank;
	int dice;
	int currentplayer;
	int currentchance;
	int currentcommunitychest;
	int activeplayers;
public:
	Monopoly(int tp);
	void changeplayer();
	void printplayersinfo();
	void rolldice();
	void moveplayer();
	void mortgage();
	void unmortgage();
	int winnercheck();
	void bidding(int pos);
	int getdice();
	~Monopoly();
	void print_board(int);
	void savedata();
	void loaddata();
};

