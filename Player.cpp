#include "Player.h"



Player::Player()
{
	name = nullptr;
	position = 0;
	money = 0;
	jail = 0;
	jailcard = false;
	propertiesowned = nullptr;
	bankrupt = false;
	sizepropertieowned = 0;
	for (int i = 0; i < 7; i++)
	{
		noOfpropowned[i] = 0;
	}
}

Player::Player(char* n)
{
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);

	position = 0;
	money = 5000;	
	jail = 0;
	jailcard = false;
	bankrupt = false;
	propertiesowned = nullptr;
	sizepropertieowned = 0;
	for (int i = 0; i < 7; i++)
	{
		noOfpropowned[i] = 0;
	}

}

void Player::setpostition(int pos)
{
	position = position + pos;
	if (position > 39)
		position = position - 40;
}

int Player::getposition()
{
	return position;
}

int Player::getmoney()
{
	return money;
}

int Player::getjail()
{
	return jail;
}

void Player::setjail(int jaill)
{
	jail = jaill;
}

bool Player::getjailcard()
{
	return jailcard;
}

void Player::setjailcard(bool jc)
{
	jailcard = jc;
}

void Player::setmoney(int mon)
{

	money = money+mon;

}

void Player::printprop()
{
	for (int i = 0; i < sizepropertieowned ; i++)
	{
		cout << propertiesowned[i] << " , ";
	}
}

void Player::deletepropowned()
{
	delete[]propertiesowned;
}

bool Player::getbankruptcy()
{
	return bankrupt;
}

void Player::setbankruptcy()
{
	bankrupt = true;
}

void Player::printplayer()
{
	cout << "Player: " << name<<endl;
	cout << "Money: " << money << endl;
	cout << "Properties: " << sizepropertieowned << endl;
	cout << "Owned: ";
	for (int i = 0; i < sizepropertieowned; i++) {
		cout << propertiesowned[i] << " ";
	}
	cout << endl;
}

int Player::getsizepropowned()
{
	return sizepropertieowned;
}

int Player::getpropowned(int index)
{
	return propertiesowned[index];
}


void Player::updatepropertiesowned(int place)
{
	
	if (sizepropertieowned == 0) {
		sizepropertieowned++;
		propertiesowned = new int[sizepropertieowned];
		propertiesowned[sizepropertieowned - 1] = place;
	}
	else {
		int* temp = new int[sizepropertieowned];
		for (int i = 0; i < sizepropertieowned; i++)
		{
			temp[i] = propertiesowned[i];
		}
		delete[]propertiesowned;
		sizepropertieowned++;
		propertiesowned = new int[sizepropertieowned];
		for (int i = 0; i < sizepropertieowned-1; i++)
		{
			propertiesowned[i]=temp[i];
		}
		propertiesowned[sizepropertieowned - 1] = place;
	}
	
}

void Player::setsizepropowned(int s)
{
	sizepropertieowned = s;
}

void Player::updatenoOfpropowned(int typeofplace)
{
	noOfpropowned[typeofplace - 1]++;
}

int Player::getnoOfpropowned(int typeofplace)
{
	return noOfpropowned[typeofplace-1];
}


Player::~Player()
{
	if (name != nullptr)
		delete[]name;
}

void Player::savePlayerData()
{
	ofstream fout("savedata.txt");
	fout << name << endl;
	fout << position << endl;
	fout << money << endl;
	fout << jail << endl;
	fout << jailcard << endl;
	fout << bankrupt << endl;
	fout << sizepropertieowned << endl;
	for (int i = 0; i < sizepropertieowned; i++)
		fout << propertiesowned[i] << endl;
	for (int i = 0; i < 7; i++)
		fout << noOfpropowned[i] << endl;
}

void Player::loadPlayerData()
{
	ifstream fin("savedata.txt");
	fin >> name;
	fin >> position;
	fin >> money;
	fin >> jail;
	fin >> jailcard;
	fin >> bankrupt;
	fin >> sizepropertieowned;
	for (int i = 0; i < sizepropertieowned; i++)
		fin >> propertiesowned[i];
	for (int i = 0; i < 7; i++)
		fin >> noOfpropowned[i];
}

