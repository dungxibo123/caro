#pragma once

//Console Window
#define WIDTH 1320
#define HEIGHT 700
#define X_CENTER WIDTH / 16 + 2
#define Y_CENTER HEIGHT / 32
//Chess Board
#define BOARD_SIZE 13
#define LEFT 2
#define TOP 1
#define HORIZONTAL_DISTANCE 4
#define VERTICAL_DISTANCE 2
//ASCII
#define SPACE 32
#define ENTER 13
#define ESC 27
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define TOP_LEFT (char)218
#define TOP_RIGHT (char)191
#define BOTTOM_LEFT (char)192
#define BOTTOM_RIGHT (char)217
#define TOP_CROSS (char)194
#define BOTTOM_CROSS (char)193
#define	LEFT_CROSS (char)195
#define RIGHT_CROSS (char)180
#define CROSS (char)197
#define HORIZONTAL_LINE (char)196
#define VERTICAL_LINE (char)179
//Playing Constances
#define FIRST true
#define SECOND false
#define P_X -1
#define P_O 1
//Built-in Libraries
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>
//File stuffs
#define SAVED_LIST "savedlist.txt" //Ten cac file game duoc save
#define PLAYER_LIST "PlayerList.txt" //Thong tin cac player da choi game
//Namespaces
using std::cout;
using std::cin;
using std::string;
//Structs Declaration
struct _POINT
{
	int x; //Hoanh do o co
	int y; //Tung o co
	int c; /*Kiem tra danh hay chua c = -1: luot X danh
									c = 1: luot O danh
									c = 0: chua danh*/
};
struct _MENU
{
	int options;	 //So chuc nang cua Menu
	int x;			 // Toa do cua diem bat 
	int y;			 //dau cua chuc nang dau tien
	int cursorColor; //Mau con tro chon menu
};
struct _PLAYER
{
	string name; //Ten nguoi choi
	int wins = 0;	 //Dem so tran thang
	int rank; //Xep hang cua nguoi choi

	bool operator>(_PLAYER other);
	bool operator<(_PLAYER other);
	bool operator==(_PLAYER other);
};
#pragma comment (lib,"winmm.lib") //dung cho PlaySoundA()