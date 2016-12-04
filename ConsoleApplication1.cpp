#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;
bool naraz;
const int sirka = 40;
const int vyska = 20;
int x, y, ovoceX, ovoceY, skore;
int clanekX[100], clanekY[100];
int pocetClanku;
enum eDirecton {S = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
char volba = '0';
char znovu;
void Zacatek()
{
	naraz = false;
	dir = S;
	x = sirka / 2;
	y = vyska / 2;
	ovoceX = rand() % sirka;
	ovoceY = rand() % vyska;
	skore = 0;
	pocetClanku = 0;
	srand((unsigned int)time(NULL));; // lepsi nahodnost dle stuck overflow
}
void Levl()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	for (int i = 0; i < sirka + 2; i++)
		cout << "\xB2";
	cout << endl;

	for (int i = 0; i < vyska; i++)
	{
		for (int j = 0; j < sirka; j++)
		{
			if (j == 0)
				cout << "\xB2";
			if (i == y && j == x)
				cout << "O";
			else if (i == ovoceY && j == ovoceX) {
				cout << "o";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < pocetClanku; k++)
				{
					if (clanekX[k] == j && clanekY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == sirka - 1)
				cout << "\xB2";
		}
		cout << endl;
	}

	for (int i = 0; i < sirka + 2; i++)
		cout << "\xB2";
	cout << endl;
	cout << "Sk\xA2re:" << skore << "    q - vypnout" << endl;
	if (skore/50 == 1) {
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	else if (skore/100 == 1)
	{
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else if (skore/150 == 1)
	{
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if (skore == 0)
	{
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	}
}
void Ovladani()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			naraz = true;
			break;
/*		case 'p':		Bohuzel nefunkcni pauza
			dir = S;
			break;*/ 
		}
	}
}
void Pohyb()
{
	int prevX = clanekX[0];
	int prevY = clanekY[0];
	int prev2X, prev2Y;
	clanekX[0] = x;
	clanekY[0] = y;
	for (int i = 1; i < pocetClanku; i++)
	{
		prev2X = clanekX[i];
		prev2Y = clanekY[i];
		clanekX[i] = prevX;
		clanekY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	// Tezsi obtiznost (narazi do steny]
	//if (x > width || x < 0 || y > height || y < 0)
	//  naraz = true;
	if (x >= sirka) x = 0; else if (x < 0) x = sirka - 1;
	if (y >= vyska) y = 0; else if (y < 0) y = vyska - 1;

	for (int i = 0; i < pocetClanku; i++)
		if (clanekX[i] == x && clanekY[i] == y)
			naraz = true;

	if (x == ovoceX && y == ovoceY)
	{
		skore += 10;
		ovoceX = rand() % sirka;
		ovoceY = rand() % vyska;
		pocetClanku++;
	}
}
void startMenu() {
	cout << "#############################################################" << endl;
	cout << "#        _______  __    _  _______  ___   _  _______        #" << endl;
	cout << "#       |       ||  |  | ||   _   ||   | | ||       |       #" << endl;
	cout << "#       |  _____||   |_| ||  |_|  ||   |_| ||    ___|       #" << endl;
	cout << "#       | |_____ |       ||       ||      _||   |___        #" << endl;
	cout << "#       |_____  ||  _    ||       ||     |_ |    ___|       #" << endl;
	cout << "#        _____| || | |   ||   _   ||    _  ||   |___        #" << endl;
	cout << "#       |_______||_|  |__||__| |__||___| |_||_______|       #" << endl;
	cout << "#############################################################" << endl;
	cout << "#############################################################" << endl;
	cout << "#        Vitejte u hry Snake                                #" << endl;
	cout << "#        Hra se ovlada klavesami W,A,S,D                    #" << endl;
	cout << "#        Hru lze ukoncit klavesou \"q\"                       #" << endl;
	cout << "#        1. Start Hry                                       #" << endl;
	cout << "#        2. Nejlepsi skore                                  #" << endl;
	cout << "#        3. Ukoncit hru                                     #" << endl;
	cout << "#                                                           #" << endl;
	cout << "#                                                           #" << endl;
	cout << "#                                                           #" << endl;
	cout << "#                                                           #" << endl;
	cout << "#                              Vytvoril Milan Lesnek 2016   #" << endl;
	cout << "#############################################################" << endl;
	cin >> volba;
}
void main()
{

	startMenu();
	if (volba == '1') {
		Zacatek();
		while (1)
		{
			Levl();
			Ovladani();
			Pohyb();
			Sleep(10);
			if (naraz == true) {
				cout << "Chcete hrat znovu? <y/n>:"; cin >> znovu;
				if (znovu == 'y' || znovu == 'Y') {
					Zacatek();
					pocetClanku = 0;
					continue;
				}
				else break;
				}
			}
		main();
		}
	else if (volba == 3) exit;
}
	
