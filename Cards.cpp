#include"Cards.h"
#include<iostream>
using namespace std;

Card::Card()
{
	cardtype = 0;  
}
Card::Card(int type,int t):places(t)
{
	cardtype = type;
}
int Card::getcardtype() 
{
	return cardtype;
}
int Card::getownership()
{
	return 0;
}
void Card::print()
{
}
Card::~Card()
{
	cardtype = 0;
}
//void Card::communitycard()
//{
//
//}
//void Card::chancecard()
//{
//
//}
//void Card::cardfunction(int type)
//{
//	//cardtype = 1;
//	if (cardtype==1)
//	{
//		communitycard();
//    }
//	if (cardtype == 2)
//	{
//		chancecard();
//	}
//
//}