// ConsoleApplication3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <Windows.h>   // para controlar la ventana de consola
#include <conio.h>  // detectar los inputs de teclas y teclado 
using namespace std;

///////////////////////////////////////////////------   H  E  A  D  E  R   -------/////////////////////////////////////////

void gotoxy(int x, int y);
void apagarCursor(bool);
void printContorno();
void showStart();
void showGameOver();
void showWin();

#define Up 72
#define Left 75
#define Right 77 

int plataformas[120][60];

class jumpMan {
public:
	jumpMan();
	~jumpMan();

	void mostrarJumpMan();
	void borrarJumpMan();
	void moverJumpMan();
	void imprimirVidas();

	void setX(int);
	int getX();
	void setY(int);
	int getY();
	void setVidas(int);
	int getVidas();
	void setDerecha(bool);
	int getDerecha();

private:
	int x;
	int y;
	int vidas;
	bool derecha;
	int salto;
};

jumpMan::jumpMan() {
	x = 50;
	y = 50;
	vidas = 3;
	salto = 0;
}
jumpMan::~jumpMan() {

}

void jumpMan::mostrarJumpMan() { //6x3
	SetConsoleOutputCP(CP_UTF8);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 14);

	if (derecha) {

		gotoxy(x, y); cout << "_( o)>";
		gotoxy(x, y + 1); cout << " <_ ) ";
		gotoxy(x, y + 2); cout << "`--'  ";

	}
	else {
		gotoxy(x, y); cout << "<(o )_";
		gotoxy(x, y + 1); cout << " ( _> ";
		gotoxy(x, y + 2); cout << "  `--'";
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void jumpMan::borrarJumpMan() {
	gotoxy(x, y);	  cout << "      ";
	gotoxy(x, y + 1); cout << "      ";
	gotoxy(x, y + 2); cout << "      ";
}

void jumpMan::moverJumpMan() {
	char tecla;

	if (_kbhit())
	{
		tecla = _getch(); // regresa el valor de la tecla y lo guarda en la variable
		borrarJumpMan();  // borrado en consola

		// detectar el movimiento 
		if (tecla == Left && x > 3 && plataformas[x - 2][y] == 0 && plataformas[x - 2][y + 1] == 0 && plataformas[x - 2][y + 2] == 0) {
			x -= 2;
			setDerecha(false);
		}
		if (tecla == Right && x < 112 && plataformas[x + 7][y] == 0 && plataformas[x + 7][y + 1] == 0 && plataformas[x + 7][y + 2] == 0) {
			x += 2;
			setDerecha(true);
		}
		if (tecla == Up && y > 2) {
			if (plataformas[x][y + 3] == 1 || plataformas[x + 5][y + 3] == 1) {
				salto = 8;
			}
		}
		mostrarJumpMan();
	}
	if (salto > 0) {
		if (plataformas[x][y - 1] == 0 && plataformas[x + 5][y - 1] == 0) {
			borrarJumpMan();
			y--;
			mostrarJumpMan();
		}
		salto--;
	}
	else if (plataformas[x][y + 3] == 0 && plataformas[x + 5][y + 3] == 0) {
		borrarJumpMan();
		y++;
		mostrarJumpMan();
	}
}

void jumpMan::imprimirVidas() {
	SetConsoleOutputCP(CP_UTF8);  /////////////////  ASCII
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);   ///// COLOR
	gotoxy(3, 58);
	cout << "Vidas:               ";
	SetConsoleTextAttribute(hConsole, 4);  ///color pt2
	for (int i = 0; i < getVidas(); i++) {
		gotoxy(10 + i, 58);
		cout << "♥";
	}
	SetConsoleTextAttribute(hConsole, 15);  ///color pt3
}

void jumpMan::setX(int _x) {
	x = _x;
}
int jumpMan::getX() {
	return x;
}

void jumpMan::setY(int _y) {
	y = _y;
}
int jumpMan::getY() {
	return y;
}

void jumpMan::setVidas(int _Vidas) {
	vidas = _Vidas;
}
int jumpMan::getVidas() {
	return vidas;
}

void jumpMan::setDerecha(bool _derecha) {
	derecha = _derecha;
}
int jumpMan::getDerecha() {
	return derecha;
}

class Barriles {
public:
	Barriles();
	~Barriles();

	void imprimirBarriles();
	void colision(class jumpMan& bowsette);

	void setX(int);
	int getX();
	void setY(int);
	int getY();

private:
	int x;
	int y;
	bool derecha;
};

Barriles::Barriles() { //////
	x = 12;
	y = 56;
	derecha = true;
}

Barriles::~Barriles() {
}

void Barriles::setX(int _x) {
	x = _x;
}
int Barriles::getX() {
	return x;
}

void Barriles::setY(int _y) {
	y = _y;
}
int Barriles::getY() {
	return y;
}

void Barriles::imprimirBarriles() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(CP_UTF8);
	//Borrar
	gotoxy(x, y);
	cout << " ";

	//Asignar Coordenadas


	if (getX() == 2) {
		derecha = true;
	}
	else if (getX() == 117) {
		derecha = false;
	}

	if (plataformas[x][y + 1] != 1) {
		y++;
	}
	else if (plataformas[x][y + 1] == 1 && derecha == false) {
		x--;
	}
	else if (plataformas[x][y + 1] == 1 && derecha == true) {
		x++;
	}

	if (y > 54) {
		if (rand() % 2 == 1) {
			x = rand() % 48 + 2;
		}
		else {
			x = rand() % 42 + 74;
		}
		y = 2;
		if (rand() % 2 == 1) {
			derecha = true;
		}
		else {
			derecha = false;
		}
	}

	//Imprimir
	gotoxy(x, y);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "●";
	SetConsoleTextAttribute(hConsole, 15);
}

void Barriles::colision(class jumpMan& bowsette) {

	if (x >= bowsette.getX() && x <= bowsette.getX() + 5 && y >= bowsette.getY() && y <= bowsette.getY() + 2) {
		bowsette.setVidas(bowsette.getVidas() - 1);
		bowsette.imprimirVidas();

		if (rand() % 2 == 1) {
			x = rand() % 48 + 2;
		}
		else {
			x = rand() % 42 + 74;
		}
		y = 2;
		if (rand() % 2 == 1) {
			derecha = true;
		}
		else {
			derecha = false;
		}
	}
}

/// /// /// Vidas

class Vidas {
public:
	Vidas();
	~Vidas();

	void imprimirVidas();
	void colision(class jumpMan& bowsette);

	void setX(int);
	int getX();
	void setY(int);
	int getY();

private:
	int x;
	int y;
	int pos;
};

Vidas::Vidas() { 
	x = 40;
	y = 47;
}

Vidas::~Vidas() {
}

void Vidas::setX(int _x) {
	x = _x;
}
int Vidas::getX() {
	return x;
}

void Vidas::setY(int _y) {
	y = _y;
}
int Vidas::getY() {
	return y;
}

void Vidas::imprimirVidas() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(CP_UTF8);
	//Borrar
	gotoxy(x, y);
	cout << " ";

	//Asignar Coordenadas
	if (pos == 0)
	{
		x = 43;
		y = 33;
	}
	else if (pos == 1)
	{
		x = 104;
		y = 26;
	}
	else if (pos == 2)
	{
		x = 8;
		y = 12;
	}
	else if (pos == 3)
	{
		x = 87;
		y = 12;
	}
	else if (pos == 4)
	{
		x = 24;
		y = 19;
	}
	else if (pos == 5)
	{
		x = 75;
		y = 19;
	}
	else if (pos == 6)
	{
		x = 8;
		y = 40;
	}
	else if (pos == 7)
	{
		x = 98;
		y = 47;
	}

	//Imprimir
	gotoxy(x, y);
	SetConsoleTextAttribute(hConsole, 4);
	cout << "♥";
	SetConsoleTextAttribute(hConsole, 15);
}

void Vidas::colision(class jumpMan& bowsette) {

	if (x >= bowsette.getX() && x <= bowsette.getX() + 5 && y >= bowsette.getY() && y <= bowsette.getY() + 2) {
		if (bowsette.getVidas() != 5)
		{
			bowsette.setVidas(bowsette.getVidas() + 1);
		}

		bowsette.imprimirVidas();
		pos = rand() % 7;
	}
}


/////////////////////////////////////////////////--------   M   A   I   N   ---------/////////////////////////////////////////


int main()
{
	apagarCursor(false);
	char tecla;
	bool gameOver = false;
	int x = 10, y = 51;


	showStart();
	gotoxy(45, 51);
	system("pause");  ///// PAUSE	
	system("cls");

	Vidas corazon;
	jumpMan bowsette;
	bowsette.setX(x);
	bowsette.setY(y);

	bowsette.mostrarJumpMan();

	printContorno();

	Barriles obstaculo[8];

	while (gameOver != true)
	{
		corazon.imprimirVidas(); 
		corazon.colision(bowsette);
		bowsette.imprimirVidas();
		bowsette.moverJumpMan();
		for (int i = 0; i < 8; i++) {
			obstaculo[i].imprimirBarriles();
			obstaculo[i].colision(bowsette);
		}
		Sleep(50);

		if (bowsette.getVidas() == 0) {
			gameOver = true;
			system("cls");
			showGameOver();
			system("pause");
		}
		if (plataformas[bowsette.getX()][bowsette.getY() + 3] == 2 || plataformas[bowsette.getX() + 5][bowsette.getY() + 3] == 2) {
			gameOver = true;
			system("cls");
			showWin();
			system("pause");
		}
	}
}


//////////////////////////////////////--------   F  U  N  C  I  O  N  E  S   ---------///////////////////////////////

void gotoxy(int x, int y) {

	HANDLE hCon; // objeto de tipo ventana, identificador de la ventana

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);   // tomar el control de la salida de consola

	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);   // da una pos al cursor en la ventana 
}


void apagarCursor(bool x) {
	HANDLE hCon;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = x;
	SetConsoleCursorInfo(hCon, &cci);
}

void printContorno() {
	SetConsoleOutputCP(CP_UTF8);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 120; i++) {
		gotoxy(i, 1); cout << "═";
		gotoxy(i, 57); cout << "▬";
	}
	for (int i = 0; i < 60; i++) {
		gotoxy(1, i); cout << "║";
		gotoxy(118, i); cout << "║";
	}

	///// M A P A

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(58, 3); cout << "  _,,,_  ";
	gotoxy(58, 4); cout << "(| . . |)";
	gotoxy(58, 5); cout << " ( (Y) ) ";
	gotoxy(58, 6); cout << " _|)_(|_ ";


	SetConsoleTextAttribute(hConsole, 9);
	//  ----> 0
	gotoxy(52, 7); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(52, 8); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 20

	//  ----> 1
	gotoxy(2, 14); cout << "▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(2, 15); cout << "╧╧╧╧╧╧╧╧╧╧╧╧";//-- 12
	gotoxy(27, 14); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(27, 15); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 30
	gotoxy(72, 14); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(72, 15); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 30


	//  ----> 2
	gotoxy(8, 21); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(8, 22); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 34
	gotoxy(58, 21); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(58, 22); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 26
	gotoxy(106, 21); cout << "▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(106, 22); cout << "╧╧╧╧╧╧╧╧╧╧╧╧";//-- 12

	//  ----> 3
	gotoxy(36, 28); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(36, 29); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 36
	gotoxy(94, 28); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(94, 29); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 36


	//  ----> 4
	gotoxy(14, 35); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(14, 36); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 36
	gotoxy(68, 35); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(68, 36); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 34


	//  ----> 5
	gotoxy(2, 42); cout << "▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(2, 43); cout << "╧╧╧╧╧╧╧╧╧╧╧╧";//-- 12
	gotoxy(36, 42); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(36, 43); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 54
	gotoxy(106, 42); cout << "▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(106, 43); cout << "╧╧╧╧╧╧╧╧╧╧╧╧";//-- 12

	//  ----> 6
	gotoxy(24, 49); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(24, 50); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 36
	gotoxy(86, 49); cout << "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬";
	gotoxy(86, 50); cout << "╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧╧";//-- 24

	//  ----> Suelo
	gotoxy(2, 56); cout << "▬▬▬▬▬▬▬▬▬▬     ▬▬▬▬     ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬     ▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬     ▬▬▬▬▬"; //-- 112

	SetConsoleTextAttribute(hConsole, 15);

	//Plataformas Binarias
	//plataformas[i + Coordenada x][7 + Coordenada y de arriba] = 1;

	//20
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			plataformas[i + 52][7 + j] = 2;
		}
	}

	//12
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			plataformas[i + 2][14 + j] = 1;
			plataformas[i + 106][j + 21] = 1;
			plataformas[i + 2][j + 42] = 1;
			plataformas[i + 106][j + 42] = 1;
		}
	}

	//30
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			plataformas[i + 27][14 + j] = 1;
			plataformas[i + 72][14 + j] = 1;
			plataformas[i + 8][j + 21] = 1;
		}
	}

	//26
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 26; i++)
		{
			plataformas[i + 58][j + 21] = 1;
		}
	}

	//36
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 36; i++)
		{
			plataformas[i + 36][j + 28] = 1;
			plataformas[i + 94][j + 28] = 1;
			plataformas[i + 14][j + 35] = 1;
			plataformas[i + 24][j + 49] = 1;
		}
	}

	//34
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 34; i++)
		{
			plataformas[i + 68][j + 35] = 1;
		}
	}

	//54
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 54; i++)
		{
			plataformas[i + 36][j + 42] = 1;
		}
	}

	//24
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 24; i++)
		{
			plataformas[i + 86][j + 49] = 1;
		}
	}


	//Suelo
	for (int i = 0; i < 120; i++)
	{
		plataformas[i + 2][56] = 1;
	}
}

void showStart() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(0, 3); cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:..:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.";

	SetConsoleTextAttribute(hConsole, 1);
	gotoxy(15, 7); cout << " .d8888b.                                     ";
	gotoxy(15, 8); cout << "d88P  Y88b                                    ";
	gotoxy(15, 9); cout << "Y88b.                                         ";
	gotoxy(15, 10); cout << "  Y888b.   888  888 88888b.   .d88b.  888d888 ";
	gotoxy(15, 11); cout << "     Y88b. 888  888 888  88b d8P  Y8b 888P    ";
	gotoxy(15, 12); cout << "       888 888  888 888  888 88888888 888     ";
	gotoxy(15, 13); cout << "Y88b  d88P Y88b 888 888 d88P Y8b.     888     ";
	gotoxy(15, 14); cout << "  Y8888P     Y88888 88888P     Y8888  888     ";
	gotoxy(15, 15); cout << "                    888                       ";
	gotoxy(15, 16); cout << "                    888                       ";
	gotoxy(15, 17); cout << "                    888                       ";

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(30, 19); cout << "8888888b.                    888               ";
	gotoxy(30, 20); cout << "8888888b.                    888               ";
	gotoxy(30, 21); cout << "888    888                   888               ";
	gotoxy(30, 22); cout << "888    888 888  888  .d8888b 888  888 888  888 ";
	gotoxy(30, 23); cout << "888    888 888  888 d88P     888 .88P 888  888 ";
	gotoxy(30, 24); cout << "888    888 888  888 888      888888K  888  888 ";
	gotoxy(30, 25); cout << "888  .d88P Y88b 888 Y88b.    888  88b Y88b 888 ";
	gotoxy(30, 26); cout << "8888888P     Y88888   Y8888P 888  888   Y88888 ";
	gotoxy(30, 27); cout << "                                           888 ";
	gotoxy(30, 28); cout << "                                      Y8b d88P ";
	gotoxy(30, 29); cout << "                                        Y88P   ";

	SetConsoleTextAttribute(hConsole, 1);
	gotoxy(42, 31); cout << "888    d8P                             888 888 ";
	gotoxy(42, 32); cout << "888   d8P                              888 888 ";
	gotoxy(42, 33); cout << "888  d8P                               888 888 ";
	gotoxy(42, 34); cout << "888d88K      .d88b.  88888b.   .d88b.  888 888 ";
	gotoxy(42, 35); cout << "8888888b    d88  88b 888  88b d88P 88b 888 888 ";
	gotoxy(42, 36); cout << "888  Y88b   888  888 888  888 888  888 Y8P Y8P ";
	gotoxy(42, 37); cout << "888   Y88b  Y88..88P 888  888 Y88b 888         ";
	gotoxy(42, 38); cout << "888    Y88b   Y88P   888  888   Y88888 888 888 ";
	gotoxy(42, 39); cout << "                                   888         ";
	gotoxy(42, 40); cout << "                              Y8b d88P         ";
	gotoxy(42, 41); cout << "                                Y88P           ";

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(0, 45); cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:..:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.";



	SetConsoleTextAttribute(hConsole, 14);
	gotoxy(70, 7); cout << "       ..---..";
	gotoxy(70, 8); cout << "     .'  _    `.";
	gotoxy(70, 9); cout << " __..'  (o)    :";
	gotoxy(70, 10); cout << "`..__          ;";
	gotoxy(70, 11); cout << "     `.       / ";
	gotoxy(70, 12); cout << "       ;      `..---...___";
	gotoxy(70, 13); cout << "     .'                   `~-. .-')";
	gotoxy(70, 14); cout << "    .                         ' _.'";
	gotoxy(70, 15); cout << "   :                           :";
	gotoxy(70, 16); cout << "   \                           ' ";
	gotoxy(70, 17); cout << "    +                         J";
	gotoxy(70, 18); cout << "     `._                   _.'";
	gotoxy(70, 19); cout << "        `~--....___...---~' ";


	SetConsoleTextAttribute(hConsole, 15);

	cout << endl << endl << endl << endl << endl << endl;

	//gotoxy(20, 20); cout << "Presiona cualquier tecla para continuar...";
	//cout << endl << endl << endl << endl << endl << endl;
}

void showGameOver() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(0, 10); cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:..:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.";

	SetConsoleTextAttribute(hConsole, 1);
	gotoxy(23, 20); cout << " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ ";
	gotoxy(23, 21); cout << "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗";
	gotoxy(23, 22); cout << "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝";
	gotoxy(23, 23); cout << "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗";
	gotoxy(23, 24); cout << "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║";
	gotoxy(23, 25); cout << " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝";

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(0, 35); cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:..:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.";


	SetConsoleTextAttribute(hConsole, 15);

	cout << endl << endl << endl << endl << endl << endl;


}

void showWin()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(0, 10); cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:..:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.";

	SetConsoleTextAttribute(hConsole, 1);
	gotoxy(23, 20); cout << ":::   :::  ::::::::  :::    :::      :::       ::: ::::::::::: ::::    ::: ::: ::: ";
	gotoxy(23, 21); cout << ":+:   :+: :+:    :+: :+:    :+:      :+:       :+:     :+:     :+:+:   :+: :+: :+: ";
	gotoxy(23, 22); cout << " +:+ +:+  +:+    +:+ +:+    +:+      +:+       +:+     +:+     :+:+:+  +:+ +:+ +:+ ";
	gotoxy(23, 23); cout << "  +#++:   +#+    +:+ +#+    +:+      +#+  +:+  +#+     +#+     +#+ +:+ +#+ +#+ +#+ ";
	gotoxy(23, 24); cout << "   +#+    +#+    +#+ +#+    +#+      +#+ +#+#+ +#+     +#+     +#+  +#+#+# +#+ +#+ ";
	gotoxy(23, 25); cout << "   #+#    #+#    #+# #+#    #+#       #+#+# #+#+#      #+#     #+#   #+#+#         ";
	gotoxy(23, 26); cout << "   ###     ########   ########         ###   ###   ########### ###    #### ### ### ";

	SetConsoleTextAttribute(hConsole, 4);
	gotoxy(0, 36); cout << ".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:..:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.";


	SetConsoleTextAttribute(hConsole, 15);

	cout << endl << endl << endl << endl << endl << endl;
}