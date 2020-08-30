#pragma once
#include<iostream>
using namespace std;


class places
{
protected:

	int Type; //1- Normal Places, 2- Special Places, 3- Cards, 4- Corners
public:
	places();
	places( int type );
	int gettype();
	virtual int getownership() = 0;
	virtual void setownership(int);
	virtual int getrent();
	virtual int getprice();
	virtual int getcardtype();
	virtual int gettypeofplace();
	virtual int getHouse();
	virtual int getHotel();
	virtual int getmortprice();
	virtual int getShop();
	virtual bool getWifi();
	virtual bool getGas();
	virtual bool getElectricity();
	virtual void mortgagedd();
	virtual bool getmortgage();
	virtual void unmort();

	virtual void setrent(int r);
	virtual void setHouse(int house);
	virtual void setHotel(int hotel);
	virtual void setShop(int shop);
	virtual void setWifi(bool wifi);
	virtual void setGas(bool gas);
	virtual void setElectricity(bool electricity);
	virtual ~places();
	
};

