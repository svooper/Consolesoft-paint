#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Player {
public:
	int x = 5;
	int y = 30;
	char playerBody = 220;

	void updatePlayerPos(int e, int w, char mode) {
		if (mode == '+') {
			x += e;
			y += w;
		}
		else {
			x -= e;
			y -= w;
		}
	}
};

WORD color = 15;
char symbol = '@';

bool gameOver = false;
Player player;

void gotoxy(int x, int y) {
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void wordAtXY(int x, int y, string word, WORD color) {
	COORD coord = { x, y };
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(StdHandle, color);
	cout << word;
	return;
}

void printAtXY(int x, int y, char gfx, WORD color) {
	COORD coord = { x, y };
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(StdHandle, color);
	cout << gfx;
	return;
}

void LoadFile(string filename) {
	string getContent;
	ifstream openfile(filename);
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (openfile.is_open()) {
		while (!openfile.eof())
		{
			getline(openfile, getContent);
			SetConsoleTextAttribute(StdHandle, 8);
			cout << getContent << endl;
		}
	}
}

char getCursorChar()
{
	char c = '\0';
	CONSOLE_SCREEN_BUFFER_INFO con;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hcon != INVALID_HANDLE_VALUE &&
		GetConsoleScreenBufferInfo(hcon, &con))
	{
		DWORD read = 0;
		if (!ReadConsoleOutputCharacterA(hcon, &c, 1,
			con.dwCursorPosition, &read) || read != 1
			)
			c = '\0';
	}
	return c;
}

char readChar(int x, int y)
{
	gotoxy(x, y);
	char ccccc = getCursorChar();
	return ccccc;
}

void printCoords(int x, int y) {
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(StdHandle, 13);
	gotoxy(136, 0);
	cout << "{" << x << ", " << y << "}";
}

void input() {
	if (GetAsyncKeyState(0x44) & 0x8000)
	{
		if (readChar((player.x + 1), player.y) != '#') {
			player.updatePlayerPos(1, 0, '+');
			printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			if (readChar(player.x - 1, player.y) != '@') {
				printAtXY(player.x - 1, player.y, ' ', NULL);
			}
			Sleep(20);
		}
	}
	else if (GetAsyncKeyState(0x41) & 0x8000)
	{
		if (readChar((player.x - 1), player.y) != '#') {
			player.updatePlayerPos(1, 0, '-');
			printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			if (readChar(player.x + 1, player.y) != '@') {
				printAtXY(player.x + 1, player.y, ' ', NULL);
			}
			Sleep(20);
		}
	}
	else if (GetAsyncKeyState(0x53) & 0x8000)
	{
		if (readChar(player.x, (player.y + 1)) != '#') {
			player.updatePlayerPos(0, 1, '+');
			printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			if (readChar(player.x, player.y - 1) != '@') {
				printAtXY(player.x, player.y - 1, ' ', NULL);
			}
			Sleep(20);
		}
	}
	else if (GetAsyncKeyState(0x57) & 0x8000)
	{
		if (readChar(player.x, (player.y - 1)) != '#') {
			player.updatePlayerPos(0, 1, '-');
			printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			if (readChar(player.x, player.y + 1) != '@') {
				printAtXY(player.x, player.y + 1, ' ', NULL);
			}
			Sleep(20);
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		printAtXY(player.x, player.y, symbol, color);
	}
	if (GetAsyncKeyState(0x45) & 0x8000) {
		printAtXY(player.x, player.y, ' ', NULL);
	}

	if (GetAsyncKeyState(0x43) & 0x8000) {
		system("cls");

		LoadFile("lvl1.txt");

		printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);

		wordAtXY(147, 4, "WELCOME TO CONSOLE PAINT!", 13);
		wordAtXY(147, 6, "Move with W/S/A/D", 13);
		wordAtXY(147, 7, "Use space to paint", 13);
		wordAtXY(147, 9, "Use the top number keys 1-8 to choose colors", 13);
		wordAtXY(147, 10, "1: White", 15);
		wordAtXY(147, 11, "2: Yellow", 14);
		wordAtXY(147, 12, "3: Pink", 13);
		wordAtXY(147, 13, "4: Red", 12);
		wordAtXY(147, 14, "5: Cyan", 11);
		wordAtXY(147, 15, "6: Green", 10);
		wordAtXY(147, 16, "7: Blue", 9);
		wordAtXY(147, 17, "8: Gray", 8);
		wordAtXY(147, 19, "Press C to clear", 13);
		wordAtXY(147, 19, "Press E to erase", 13);
	}
}

void changeColor() {
	if (GetAsyncKeyState(0x31) & 0x8000) {
		color = 15;
	}
	if (GetAsyncKeyState(0x32) & 0x8000) {
		color = 14;
	}
	if (GetAsyncKeyState(0x33) & 0x8000) {
		color = 13;
	}
	if (GetAsyncKeyState(0x34) & 0x8000) {
		color = 12;
	}
	if (GetAsyncKeyState(0x35) & 0x8000) {
		color = 11;
	}
	if (GetAsyncKeyState(0x36) & 0x8000) {
		color = 10;
	}
	if (GetAsyncKeyState(0x37) & 0x8000) {
		color = 9;
	}
	if (GetAsyncKeyState(0x38) & 0x8000) {
		color = 8;
	}
}

bool start() {
	int index = 0;

	wordAtXY(106, 20, "CONSOLE PAINT", 13);
	wordAtXY(110, 22, "START", 15);
	wordAtXY(110, 24, "QUIT", 8);
	
	while (true) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			wordAtXY(110, 22, "START", 15);
			wordAtXY(110, 24, "QUIT", 8);
			index = 0;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			wordAtXY(110, 22, "START", 8);
			wordAtXY(110, 24, "QUIT", 15);
			index = 1;
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (index == 0) {
				return true;
			}
			else {
				gameOver = true;
				return false;
			}
		}

	}
}

int main() {

	if (start()) {
		system("cls");
		LoadFile("lvl1.txt");
		printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
	}

	printCoords(player.x, player.y);
	wordAtXY(147, 4, "WELCOME TO CONSOLE PAINT!", 13);
	wordAtXY(147, 6, "Move with W/S/A/D", 13);
	wordAtXY(147, 7, "Use space to paint", 13);
	wordAtXY(147, 9, "Use the top number keys 1-8 to choose colors", 13);
	wordAtXY(147, 10, "1: White", 15);
	wordAtXY(147, 11, "2: Yellow", 14);
	wordAtXY(147, 12, "3: Pink", 13);
	wordAtXY(147, 13, "4: Red", 12);
	wordAtXY(147, 14, "5: Cyan", 11);
	wordAtXY(147, 15, "6: Green", 10);
	wordAtXY(147, 16, "7: Blue", 9);
	wordAtXY(147, 17, "8: Gray", 8);
	wordAtXY(147, 19, "Press C to clear", 13);
	wordAtXY(147, 19, "Press E to erase", 13);

	while (!gameOver) {

		gotoxy(0, 0);

		printCoords(player.x, player.y);

		input();

		changeColor();
	}

	system("cls");
	return 0;
}