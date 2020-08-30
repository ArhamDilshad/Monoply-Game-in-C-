#include "Upgrade.h"



Upgrade::Upgrade()
{
	House = 0;
	Hotel = 0;
	Shop = 0;
	Wifi = false;
	Gas = false;
	Electricity = false;
}


Upgrade::~Upgrade()
{
}



int Upgrade::getHouse()
{
	return House;
}

int Upgrade::getHotel()
{
	return Hotel;
}

int Upgrade::getShop()
{
	return Shop;
}

bool Upgrade::getWifi()
{
	return Wifi;
}

bool Upgrade::getGas()
{
	return Gas;
}

bool Upgrade::getElectricity()
{
	return Electricity;
}



void Upgrade::setHouse(int house)
{
	House = house;
}

void Upgrade::setHotel(int hotel)
{
	Hotel = hotel;
}

void Upgrade::setShop(int shop)
{
	Shop = shop;
}

void Upgrade::setWifi(bool wifi)
{
	Wifi = wifi;
}

void Upgrade::setGas(bool gas)
{
	Gas = gas;
}

void Upgrade::setElectricity(bool electricity)
{
	Electricity = electricity;
}
