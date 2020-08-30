#include"places.h"
#include"Upgrade.h"

class Normal_places:public places {
protected:
	int rent;                         //rent of the particular normal place.
	int purchase_price;               //purchase price of the particular normal place.
	bool mortgaged;                   //true if the place is mortgaged else false.
	int mortprice;
	int ownership;                    //specifies which player owns the place.
	int typeof_place;                 //which type of place e.g. iqbal,johar,model town etc. 
	Upgrade U;

public:
	Normal_places();
	int getownership();
	void setownership(int id);
	int getprice();
	int gettypeofplace();
	void unmort();
	void setprice(int price);
	void mortgagedd();
	bool getmortgage();
	~Normal_places();
	Normal_places(int rent1, int purchase_price1, int ownership, bool mortgaged1,int typeof_place1, int type);

	int getrent();
	void setrent(int r);

	int getmortprice();
	

	int getHouse();
	int getHotel();
	int getShop();
	bool getWifi();
	bool getGas();
	bool getElectricity();

	void setHouse(int house);
	void setHotel(int hotel);
	void setShop(int shop);
	void setWifi(bool wifi);
	void setGas(bool gas);
	void setElectricity(bool electricity);

};