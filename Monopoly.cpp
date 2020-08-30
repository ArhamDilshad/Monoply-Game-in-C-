#include "Monopoly.h"
#include<fstream>
#include"places.h"
#include"Corners.h"
#include"Chance.h"
#include"NormalPlaces.h"
#include"CommunityChest.h"
#include"Cards.h"
#include"SpecialPlaces.h"
#include<windows.h>
#include"Header.h"
#include<conio.h>

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

Monopoly::Monopoly(int tp)
{
	totalplayers = tp;
	place = new places * [40];

	//setting board
	place[0] = new Corners(4);
	place[1] = new Normal_places(80, 200, 0, false, 2, 1);            //johar town a
	place[2] = new Card(2, 3);                                        //community chest
	place[3] = new Normal_places(90, 250, 0, false, 2, 1);            //johar town b
	place[4] = new Corners(4);                                        //tax                                  
	place[5] = new SpecialPlaces(200, 2000, 0, false, 1, 2);          //metro
	place[6] = new Normal_places(60, 250, 0, false, 1, 1);            //iqbal town a
	place[7] = new Card(1, 3);                                        //chance
	place[8] = new Normal_places(70, 300, 0, false, 1, 1);            //iqbal town b
	place[9] = new Normal_places(100, 400, 0, false, 1, 1);           //iqbal town c
	place[10] = new Corners(4);                                       //jail
	place[11] = new Normal_places(100, 300, 0, false, 3, 1);          //faisal town a
	place[13] = new Normal_places(130, 400, 0, false, 3, 1);          //faisal town b
	place[14] = new Normal_places(130, 400, 0, false, 3, 1);          //faisal town c
	place[12] = new SpecialPlaces(450, 5000, 0, false, 2, 2);         //lesco
	place[15] = new SpecialPlaces(350, 2500, 0, false, 1, 2);         //railway station
	place[16] = new Normal_places(200, 800, 0, false, 4, 1);          //model town a
	place[17] = new Card(2, 3);                                       //community chest
	place[18] = new Normal_places(250, 850, 0, false, 4, 1);          //model town b
	place[19] = new Normal_places(500, 2000, 0, false, 4, 1);         //model town c
	place[20] = new Corners(4);                                       //free parking
	place[21] = new Normal_places(300, 1000, 0, false, 5, 1);         //gulberg a
	place[22] = new Card(1, 3);                                       //chance
	place[23] = new Normal_places(350, 1200, 0, false, 5, 1);         //gulberg b
	place[24] = new Normal_places(600, 2500, 0, false, 5, 1);         //gulberg c
	place[25] = new SpecialPlaces(200, 2000, 0, false, 1, 2);         //bus station
	place[26] = new Normal_places(500, 2000, 0, false, 6, 1);         //dha a
	place[27] = new Normal_places(500, 2000, 0, false, 6, 1);         //dha b
	place[28] = new SpecialPlaces(400, 4000, 0, false, 2, 2);         //lesco
	place[29] = new Normal_places(1000, 2500, 0, false, 6, 1);        //dha c
	place[30] = new Corners(4);                                       //go to jail
	place[31] = new Normal_places(800, 2500, 0, false, 7, 1);         //bahria a
	place[32] = new Normal_places(900, 3000, 0, false, 7, 1);         //bahria b
	place[33] = new Card(2, 3);                                       //community chest
	place[34] = new Normal_places(1000, 3000, 0, false, 7, 1);        //bahria c
	place[35] = new SpecialPlaces(350, 2500, 0, false, 1, 2);         //orange train
	place[36] = new Card(1, 3);                                       //chance
	place[37] = new Corners(4);                                       //parking rs 10                
	place[38] = new SpecialPlaces(350, 2500, 0, false, 2, 2);         //sui
	place[39] = new SpecialPlaces(500, 8000, 0, false, 2, 2);         //PTCL






	players = new Player * [totalplayers];
	for (int i = 0; i < totalplayers; i++) {
		char* name;
		char temp[30];
		cout << "\nEnter Player " << i + 1 << " name: ";
		cin.getline(temp, 30, ',');
		name = new char[strlen(temp) + 1];
		strcpy_s(name, strlen(temp) + 1, temp);
		players[i] = new Player(name);
		delete[]name;
	}


	chance = new Card * [15];
	ifstream fin("Chance.txt");
	char buffer[300];
	for (int i = 0; i < 15; i++) {
		fin.getline(buffer, 300, ';');
		char* temp = new char[strlen(buffer) + 1];

		strcpy_s(temp, strlen(buffer) + 1, buffer);
		chance[i] = new Chance(temp, 1, 3);
		delete[]temp;

	}
	fin.close();
	communitychest = new Card * [15];
	ifstream finn("CommunityChest.txt");
	for (int i = 0; i < 15; i++) {
		finn.getline(buffer, 300, ';');
		char* temp = new char[strlen(buffer) + 1];
		strcpy_s(temp, strlen(buffer) + 1, buffer);
		chance[i] = new CommunityChest(temp, 2, 3);
		delete[]temp;

	}
	finn.close();

	bank = 50000;
	currentplayer = 1;
	currentchance = 0;
	currentcommunitychest = 0;
	dice = 0;
	activeplayers = totalplayers;
}

void Monopoly::changeplayer()
{
	currentplayer++;
	if (currentplayer > totalplayers)
		currentplayer = 1;
}

void Monopoly::printplayersinfo()
{
	for (int i = 0; i < totalplayers; i++) {
		players[i]->printplayer();
		cout << endl;
	}
}

void Monopoly::rolldice()
{
	if (players[currentplayer - 1]->getbankruptcy() == false) {
		cout << "\nPlayer " << currentplayer << "'s turn\n";
		srand(time(0));
		dice = (rand() % 6) + 1;
		cout << dice << endl;
	}

	/*cin >> dice;*/



}

void Monopoly::moveplayer()
{



	if (players[currentplayer - 1]->getbankruptcy() == false) {
		if (players[currentplayer - 1]->getmoney() < 0) {
			cout << "Do you want to\n1-Declare Bankruptcy\n2-Mortgage Properties\n";
			int choice;
			cin >> choice;
			if (choice == 1) {
				players[currentplayer - 1]->setbankruptcy();
				cout << "\nPlayer " << currentplayer << " is bankrupt now and is out of the game.\n";
				activeplayers--;
				for (int i = 0; i < players[currentplayer - 1]->getsizepropowned(); i++) {
					place[players[currentplayer - 1]->getpropowned(i)]->setownership(0);                //giving properties back to the bank after bankruptcy
					players[currentplayer - 1]->deletepropowned();
					players[currentplayer - 1]->setsizepropowned(0);
				}
			}
			if (choice == 2) {
				mortgage();
			}
		}
		if (players[currentplayer - 1]->getjail() == 0) {
			int position, typeofplace;
			players[currentplayer - 1]->setpostition(dice);

			while (true) {
				position = players[currentplayer - 1]->getposition();
				typeofplace = place[position]->gettype();

				if (typeofplace == 1) {
					int own = place[position]->getownership();
					int rent = place[position]->getrent();
					int money1, money2;
					if (own != currentplayer) {

						if (own == 0) {
							cout << "Do you want to purchase this place for " << place[position]->getprice() << "? [1-Yes, 2-No]\n";
							int choice;
							cin >> choice;
							money2 = players[currentplayer - 1]->getmoney();
							if (money2 < place[position]->getprice())
								choice = 2;
							if (choice == 1) {

								money2 = place[position]->getprice();
								place[position]->setownership(currentplayer);
								players[currentplayer - 1]->setmoney(-money2);
								players[currentplayer - 1]->updatepropertiesowned(position);
								int typeofplace = place[position]->gettypeofplace();
								players[currentplayer - 1]->updatenoOfpropowned(typeofplace);
								cout << "\nIt is now your property\n";
								break;

							}
							if (choice == 2) {
								bidding(position);
								break;

							}
						}
						else {
							for (int i = 1; i <= totalplayers; i++)
							{
								if (own == i && place[position]->getmortgage() == false) {
									money1 = rent;
									money2 = -rent;
									players[i - 1]->setmoney(money1);
									players[currentplayer - 1]->setmoney(money2);
									cout << "\nRent paid Rs " << place[position]->getrent() << " to Player " << i << endl;
									break;
								}
								else if (place[position]->getmortgage() == true) {
									cout << "\nDo you want to buy this property?[1-Yes, 2-No] ";
									int x;
									cin >> x;
									if (x == 1) {

										place[position]->setownership(currentplayer);

										int typeofplace = place[position]->gettypeofplace();
										players[currentplayer - 1]->updatenoOfpropowned(typeofplace);
										cout << "\nIt is now your property\nDo you want to unmortgage it\n1-Now\n2-Later\n";
										int m;
										cin >> m;
										if (m == 1) {
											unmortgage();
										}
										if (m == 2) {
											int pay = place[position]->getmortprice() * 20 / 100;
											players[currentplayer - 1]->setmoney(-pay);
											bank = bank + pay;
										}
										break;
									}
								}
							}
						}


					}
					else {
						//add check to ask if the player wants to upgrade his properties
						if (place[players[currentplayer - 1]->getposition()]->getmortgage() == true) {
							cout << "\nPROPERTY MORTGAGED\nDo you want to unmortgage it? [1-Yes,2-No]\n";
							int m;
							cin >> m;
							if (m == 1) {
								unmortgage();
								break;
							}
							if (m == 2)
								break;
						}
						position = players[currentplayer - 1]->getposition();
						int noofproperties;
						int typeofplace = place[position]->gettypeofplace();
						noofproperties = players[currentplayer - 1]->getnoOfpropowned(typeofplace);
						bool canbuild = false;
						if (typeofplace == 2)
						{
							if (noofproperties == 2)
								canbuild = true;
						}
						else {
							if (noofproperties == 3)
								canbuild = true;
						}
						if (canbuild == true) {
							int x = 1;
							while (x != 2) {
								cout << "Do you want to upgrade? [1-Yes, 2-No]\n";

								cin >> x;
								if (x == 1) {

									cout << "What do you want to upgrade? \n";
									cout << "1- Gas\n ";

									cout << "2-Electricity\n ";

									cout << "3-WiFi\n";

									cout << "4-House\n";
									int y;
									cin >> y;
									if (y == 1 && place[position]->getGas() == true)
										cout << "Gas is already connected\n";
									if (y == 1 && place[position]->getGas() == false) {
										place[position]->setGas(true);
										place[position]->setrent(place[position]->getrent() + (place[position]->getrent() * 20 / 100));
										break;
									}
									if (y == 2 && place[position]->getElectricity() == true)
										cout << "Electricity is already connected\n";
									if (y == 2 && place[position]->getElectricity() == false) {
										place[position]->setElectricity(true);
										place[position]->setrent(place[position]->getrent() + (place[position]->getrent() * 20 / 100));
										break;
									}
									if (y == 3 && place[position]->getWifi() == true)
										cout << "Wifi is already installed";
									if (y == 3 && place[position]->getWifi() == false) {
										place[position]->setWifi(true);
										place[position]->setrent(place[position]->getrent() + (place[position]->getrent() * 10 / 100));
										break;
									}
									if (y == 4)
									{
										if (place[position]->getHotel() == 1 && place[position]->getHouse() == 2)
											cout << "No more space\n";
										else
										{
											place[position]->setHouse(place[position]->getHouse() + 1);
											place[position]->setrent(place[position]->getrent() + (place[position]->getrent() * 30 / 100));

											if (place[position]->getHouse() == 3)
											{
												place[position]->setHotel(1);
												place[position]->setHouse(0);
												place[position]->setrent(place[position]->getrent() + (place[position]->getrent() * 10 / 100));
											}
											break;
										}

									}

								}
							}
						}
					}
				}
				if (typeofplace == 2) {


					int own = place[position]->getownership();
					int rent = place[position]->getrent();
					int money1, money2;
					if (own != currentplayer) {
						if (own == 0) {
							cout << "Do you want to purchase this place for " << place[position]->getprice() << "? [1-Yes, 2-No]\n";
							int choice;
							cin >> choice;
							if (choice == 1) {
								money2 = players[currentplayer - 1]->getmoney();
								money2 = place[position]->getprice();
								players[currentplayer - 1]->setmoney(-money2);
								place[position]->setownership(currentplayer);
								players[currentplayer - 1]->updatepropertiesowned(position);
								cout << "\nIt is now your property\n";
								break;
							}
							if (choice == 2) {
								//auction
								bidding(position);
								break;
							}
						}
						else {
							for (int i = 1; i <= totalplayers; i++)
							{
								if (own == i && place[position]->getmortgage() == false) {

									money1 = rent;
									money2 = -rent;
									players[i - 1]->setmoney(money1);
									players[currentplayer - 1]->setmoney(money2);
									cout << "\nRent paid Rs " << place[position]->getrent() << " to Player " << i << endl;
									break;
								}
								else if (place[position]->getmortgage() == true) {
									cout << "\nDo you want to buy this property?[1-Yes, 2-No] ";
									int x;
									cin >> x;
									if (x == 1) {
										players[currentplayer - 1]->setmoney(-(place[position]->getprice()));
										place[position]->setownership(currentplayer);
										int typeofplace = place[position]->gettypeofplace();
										players[currentplayer - 1]->updatenoOfpropowned(typeofplace);
										cout << "\nIt is now your property\nDo you want to unmortgage it\n1-Now\n2-Later\n";
										int m;
										cin >> m;
										if (m == 1) {
											unmortgage();
										}
										if (m == 2) {
											int pay = place[position]->getmortprice() * 20 / 100;
											players[currentplayer - 1]->setmoney(-pay);
											bank = bank + pay;
										}
										break;
									}
								}
							}
						}
					}
					else {
						if (place[players[currentplayer - 1]->getposition()]->getmortgage() == true) {
							cout << "\nPROPERTY MORTGAGED\nDo you want to unmortgage it? [1-Yes,2-No]\n";
							int m;
							cin >> m;
							if (m == 1) {
								unmortgage();
								break;
							}
							if (m == 2)
								break;

						}
					}

				}



				if (typeofplace == 3) {

					chance[currentchance]->print();

					if (place[position]->getcardtype() == 1)              //chance
					{
						if (currentchance == 0 || currentchance == 13) {
							//Advance to Go and Collect 300 PKR
							players[currentplayer - 1]->setpostition(-players[currentplayer - 1]->getposition());
							players[currentplayer - 1]->setmoney(300);

						}
						if (currentchance == 1) {
							//Go to DHA Phase 1
							players[currentplayer - 1]->setpostition(26 - players[currentplayer - 1]->getposition());

							position = players[currentplayer - 1]->getposition();

						}
						if (currentchance == 2) {
							//Advance token to nearest utility. If unowned buy from Bank. If owned, pay to owner 5X the amount shown on dice.

						}
						if (currentchance == 3 || currentchance == 4) {
							//You have been elected as chairperson. Pay 25 PKR to each player.
							for (int i = 0; i < totalplayers; i++) {
								if (i != currentplayer - 1) {
									players[currentplayer - 1]->setmoney(-25);
									players[i]->setmoney(25);
								}
							}
							break;

						}
						if (currentchance == 5) {
							//Advance to Model Town 1. If you pass Go collect 300 PKR
							if (players[currentplayer - 1]->getposition() > 16)
								players[currentplayer - 1]->setmoney(300);
							players[currentplayer - 1]->setpostition(16 - players[currentplayer - 1]->getposition());
							position = players[currentplayer - 1]->getposition();
						}
						if (currentchance == 6) {
							//Bank pay you 100 PKR
							players[currentplayer - 1]->setmoney(100);
							bank = bank - 100;
							break;
						}
						if (currentchance == 7) {
							//Get out of Jail. May be kept until needed or sold for 500 PKR
							players[currentplayer - 1]->setjailcard(true);
						}
						if (currentchance == 8) {
							//Go back 4 blocks.
							position = players[currentplayer - 1]->getposition();
							players[currentplayer - 1]->setpostition(-4);
							position = players[currentplayer - 1]->getposition();


						}
						if (currentchance == 9) {
							//Advance to metro station
							players[currentplayer - 1]->setpostition(5 - players[currentplayer - 1]->getposition());
						}
						if (currentchance == 10) {
							//Pay small Tax of 25 PKR
							players[currentplayer - 1]->setmoney(-25);

						}
						if (currentchance == 11) {
							//You have been elected as chairperson. Pay 25 PKR to each player.
							for (int i = 0; i < totalplayers; i++) {
								if (i != currentplayer - 1) {
									players[currentplayer - 1]->setmoney(-25);
									players[i]->setmoney(25);
								}
							}
							break;
						}
						if (currentchance == 12) {
							//Collect 150 PKR from the Bank.
							players[currentplayer - 1]->setmoney(150);
							bank = bank - 150;
							break;
						}
						if (currentchance == 14) {
							//Advance token to Metro Station.
							players[currentplayer - 1]->setpostition(16 - players[currentplayer - 1]->getposition());

						}

						currentchance++;
						if (currentchance == 15)
							currentchance = 0;
						break;
					}




					else                //community chest
					{
						//communitychest[currentcommunitychest]->print();
						if (currentcommunitychest == 0 || currentcommunitychest==10) {
							//Advance to Go and Collect 400 PKR
							players[currentplayer - 1]->setpostition(-(players[currentplayer - 1]->getposition()));
							players[currentplayer - 1]->setmoney(400);


						}
						if (currentcommunitychest == 1) {
							//Bank will pay you 200 PKR
							players[currentplayer - 1]->setmoney(200);
							bank = bank - 200;

						}
						if (currentcommunitychest == 2) {
							//Pay Doctor Fee 200 PKR
							players[currentplayer - 1]->setmoney(-200);


						}
						if (currentcommunitychest == 3) {
							//From Sale you got 50 PKR
							players[currentplayer - 1]->setmoney(50);

						}
						if (currentcommunitychest == 4) {
							//Get out of Jail. May be kept until needed or sold for 500 PKR.
							players[currentplayer - 1]->setjailcard(true);

						}
						if (currentcommunitychest == 5) {
							//Income Tax refund collect 150 PKR
							players[currentplayer - 1]->setmoney(300);
							currentcommunitychest++;

						}
						if (currentcommunitychest == 6) {
							//Your health insurance matures collect 200 PKR
							players[currentplayer - 1]->setmoney(200);

						}
						if (currentcommunitychest == 7) {
							//Pay donation to Hospital 100 PKR
							players[currentplayer - 1]->setmoney(-100);

						}
						if (currentcommunitychest == 9) {
							//Collect 50 PKR for your services.
							players[currentplayer - 1]->setmoney(50);

						}
						if (currentcommunitychest == 8) {
							//Pay Student tax of 200 PKR
							players[currentplayer - 1]->setmoney(-200);

						}
						
						if (currentcommunitychest == 11) {
							//You won prize money of 300 PKR
							players[currentplayer - 1]->setmoney(300);

						}
						if (currentcommunitychest == 12) {
							//Pay water bill of 50 PKR
							players[currentplayer - 1]->setmoney(-50);

						}
						if (currentcommunitychest == 13) {
							//Pay electricity bill of 80 PKR
							players[currentplayer - 1]->setmoney(-80);

						}
						if (currentcommunitychest == 14) {
							//Pay internet bill 50 PKR
							players[currentplayer - 1]->setmoney(-50);

						}
						currentcommunitychest++;
						if (currentcommunitychest == 15)
							currentcommunitychest = 0;
						break;

					}
				}
				if (typeofplace == 4) {
					if (players[currentplayer - 1]->getposition() == 0) {
						players[currentplayer - 1]->setmoney(500);
						break;
					}
					if (players[currentplayer - 1]->getposition() == 10)                    //jail
					{
						cout << "\nVisiting Jail\n";
						break;
					}
					if (players[currentplayer - 1]->getposition() == 30)                    //go to jail
					{
						players[currentplayer - 1]->setpostition(10 - players[currentplayer - 1]->getposition());
						players[currentplayer - 1]->setjail(2);

						break;
					}
					if (players[currentplayer - 1]->getposition() == 37) {
						players[currentplayer - 1]->setmoney(-10);
						break;
					}
					if (players[currentplayer - 1]->getposition() == 4) {
						players[currentplayer - 1]->setmoney(-200);                      
						break;
					}
				}
				break;
			}
		}
		else
		{
			int jail = players[currentplayer - 1]->getjail();
			if (players[currentplayer - 1]->getjailcard() == true) {
				players[currentplayer - 1]->setjail(0);
				//got out of jail with jail card
				players[currentplayer - 1]->setjailcard(false);
			}
			else {


				players[currentplayer - 1]->setjail(--jail);

			}
		}

	}

}

void Monopoly::mortgage()
{
	players[currentplayer - 1]->printprop();
	cout << "\nEnter the property you want to mortgage: ";
	int mort;
	while (true) {
		cin >> mort;
		if (place[mort]->getmortgage() == true) {
			cout << "\nProperty is already mortgaged\n";
		}
		else
			break;
	}
	place[mort]->mortgagedd();
	int mortgage_money = (place[mort]->getprice()) / 2 + (place[mort]->getrent()) / 2;
	players[currentplayer - 1]->setmoney(mortgage_money);
	bank = bank - mortgage_money;
	cout << "\nProperty mortgaged\n";

}

void Monopoly::unmortgage()
{
	players[currentplayer - 1]->setmoney(-(place[players[currentplayer - 1]->getposition()]->getmortprice() + place[players[currentplayer - 1]->getposition()]->getmortprice() * 20 / 100));
	bank = bank - (place[players[currentplayer - 1]->getposition()]->getmortprice() + place[players[currentplayer - 1]->getposition()]->getmortprice() * 20 / 100);
	place[players[currentplayer - 1]->getposition()]->unmort();
}

int Monopoly::winnercheck()
{
	int i = -1;
	if (activeplayers == 1) {
		for (int j=0; j < totalplayers; j++)
		{
			if (players[j]->getbankruptcy() == false)
				i = j;
				break;
		}
	}
	return i;
}

void Monopoly::bidding(int pos)
{
	int upPlayer = -1, player = -1, tempbid = 0, bid = 0;
	while (true)
	{
		while (true)
		{
			cout << "Press the number of player who wants to bid\nor press 0 to finish\n";
			while (true)
			{
				cin >> player;
				if (player == currentplayer || player<0 || player>totalplayers)
					cout << "This player cannot bid.\n";
				else
					break;
			}
			if (player == 0)
				break;
			cout << "How much money do you want to bid: ";
			cin >> tempbid;
			if (tempbid > bid && players[player - 1]->getmoney() > tempbid)
			{
				bid = tempbid;
				upPlayer = player;
			}
		}
		if (upPlayer != -1)
		{
			place[pos]->setownership(upPlayer);
			players[upPlayer - 1]->setmoney(-bid);
			players[upPlayer - 1]->updatepropertiesowned(pos);
			int typeofplace = place[pos]->gettypeofplace();
			players[upPlayer - 1]->updatenoOfpropowned(typeofplace);
			cout << "\nIt is now property of player " << upPlayer << endl;
			break;
		}
	}
}

int Monopoly::getdice()
{
	return dice;
}


Monopoly::~Monopoly()
{
	for (int i = 0; i < 40; i++) {
		delete place[i];
	}
    delete[]place;


	for (int i = 0; i < totalplayers; i++) {
		delete players[i];
	}
	delete[]players;


	for (int i = 0; i < 15; i++) {
		delete chance[i];
	}
	delete[]chance;


	for (int i = 0; i < 15; i++) {
		delete communitychest[i];
	}
	delete[]communitychest;

}

void Monopoly::print_board(int x)
{
	//fullscreen();
	//_getch();

	myRect(320, 20, 1300, 755, 255, 255, 0, 0, 0, 0);        //outer box
	myRect(420, 100, 1180, 650, 255, 255, 255, 255, 255, 255);          //inner box

	myLine(420, 20, 420, 100, 255, 255, 255);                  //lines for upper inside
	myLine(1180, 20, 1180, 100, 255, 255, 255);

	myLine(504, 20, 504, 100, 255, 255, 255);
	myLine(588, 20, 588, 100, 255, 255, 255);
	myLine(672, 20, 672, 100, 255, 255, 255);
	myLine(756, 20, 756, 100, 255, 255, 255);
	myLine(840, 20, 840, 100, 255, 255, 255);
	myLine(924, 20, 924, 100, 255, 255, 255);
	myLine(1008, 20, 1008, 100, 255, 255, 255);
	myLine(1095, 20, 1095, 100, 255, 255, 255);

	myLine(420, 650, 420, 750, 255, 255, 255);                  //lines for down inside
	myLine(1180, 650, 1180, 750, 255, 255, 255);

	myLine(504, 650, 504, 750, 255, 255, 255);
	myLine(588, 650, 588, 750, 255, 255, 255);
	myLine(672, 650, 672, 750, 255, 255, 255);
	myLine(756, 650, 756, 750, 255, 255, 255);
	myLine(840, 650, 840, 750, 255, 255, 255);
	myLine(924, 650, 924, 750, 255, 255, 255);
	myLine(1008, 650, 1008, 750, 255, 255, 255);
	myLine(1095, 650, 1095, 750, 255, 255, 255);

	myLine(320, 100, 420, 100, 255, 255, 255);                  //lines for left inside
	myLine(320, 650, 420, 650, 255, 255, 255);

	myLine(320, 161, 420, 161, 255, 255, 255);
	myLine(320, 222, 420, 222, 255, 255, 255);
	myLine(320, 283, 420, 283, 255, 255, 255);
	myLine(320, 344, 420, 344, 255, 255, 255);
	myLine(320, 405, 420, 405, 255, 255, 255);
	myLine(320, 466, 420, 466, 255, 255, 255);
	myLine(320, 527, 420, 527, 255, 255, 255);
	myLine(320, 588, 420, 588, 255, 255, 255);

	myLine(1180, 100, 1300, 100, 255, 255, 255);                  //lines for right inside
	myLine(1180, 650, 1300, 650, 255, 255, 255);

	myLine(1180, 161, 1300, 161, 255, 255, 255);
	myLine(1180, 222, 1300, 222, 255, 255, 255);
	myLine(1180, 283, 1300, 283, 255, 255, 255);
	myLine(1180, 344, 1300, 344, 255, 255, 255);
	myLine(1180, 405, 1300, 405, 255, 255, 255);
	myLine(1180, 466, 1300, 466, 255, 255, 255);
	myLine(1180, 527, 1300, 527, 255, 255, 255);
	myLine(1180, 588, 1300, 588, 255, 255, 255);



	char str[] = "MONOPOLY";
	char dice[] = { "DICE" };
	myDrawTextWithFont(620, 330, 100, str, RGB(138, 2, 2), RGB(255, 255, 255));
	myDrawTextWithFont(1050, 110, 50, dice, RGB(0, 0, 0), RGB(250, 250, 0));

	myRect(422, 80, 504, 100, 165, 42, 42, 165, 42, 42);  //upper property
	myRect(590, 80, 672, 100, 165, 42, 42, 165, 42, 42);

	myRect(1010, 80, 1095, 100, 0, 0, 255, 0, 0, 255);
	myRect(1097, 80, 1180, 100, 0, 0, 255, 0, 0, 255);
	myRect(843, 80, 922, 100, 0, 0, 255, 0, 0, 255);

	myRect(1182, 102, 1202, 160, 255, 105, 180, 255, 105, 180);          //right property
	myRect(1182, 225, 1202, 282, 255, 105, 180, 255, 105, 180);
	myRect(1182, 284, 1202, 342, 255, 105, 180, 255, 105, 180);

	myRect(1182, 408, 1202, 464, 255, 69, 0, 255, 69, 0);
	myRect(1182, 530, 1202, 587, 255, 69, 0, 255, 69, 0);
	myRect(1182, 591, 1202, 648, 255, 69, 0, 255, 69, 0);

	myRect(400, 102, 418, 160, 0, 0, 128, 0, 0, 128);          //left property
	myRect(400, 225, 418, 282, 0, 0, 128, 0, 0, 128);

	myRect(400, 408, 418, 464, 0, 128, 0, 0, 128, 0);
	myRect(400, 530, 418, 587, 0, 128, 0, 0, 128, 0);
	myRect(400, 591, 418, 648, 0, 128, 0, 0, 128, 0);

	myRect(422, 652, 502, 672, 255, 255, 0, 255, 255, 0);  //lower property
	myRect(590, 652, 670, 672, 255, 255, 0, 255, 255, 0);
	myRect(674, 652, 754, 672, 255, 255, 0, 255, 255, 0);

	myRect(927, 652, 1005, 672, 200, 0, 0, 200, 0, 0);
	myRect(1098, 652, 1178, 672, 200, 0, 0, 200, 0, 0);
	myRect(843, 652, 922, 672, 200, 0, 0, 200, 0, 0);



	char str1[] = "GO";
	myDrawText(330, 30, 800, str1, RGB(250, 255, 0), 0);


	char str2[] = "Johar\nTown(A)";
	myDrawText(422, 30, 80, str2, RGB(255, 0, 0), 0);

	char str3[] = "Community\nChest";
	myDrawText(506, 30, 350, str3, RGB(255, 0, 0), 0);

	char str4[] = "Johar\nTown(B)";
	myDrawText(590, 30, 350, str4, RGB(255, 0, 0), 0);

	char str5[] = "TAX";
	myDrawText(674, 30, 350, str5, RGB(255, 0, 0), 0);

	char str6[] = " Metro bus";
	myDrawText(758, 30, 350, str6, RGB(255, 0, 0), 0);
	myRect(770, 55, 835, 80, 0, 0, 0, 255, 20, 20);
	myRect(775, 62, 820, 72, 255, 255, 255, 0, 0, 0);
	//myRect(820, 57, 828 , 62, 255, 255, 255, 0, 0, 0);
	myEllipse(780, 81, 790, 91, 255, 255, 0,0,0,0);//right say first tyre
	myEllipse(800, 81, 810, 91, 255, 255, 0,0,0,0);//right say first tyre
	myEllipse(818, 81, 828, 91, 255, 255, 0,0,0,0);//right say first tyre

	char str7[] = "Iqbal \nTown A ";
	myDrawText(842, 30, 350, str7, RGB(255, 0, 0), 0);

	char str8[] = "CHANCE";
	myDrawText(925, 30, 350, str8, RGB(255, 0, 0), 0);

	char str9[] = "Iqbal \nTown B";
	myDrawText(1010, 30, 350, str9, RGB(255, 0, 0), 0);

	char str10[] = "Iqbal \nTown C";
	myDrawText(1097, 30, 350, str10, RGB(255, 0, 0), 0);

	char str11[] = "JAIL";
	myRect(1180, 20, 1300, 100, 220, 220, 220, 220, 220, 220);
	for (int i = 0; i < 120; i = i + 4)
		myRect(1180 + i, 20, 1182 + i, 100, 0, 0, 0, 0, 0, 0);
	myDrawText(1183, 30, 50, str11, RGB(255, 0, 0), 0);


	char str12[] = "FAISAL\nTown(A)";
	myDrawText(1208, 105, 50, str12, RGB(255, 0, 0), 0);

	char str13[] = "LESCO";
	myDrawText(1183, 163, 50, str13, RGB(255, 0, 0), 0);

	char str14[] = "FAISAL\nTown(B)";
	myDrawText(1208, 224, 50, str14, RGB(255, 0, 0), 0);

	char str15[] = "FAISAL\nTown(C)";
	myDrawText(1208, 286, 50, str15, RGB(255, 0, 0), 0);

	char str16[] = "Station";
	myDrawText(1183, 347, 50, str16, RGB(255, 0, 0), 0);
	myRect(1230, 360, 1290, 370, 0, 0, 0, 255, 255, 255);
	myRect(1240, 370, 1280, 395, 0, 0, 0, 11, 159, 21);
	myRect(1245, 375, 1250, 380, 255, 250, 0, 255, 255, 255);
	myRect(1210, 380, 1240, 395, 0, 0, 0, 255, 255, 0);
	myEllipse(1195, 380, 1210, 395, 255, 255, 0,0,0,0);//right say first tyre
	myEllipse(1210, 396, 1220, 406, 255, 255, 255,0,0,0);//right say first tyre
	myEllipse(1221, 396, 1231, 406, 255, 255, 255,0,0,0);//right say first tyre
	myEllipse(1231, 396, 1241, 406, 255, 255, 255,0,0,0);//right say first tyre
	myEllipse(1251, 396, 1261, 406, 255, 255, 255,0,0,0);//right say first tyre
	myEllipse(1261, 396, 1271, 406, 255, 255, 255,0,0,0);//right say first tyre
	myEllipse(1271, 396, 1281, 406, 255, 255, 255,0,0,0);//right say first tyre

	char str17[] = "Model\nTown(A)";
	myDrawText(1208, 408, 50, str17, RGB(255, 0, 0), 0);

	char str18[] = "Community\nChest";
	myDrawText(1183, 469, 50, str18, RGB(255, 0, 0), 0);

	char str19[] = "Model\nTown(B)";
	myDrawText(1208, 530, 50, str19, RGB(255, 0, 0), 0);

	char str20[] = "Model\nTown(C)";
	myDrawText(1208, 591, 50, str20, RGB(255, 0, 0), 0);

	char str21[] = "Free\nParking";
	myDrawText(1183, 653, 50, str21, RGB(255, 0, 0), 0);

	char str22[] = "GULBERG\n(A)";
	myDrawText(1097, 674, 50, str22, RGB(255, 0, 0), 0);

	char str23[] = "Chance";
	myDrawText(1010, 653, 50, str23, RGB(255, 0, 0), 0);

	char str24[] = "GULBERG\n(B)";
	myDrawText(925, 674, 50, str24, RGB(255, 0, 0), 0);

	char str25[] = "GULBERG\n(C)";
	myDrawText(842, 674, 50, str25, RGB(255, 0, 0), 0);

	char str26[] = "BUS Station";
	myDrawText(758, 660, 50, str26, RGB(250, 255, 0), 0);
	myRect(770, 680, 830, 710, 0, 0, 0, 255, 255, 255);
	myRect(780, 685, 790, 695, 0, 0, 0, 0, 0, 0);
	myRect(795, 685, 805, 695, 0, 0, 0, 0, 0, 0);
	myRect(810, 685, 820, 695, 0, 0, 0, 0, 0, 0);
	myEllipse(780, 711, 790, 721, 255, 255, 255,0,0,0);//right say first tyre
	myEllipse(810, 711, 820, 721, 255, 255, 255,0,0,0);//right say first tyre

	char str27[] = "DHA (A)";
	myDrawText(674, 674, 50, str27, RGB(255, 0, 0), 0);

	char str28[] = "DHA (B)";
	myDrawText(590, 674, 50, str28, RGB(255, 0, 0), 0);

	char str29[] = "WASA";
	myDrawText(506, 653, 50, str29, RGB(255, 0, 0), 0);

	char str30[] = "DHA (C)";
	myDrawText(422, 674, 50, str30, RGB(255, 0, 0), 0);

	char str31[] = "GO TO\nJAIL";
	myDrawText(324, 653, 50, str31, RGB(255, 0, 0), 0);

	char str32[] = "Baharia\nTown(A)";
	myDrawText(324, 591, 50, str32, RGB(255, 0, 0), 0);                       //591,530,469,408,347,286,224,163,105

	char str33[] = "Baharia\nTown(B)";
	myDrawText(324, 530, 50, str33, RGB(255, 0, 0), 0);

	char str34[] = "Community\nChest";
	myDrawText(324, 469, 50, str34, RGB(255, 0, 0), 0);

	char str35[] = "Baharia\nTown(C)";
	myDrawText(324, 408, 50, str35, RGB(255, 0, 0), 0);

	char str36[] = " Orange Train";
	myDrawText(324, 347, 50, str36, RGB(255, 122, 20), 0);
	myRect(330, 370, 355, 390, 0, 0, 0, 255, 255, 255);
	myRect(356, 370, 377, 390, 0, 0, 0, 255, 255, 255);
	myRect(378, 370, 399, 390, 0, 0, 0, 255, 255, 255);
	myEllipse(330, 391, 400, 399, 250, 255, 20,0,0,0);//right say first tyre
	char str37[] = "Chance";
	myDrawText(324, 286, 50, str37, RGB(255, 0, 0), 0);

	char str38[] = "Parking";
	myDrawText(324, 224, 50, str38, RGB(255, 0, 0), 0);

	char str39[] = "SUI";
	myDrawText(324, 163, 50, str39, RGB(255, 0, 0), 0);

	char str40[] = "PTCL";
	myDrawText(324, 105, 50, str40, RGB(255, 0, 0), 0);

	char str41[] = "A";
	if (players[0]->getposition() == 0)
		myDrawTextWithFont(350, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 1)
		myDrawTextWithFont(424, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 2)
		myDrawTextWithFont(512, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 3)
		myDrawTextWithFont(598, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 4)
		myDrawTextWithFont(682, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 5)
		myDrawTextWithFont(772, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 6)
		myDrawTextWithFont(845, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 7)
		myDrawTextWithFont(930, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 8)
		myDrawTextWithFont(1015, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 9)
		myDrawTextWithFont(1100, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 10)
		myDrawTextWithFont(1220, 28, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 11)
		myDrawTextWithFont(1207, 110, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 12)
		myDrawTextWithFont(1200, 185, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 13)
		myDrawTextWithFont(1207, 240, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 14)
		myDrawTextWithFont(1207, 300, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 15)
		myDrawTextWithFont(1200, 370, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 16)
		myDrawTextWithFont(1207, 420, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 17)
		myDrawTextWithFont(1200, 490, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 18)
		myDrawTextWithFont(1207, 540, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 19)
		myDrawTextWithFont(1207, 600, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 20)
		myDrawTextWithFont(1200, 690, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 21)
		myDrawTextWithFont(1100, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 22)
		myDrawTextWithFont(1015, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 23)
		myDrawTextWithFont(930, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 24)
		myDrawTextWithFont(845, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 25)
		myDrawTextWithFont(772, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 26)
		myDrawTextWithFont(682, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 27)
		myDrawTextWithFont(598, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 28)
		myDrawTextWithFont(512, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 29)
		myDrawTextWithFont(424, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 30)
		myDrawTextWithFont(330, 660, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 31)
		myDrawTextWithFont(330, 600, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 32)
		myDrawTextWithFont(330, 540, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 33)
		myDrawTextWithFont(330, 490, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 34)
		myDrawTextWithFont(330, 420, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 35)
		myDrawTextWithFont(330, 370, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 36)
		myDrawTextWithFont(330, 300, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 37)
		myDrawTextWithFont(330, 240, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 38)
		myDrawTextWithFont(330, 185, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));
	else if (players[0]->getposition() == 39)
		myDrawTextWithFont(330, 110, 30, str41, RGB(0, 0, 0), RGB(255, 100, 255));

	char str42[] = "B";
	if (players[1]->getposition() == 0)
		myDrawTextWithFont(370, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 1)
		myDrawTextWithFont(444, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 2)
		myDrawTextWithFont(530, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 3)
		myDrawTextWithFont(618, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 4)
		myDrawTextWithFont(702, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 5)
		myDrawTextWithFont(792, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 6)
		myDrawTextWithFont(865, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 7)
		myDrawTextWithFont(950, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 8)
		myDrawTextWithFont(1035, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 9)
		myDrawTextWithFont(1120, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 10)
		myDrawTextWithFont(1240, 28, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 11)
		myDrawTextWithFont(1227, 110, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 12)
		myDrawTextWithFont(1220, 185, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 13)
		myDrawTextWithFont(1227, 240, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 14)
		myDrawTextWithFont(1227, 300, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 15)
		myDrawTextWithFont(1220, 370, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 16)
		myDrawTextWithFont(1227, 420, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 17)
		myDrawTextWithFont(1220, 490, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 18)
		myDrawTextWithFont(1227, 540, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 19)
		myDrawTextWithFont(1227, 600, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 20)
		myDrawTextWithFont(1220, 690, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 21)
		myDrawTextWithFont(1120, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 22)
		myDrawTextWithFont(1035, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 23)
		myDrawTextWithFont(950, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 24)
		myDrawTextWithFont(865, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 25)
		myDrawTextWithFont(792, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 26)
		myDrawTextWithFont(702, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 27)
		myDrawTextWithFont(618, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 28)
		myDrawTextWithFont(532, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 29)
		myDrawTextWithFont(444, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 30)
		myDrawTextWithFont(350, 660, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 31)
		myDrawTextWithFont(350, 600, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 32)
		myDrawTextWithFont(350, 540, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 33)
		myDrawTextWithFont(350, 490, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 34)
		myDrawTextWithFont(350, 420, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 35)
		myDrawTextWithFont(350, 370, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 36)
		myDrawTextWithFont(350, 300, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 37)
		myDrawTextWithFont(350, 240, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 38)
		myDrawTextWithFont(350, 185, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));
	else if (players[1]->getposition() == 39)
		myDrawTextWithFont(350, 110, 30, str42, RGB(0, 0, 0), RGB(115, 134, 120));

	if (totalplayers >= 3) {
		char str43[] = "C";
		if (players[2]->getposition() == 0)
			myDrawTextWithFont(350, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 1)
			myDrawTextWithFont(424, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 2)
			myDrawTextWithFont(512, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 3)
			myDrawTextWithFont(598, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 4)
			myDrawTextWithFont(682, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 5)
			myDrawTextWithFont(772, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 6)
			myDrawTextWithFont(845, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 7)
			myDrawTextWithFont(930, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 8)
			myDrawTextWithFont(1015, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 9)
			myDrawTextWithFont(1100, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 10)
			myDrawTextWithFont(1220, 60, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 11)
			myDrawTextWithFont(1247, 110, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 12)
			myDrawTextWithFont(1240, 185, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 13)
			myDrawTextWithFont(1247, 240, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 14)
			myDrawTextWithFont(1247, 300, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 15)
			myDrawTextWithFont(1240, 370, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 16)
			myDrawTextWithFont(1247, 420, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 17)
			myDrawTextWithFont(1240, 490, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 18)
			myDrawTextWithFont(1247, 540, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 19)
			myDrawTextWithFont(1247, 600, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 20)
			myDrawTextWithFont(1240, 690, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 21)
			myDrawTextWithFont(1100, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 22)
			myDrawTextWithFont(1015, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 23)
			myDrawTextWithFont(930, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 24)
			myDrawTextWithFont(845, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 25)
			myDrawTextWithFont(772, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 26)
			myDrawTextWithFont(682, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 27)
			myDrawTextWithFont(598, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 28)
			myDrawTextWithFont(512, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 29)
			myDrawTextWithFont(424, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 30)
			myDrawTextWithFont(330, 693, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 31)
			myDrawTextWithFont(370, 600, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 32)
			myDrawTextWithFont(370, 540, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 33)
			myDrawTextWithFont(370, 490, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 34)
			myDrawTextWithFont(370, 420, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 35)
			myDrawTextWithFont(370, 370, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 36)
			myDrawTextWithFont(370, 300, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 37)
			myDrawTextWithFont(370, 240, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 38)
			myDrawTextWithFont(370, 185, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
		else if (players[2]->getposition() == 39)
			myDrawTextWithFont(370, 110, 30, str43, RGB(0, 0, 0), RGB(228, 132, 0));
	}
	if (totalplayers == 4) {
		char str44[] = "D";
		if (players[3]->getposition() == 0)
			myDrawTextWithFont(370, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 1)
			myDrawTextWithFont(444, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 2)
			myDrawTextWithFont(532, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 3)
			myDrawTextWithFont(618, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 4)
			myDrawTextWithFont(702, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 5)
			myDrawTextWithFont(792, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 6)
			myDrawTextWithFont(865, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 7)
			myDrawTextWithFont(950, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 8)
			myDrawTextWithFont(1035, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 9)
			myDrawTextWithFont(1120, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 10)
			myDrawTextWithFont(1240, 60, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 11)
			myDrawTextWithFont(1267, 110, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 12)
			myDrawTextWithFont(1260, 185, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 13)
			myDrawTextWithFont(1267, 240, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 14)
			myDrawTextWithFont(1267, 300, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 15)
			myDrawTextWithFont(1260, 370, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 16)
			myDrawTextWithFont(1267, 420, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 17)
			myDrawTextWithFont(1260, 490, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 18)
			myDrawTextWithFont(1267, 540, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 19)
			myDrawTextWithFont(1267, 600, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 20)
			myDrawTextWithFont(1260, 690, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 21)
			myDrawTextWithFont(1120, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 22)
			myDrawTextWithFont(1035, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 23)
			myDrawTextWithFont(950, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 24)
			myDrawTextWithFont(865, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 25)
			myDrawTextWithFont(792, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 26)
			myDrawTextWithFont(702, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 27)
			myDrawTextWithFont(618, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 28)
			myDrawTextWithFont(532, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 29)
			myDrawTextWithFont(444, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 30)
			myDrawTextWithFont(350, 693, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 31)
			myDrawTextWithFont(390, 600, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 32)
			myDrawTextWithFont(390, 540, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 33)
			myDrawTextWithFont(390, 490, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 34)
			myDrawTextWithFont(390, 420, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 35)
			myDrawTextWithFont(390, 370, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 36)
			myDrawTextWithFont(390, 300, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 37)
			myDrawTextWithFont(390, 240, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 38)
			myDrawTextWithFont(390, 185, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
		else if (players[3]->getposition() == 39)
			myDrawTextWithFont(390, 110, 30, str44, RGB(0, 0, 0), RGB(255, 255, 255));
	}

	int i = 0;
	while (i < 20) {
		myRect(780 + i, 430 + i, 1050 + i, 600 + i, 184, 134, 11, 228, 132, 0);
		i = i + 2;
	}
	myRect(840, 520, 1030, 600, 255, 215, 0, 255, 215, 0);
	myRect(850, 530, 1020, 590, 165, 42, 42, 165, 42, 42);

	myRect(840, 470, 1030, 520, 255, 215, 0, 255, 215, 0);
	myRect(850, 470, 1020, 510, 165, 42, 42, 165, 42, 42);

	myLine(840, 520, 1030, 520, 128, 0, 0);

	myLine(850, 540, 1020, 550, 128, 0, 0);
	myLine(850, 570, 1020, 560, 128, 0, 0);
	myLine(850, 580, 1020, 580, 128, 0, 0);

	myLine(850, 480, 1020, 485, 128, 0, 0);
	myLine(850, 500, 1020, 496, 128, 0, 0);

	myRect(925, 520, 945, 540, 255, 215, 0, 255, 215, 0);            //lock

	myEllipse(931, 520, 939, 528, 165, 42, 42, 165, 42, 42);
	myRect(934, 525, 937, 535, 165, 42, 42, 165, 42, 42);


	char str45[] = "Community Chest";
	myDrawText(880, 600, 10, str45, RGB(0, 0, 0), RGB(228, 132, 0));





	i = 0;
	while (i < 20) {
		myRect(530 + i, 200 + i, 810 + i, 310 + i, 184, 134, 11, 228, 132, 0);
		i = i + 2;
	}
	char str46[] = "CHANCES";
	myDrawTextWithFont(600, 240, 50, str46, RGB(255, 255, 255), RGB(228, 132, 0));



	if (x == 1)
	{
		myRect(1100, 150, 1150, 200, 240, 240, 240, 0, 0, 0);        //  one
		myEllipse(1120, 170, 1130, 180, 255, 255, 255, 255, 255, 255);
	}
	else if (x == 2)
	{
		myRect(1100, 150, 1150, 200, 240, 240, 240, 0, 0, 0);   // two 
		myEllipse(1110, 170, 1120, 180, 255, 255, 255, 255, 255, 255);
		myEllipse(1130, 170, 1140, 180, 255, 255, 255, 255, 255, 255);
	}
	else if (x == 3)
	{
		myRect(1100, 150, 1150, 200, 240, 240, 240, 0, 0, 0);    //  three
		myEllipse(1105, 170, 1115, 180, 255, 255, 255, 255, 255, 255);
		myEllipse(1120, 170, 1130, 180, 255, 255, 255, 255, 255, 255);
		myEllipse(1135, 170, 1145, 180, 255, 255, 255, 255, 255, 255);
	}
	else if (x == 4)
	{
		myRect(1100, 150, 1150, 200, 240, 240, 240, 0, 0, 0); //  four
		myEllipse(1110, 160, 1120, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1130, 160, 1140, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1110, 180, 1120, 190, 255, 255, 255, 255, 255, 255);
		myEllipse(1130, 180, 1140, 190, 255, 255, 255, 255, 255, 255);
	}
	else if (x == 5)
	{
		myRect(1100, 150, 1150, 200, 240, 240, 240, 0, 0, 0);   //  five
		myEllipse(1120, 170, 1130, 180, 255, 255, 255, 255, 255, 255);
		myEllipse(1110, 160, 1120, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1130, 160, 1140, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1110, 180, 1120, 190, 255, 255, 255, 255, 255, 255);
		myEllipse(1130, 180, 1140, 190, 255, 255, 255, 255, 255, 255);
	}
	else if (x == 6)
	{
		myRect(1100, 150, 1150, 200, 240, 240, 240, 0, 0, 0);    //  three
		myEllipse(1105, 160, 1115, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1120, 160, 1130, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1135, 160, 1145, 170, 255, 255, 255, 255, 255, 255);
		myEllipse(1105, 180, 1115, 190, 255, 255, 255, 255, 255, 255);
		myEllipse(1120, 180, 1130, 190, 255, 255, 255, 255, 255, 255);
		myEllipse(1135, 180, 1145, 190, 255, 255, 255, 255, 255, 255);
	}



	_getch();



}

void Monopoly::savedata()
{
	ofstream fout;
	fout.open("savedata.txt");

	fout << totalplayers << endl;

	for (int i = 0; i < totalplayers; i++)
		players[i]->savePlayerData();

	fout << bank << endl;
	fout << dice << endl;
	fout << currentplayer << endl;
	fout << currentchance << endl;
	fout << currentcommunitychest << endl;
	fout << activeplayers << endl;

	fout.close();
}

void Monopoly::loaddata()
{
	ifstream fin;
	fin.open("savedata.txt");

	fin >> totalplayers;

	for (int i = 0; i < totalplayers; i++)
		players[i]->loadPlayerData();

	fin >> bank;
	fin >> dice;
	currentplayer;
	fin >> currentchance;
	fin >> currentcommunitychest;
	fin >> activeplayers;

	fin.close();
}
