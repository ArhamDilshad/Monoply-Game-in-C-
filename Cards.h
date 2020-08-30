#include"places.h"
#include<iostream>
#pragma once
using namespace std;


class Card :public places
{
protected:
	int cardtype;  //card type that define whether its a comunity card or of chance card//

public:
	Card();
	Card(int,int);
	int getcardtype();
    int getownership();
	virtual void print();
	virtual ~Card();
	//void communitycard();
	//void chancecard();
	//void cardfunction(int );
	

};