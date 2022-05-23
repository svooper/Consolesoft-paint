#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//Player class with all the playyers attributes
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

// Variables

//Paint color
WORD color = 15;
//Symbol for painting
char symbol = '@';
//Game over variable
bool gameOver = false;
//Player variable
Player player;

//Function for setting the cursor to a specific coordiante
void gotoxy(int x, int y){
	COORD coord = { x, y }; //The coords to go to

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

//Prints a word at a specific coordinate
void wordAtXY(int x, int y, string word, WORD color) {
	COORD coord = { x, y }; //Coord to print at
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(StdHandle, color);
	cout << word; //Prints the word
	return;
}

//Prints a single characther at a coord
void printAtXY(int x, int y, char gfx, WORD color) {
	COORD coord = { x, y }; //Coord to print at
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleTextAttribute(StdHandle, color);
	cout << gfx; //Prints symbol
	return;
}

//Loads a text file in to the console
void LoadFile(string filename) {
	string getContent; //The content of the file
	ifstream openfile(filename); //Opens the file
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (openfile.is_open()) { //Cheks if the file is open
		while (!openfile.eof()) //While the file is open...
		{
			getline(openfile, getContent); //Gets the lies of the file and stores them in the getContent varible
			SetConsoleTextAttribute(StdHandle, 8);
			cout << getContent << endl; //Prints them out
		}
	}
}

//Gets the character at the cursors current point
char getCursorChar()
{
	char c = '\0';
	CONSOLE_SCREEN_BUFFER_INFO con;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	//Gets the char
	if (hcon != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hcon, &con))
	{
		DWORD read = 0;
		if (!ReadConsoleOutputCharacterA(hcon, &c, 1,
			con.dwCursorPosition, &read) || read != 1
			)
			c = '\0';
	}
	//Returns the char
	return c;
}

//Uses getCursorChar function and reads the char at a coordinate
char readChar(int x, int y)
{
	gotoxy(x, y); //Go to coordinates x and y
	char ccccc = getCursorChar();
	return ccccc; //returns the char
}

//Prints the players coordinates
void printCoords(int x, int y) {
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set text color
	SetConsoleTextAttribute(StdHandle, 13);
	gotoxy(136, 0); //Go to x and y
	cout << "{" << x << ", " << y << "}"; //Print the coords
}

//Handles the player input
void input() {
	//Cheks if D was pressed
	if (GetAsyncKeyState(0x44) & 0x8000)
	{
		//Cheks if there is a wall where the player is about to move
		if (readChar((player.x + 1), player.y) != '#') {
			//Updates the players position
			player.updatePlayerPos(1, 0, '+');
			//Cheks if it is painted where the player si about to move if so then dont print the player
			if (readChar(player.x, player.y) != '@'){
				//Prints the player
				printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			}
			//Makes sure so the old player position was erased if ther was no paint there
			if (readChar(player.x - 1, player.y) != '@') {
				//Prints a blank space
				printAtXY(player.x - 1, player.y, ' ', NULL);
			}
			Sleep(30);
		}
	}
	//Cheks if A was pressed
	else if (GetAsyncKeyState(0x41) & 0x8000)
	{
		//Cheks if there is a wall where the player is about to move
		if (readChar((player.x - 1), player.y) != '#') {
			//Updates the players position
			player.updatePlayerPos(1, 0, '-');
			//Cheks if it is painted where the player si about to move if so then dont print the player
			if (readChar(player.x, player.y) != '@') {
				//Prints the player
				printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			}
			//Makes sure so the old player position was erased if ther was no paint there
			if (readChar(player.x + 1, player.y) != '@') {
				//Prints a blank space
				printAtXY(player.x + 1, player.y, ' ', NULL);
			}
			Sleep(30);
		}
	}
	//Cheks if W was pressed
	else if (GetAsyncKeyState(0x53) & 0x8000)
	{
		//Cheks if there is a wall where the player is about to move
		if (readChar(player.x, (player.y + 1)) != '#') {
			//Updates the players position
			player.updatePlayerPos(0, 1, '+'); 
			//Cheks if it is painted where the player si about to move if so then dont print the player
			if (readChar(player.x, player.y) != '@') {
				//Prints the player
				printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			}
			//Makes sure so the old player position was erased if ther was no paint there
			if (readChar(player.x, player.y - 1) != '@') {
				//Prints a blank space
				printAtXY(player.x, player.y - 1, ' ', NULL);
			}
			Sleep(45);
		}
	}
	//Cheks if S was pressed
	else if (GetAsyncKeyState(0x57) & 0x8000)
	{
		//Cheks if there is a wall where the player is about to move
		if (readChar(player.x, (player.y - 1)) != '#') {
			//Updates the players position
			player.updatePlayerPos(0, 1, '-'); 
			//Cheks if it is painted where the player si about to move if so then dont print the player
			if (readChar(player.x, player.y) != '@') {
				//Prints the player
				printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
			}
			//Makes sure so the old player position was erased if ther was no paint there
			if (readChar(player.x, player.y + 1) != '@') {
				//Prints a blank space
				printAtXY(player.x, player.y + 1, ' ', NULL);
			}
			Sleep(45);
		}
	}

	//Cheks if Space was pressed
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		//Prints paint in suggested color
		printAtXY(player.x, player.y, symbol, color);
	}
	//Cheks if E was pressed
	if (GetAsyncKeyState(0x45) & 0x8000) {
		//Prints a blank space to erase
		printAtXY(player.x, player.y, ' ', NULL);
	}

	//Cheks if C was pressed
	if (GetAsyncKeyState(0x43) & 0x8000) {
		//Clears the space and prints the frame and text again
		system("cls");

		LoadFile("lvl1.txt");

		printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);

		wordAtXY(147, 4, "WELCOME TO CONSOLESOFT PAINT!", 13);
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
	//Cheks if 1 was pressed
	if (GetAsyncKeyState(0x31) & 0x8000) {
		//changes the paint color to white
		color = 15;
	}
	//Cheks if 2 was pressed
	if (GetAsyncKeyState(0x32) & 0x8000) {
		//changes the paint color to yellow
		color = 14;
	}
	//Cheks if 3 was pressed
	if (GetAsyncKeyState(0x33) & 0x8000) {
		//changes the paint color to pink
		color = 13;
	}
	//Cheks if 4 was pressed
	if (GetAsyncKeyState(0x34) & 0x8000) {
		//changes the paint color to red
		color = 12;
	}
	//Cheks if 5 was pressed
	if (GetAsyncKeyState(0x35) & 0x8000) {
		//changes the paint color to cyan
		color = 11;
	}
	//Cheks if 6 was pressed
	if (GetAsyncKeyState(0x36) & 0x8000) {
		//changes the paint color to green
		color = 10;
	}
	//Cheks if 7 was pressed
	if (GetAsyncKeyState(0x37) & 0x8000) {
		//changes the paint color to blue
		color = 9;
	}
	//Cheks if 8 was pressed
	if (GetAsyncKeyState(0x38) & 0x8000) {
		//changes the paint color to gray
		color = 8;
	}
}

//Menu
bool start() {
	//Index of the current choice
	int index = 0;

	//Prints the menu
	wordAtXY(106, 20, "CONSOLE PAINT", 13);
	wordAtXY(110, 22, "START", 15);
	wordAtXY(110, 24, "QUIT", 8);
	
	//While in menu
	while (true) {
		//Cheks if up key was pressed
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			//Changes the index to 0 and makes start text white and quit text gray
			wordAtXY(110, 22, "START", 15);
			wordAtXY(110, 24, "QUIT", 8);
			index = 0;
		}
		//Cheks if down key was pressed
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			//Changes the index to 1 and makes start text gray and quit text white
			wordAtXY(110, 22, "START", 8);
			wordAtXY(110, 24, "QUIT", 15);
			index = 1;
		}
		//Cheks if up enter was pressed
		else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (index == 0) {
				//If the index was 0 then start game
				return true;
			}
			else {
				//If the index was 1 then quit
				gameOver = true;
				return false;
			}
		}

	}
}

int main() {

	//Cheks if the game has started
	if (start()) {
		//Prints level and player
		system("cls");
		LoadFile("lvl1.txt");
		printAtXY(player.x, player.y, player.playerBody, FOREGROUND_RED);
	}

	//Prints the text
	printCoords(player.x, player.y);
	wordAtXY(147, 4, "WELCOME TO CONSOLESOFT PAINT!", 13);
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

	//Main while loop
	while (!gameOver) {
		//Go to 0, 0
		gotoxy(0, 0);
		//Print player coords
		printCoords(player.x, player.y);
		//Chek for input
		input();
		//Chek if the color changed
		changeColor();
	}

	//Clears the screen and quits
	system("cls");
	return 0;
}
