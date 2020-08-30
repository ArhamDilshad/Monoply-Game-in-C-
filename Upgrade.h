#pragma once
class Upgrade
{
protected:
	int House;
	int Hotel;
	int Shop;
	bool Wifi;
	bool Gas;
	bool Electricity;
public:
	Upgrade();
	~Upgrade();

	//getters
	int getHouse();
	int getHotel();
	int getShop();
	bool getWifi();
	bool getGas();
	bool getElectricity();

	//setters
	void setHouse(int house);
	void setHotel(int hotel);
	void setShop(int shop);
	void setWifi(bool wifi);
	void setGas(bool gas);
	void setElectricity(bool electricity);
};

