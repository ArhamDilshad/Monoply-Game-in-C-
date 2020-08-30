#include<iostream>
#include"Monopoly.h"
#include <Windows.h>


using namespace std;
void fullscreen();
void myDrawTextWithFont(int x, int y, int ht, char  str[], COLORREF lineColor, COLORREF fillColor);

void main() {
	fullscreen();
	char str1[] = "Monopoly";
	for (int i = 0; i < 5; i++) {
		myDrawTextWithFont(380, 250, 200, str1, RGB(138, 2, 2), RGB(255, 255, 255));
		Sleep(1000);
	}
	system("cls");
	cout << "Do you want to\n1. Start the Game\n2. Read the Rules\n";
	int retrive=0;
	
	int players;
	while (retrive != 1) {
		system("cls");
		cout << "Do you want to\n1. Start the Game\n2. Read the Rules\n";
		cin >> retrive;
		if (retrive == 1)
		{
			cout << "Enter number of players: ";
			cin >> players;
		}
		if (retrive == 2)
		{
			system("cls");
			cout << "RULES\n\n\n1. A player will go bankrupt only he chooses to do so\n\n2. A player can skip bankruptcy by mortgaging properties\n\n3. If the player has no properties and his money drops below zero, he will be bankrupted\n\n4. A player can only upgrade a property if he owns all properties of that type\n\n5. The last player who will remain safe from bankruptcy will win.\n\n";
			system("pause");
		}
	}
	Monopoly M(players);
	
	int dice = 1;
	int W = M.winnercheck();
	while (W==-1) {
		M.printplayersinfo();
		cout << endl<<endl;
		M.print_board(dice);

		M.rolldice();
		dice = M.getdice();
		M.print_board(dice);
		M.moveplayer();
		M.print_board(dice);
		W = M.winnercheck();
		M.changeplayer();

		system("cls");
		M.savedata();
	}
	if (W == 0) {
		cout << "\n\nPlayer 1 wins\n\n";
	}
	if (W == 1) {
		cout << "\n\nPlayer 2 wins\n\n";
	}
	if (W == 2) {
		cout << "\n\nPlayer 3 wins\n\n";
	}
	if (W == 3) {
		cout << "\n\nPlayer 4 wins\n\n";
	}
	system("pause");
}