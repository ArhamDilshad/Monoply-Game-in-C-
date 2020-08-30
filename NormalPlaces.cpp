#include "NormalPlaces.h"

Normal_places::Normal_places():places()
{
	rent = 0;
	purchase_price = 0;
	mortgaged = false;
	ownership = 0;
    typeof_place = 0;
	mortprice = purchase_price / 2 + rent / 2;
}

int Normal_places::getownership()
{
	return ownership;
}

void Normal_places::setownership(int id)
{
	ownership = id;
}

int Normal_places::getrent()
{
	return rent;
}

void Normal_places::setrent(int r)
{
	rent = r;
}

int Normal_places::getmortprice()
{
	return mortprice;
}

int Normal_places::getprice()
{
	return purchase_price;
}

int Normal_places::gettypeofplace()
{
	return typeof_place;
}

void Normal_places::unmort()
{
	mortgaged = false;
}

void Normal_places::setprice(int price)
{
	purchase_price=price;
}

void Normal_places::mortgagedd()
{
	mortgaged=true;

}

bool Normal_places::getmortgage()
{
	return mortgaged;
}

Normal_places::~Normal_places()
{
}

Normal_places::Normal_places(int rent1, int purchase_price1, int ownership1, bool mortgaged1, int typeof_place1, int type):places(type)
{
	rent = rent1;
	purchase_price = purchase_price1;
	mortgaged = mortgaged1;
	ownership = ownership1;
	typeof_place= typeof_place1;
	mortprice = purchase_price / 2 + rent / 2;
}



int Normal_places::getHouse()
{
	return U.getHouse();
}

int Normal_places::getHotel()
{
	return U.getHotel();
}

int Normal_places::getShop()
{
	return U.getShop();
}

bool Normal_places::getWifi()
{
	return U.getWifi();
}

bool Normal_places::getGas()
{
	return U.getGas();
}

bool Normal_places::getElectricity()
{
	return U.getElectricity();
}

void Normal_places::setHouse(int house)
{
	U.setHouse(house);
}

void Normal_places::setHotel(int hotel)
{
	U.setHotel(hotel);
}

void Normal_places::setShop(int shop)
{
	U.setShop(shop);
}

void Normal_places::setWifi(bool wifi)
{
	U.setWifi(wifi);
}

void Normal_places::setGas(bool gas)
{
	U.setGas(gas);
}

void Normal_places::setElectricity(bool electricity)
{
	U.setElectricity(electricity);
}

