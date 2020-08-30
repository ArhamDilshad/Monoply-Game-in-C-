#pragma once
#include"places.h"
#include <fstream>
class Player
{
protected:
	char* name;                  
	int position;                 //index of board on which the player is
	int money;
	int jail;                     //2 or 1 if the player is in jail otherwise 0
	bool jailcard;                //true if owned
	bool bankrupt;
	int sizepropertieowned;
	int* propertiesowned;         //contains indexes of properties owned
	int noOfpropowned[7];         //contains the number of properties owned of each group
	
public:
	Player();
	Player(char* n);
	void setpostition(int pos);
	int getposition();
	int getmoney();
	int getjail();
	void setjail(int jaill);
	bool getjailcard();
	void setjailcard(bool);
	void setmoney(int mon);
	void printprop();
	void deletepropowned();
	bool getbankruptcy();
	void setbankruptcy();
	void printplayer();
	int getsizepropowned();
	int getpropowned(int index);
	void updatepropertiesowned(int place);
	void setsizepropowned(int);
	void updatenoOfpropowned(int typeofplace);
	int getnoOfpropowned(int typeofplace);
	~Player();
	void savePlayerData();
	void loadPlayerData();
};

