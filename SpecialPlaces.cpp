#include "SpecialPlaces.h"

SpecialPlaces::SpecialPlaces():places()
{
	rent = 0;
	purchase_price = 0;
	mortgaged = false;
	ownership = 0;
	typeof_place = 0;
	mortprice = purchase_price / 2 + rent / 2;

}
SpecialPlaces::SpecialPlaces(int rent1, int purchase_price1, int ownership, bool mortgaged1, int typeofplace, int type) :places(type)
{

	rent = rent1;
	purchase_price = purchase_price1;
	this->ownership = ownership;
	mortgaged = mortgaged1;
	typeof_place = typeofplace;
	mortprice = purchase_price / 2 + rent / 2;
}
int SpecialPlaces::getrent()
{
	return rent;
}
int SpecialPlaces::getprice()
{
	return purchase_price;
}
int SpecialPlaces::getownership()
{
	return ownership;
}
void SpecialPlaces::setownership(int id)
{
	ownership = id;
}
void SpecialPlaces::unmort()
{
	mortgaged = false;
}
int SpecialPlaces::getmortprice()
{
	return mortprice ;
}
void SpecialPlaces::mortgagedd()
{
	mortgaged = true;
}
bool SpecialPlaces::getmortgage()
{
	return mortgaged;
}
int SpecialPlaces::gettypeofplace()
{
	return typeof_place;
}


SpecialPlaces::~SpecialPlaces()
{
}
