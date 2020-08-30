#include"places.h"


class SpecialPlaces
	:public places
{
protected:
	int rent;                      //rent of the station/utility
	int purchase_price;            //purchase price of station/utility
	bool mortgaged;
	int mortprice;
	int ownership;                 //ID of owner, 0 if unowned
	int typeof_place;
public:
	SpecialPlaces();
	int getrent();
	int getprice();
	int getownership();
	void setownership(int id);
	void unmort();
	int getmortprice();
	void mortgagedd();
	bool getmortgage();
	int gettypeofplace();
	SpecialPlaces(int rent1, int purchase_price1, int ownership, bool mortgaged1,int typeofplace, int);
	~SpecialPlaces();

};