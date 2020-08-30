#include "places.h"





places::places()
{

	Type = 0;
}

places::places( int type)
{
	
	Type = type;
}

int places::gettype()
{
	return Type;
}

void places::setownership(int)
{
}

int places::getrent()
{
	return 0;
}

int places::getprice()
{
	return 0;
}

int places::getcardtype()
{
	return 0;
}

int places::gettypeofplace()
{
	return 0;
}

int places::getHouse()
{
	return 0;
}

int places::getHotel()
{
	return 0;
}

int places::getmortprice()
{
	return 0;
}

int places::getShop()
{
	return 0;
}

bool places::getWifi()
{
	return false;
}

bool places::getGas()
{
	return false;
}

bool places::getElectricity()
{
	return false;
}

void places::mortgagedd()
{
	
}

bool places::getmortgage()
{
	return false;
}

void places::unmort()
{
}

void places::setrent(int r)
{
}

void places::setHouse(int house)
{
}

void places::setHotel(int hotel)
{
}

void places::setShop(int shop)
{
}

void places::setWifi(bool wifi)
{
}

void places::setGas(bool gas)
{
}

void places::setElectricity(bool electricity)
{
}

places::~places()
{
	
}
