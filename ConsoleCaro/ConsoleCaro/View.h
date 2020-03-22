#pragma once
#include "Data.h"
#include "Model.h"
#include "Control.h"

//Console Window
void CreateConsoleWindow(int pWidth, int pHeight); //Tao console voi kich thuoc cho truoc
void FixConsoleWindow(); //Co dinh console khong cho ng dung thay doi
//Chess Board
void DrawTableLine(int numOfCol, char mainSym, char subSym, int length);
void DrawBoard(int row, int col, int width, int height, int x, int y);
void DrawLoaded(_POINT _A[][BOARD_SIZE]);
//Menu
_MENU MainMenu();
_MENU LoadingMenu();
_MENU EscMenu(_POINT _A[][BOARD_SIZE]);
_MENU YesNoMenu(int x, int y);
//Display
void ShowTurn(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN);
void ShowPlayerInfo(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2);
void ShowHelp();
void ShowRank();
//Cursor
void GotoXY(int x, int y);
//Fancy
void DrawBox(int color, int width, int height, int x, int y);
void SetColor(int color);
void PrintText(string text, int color, int x, int y);
void DrawBigText(string filename, int color, int x, int y);
//Process finish
int ProcessFinish(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int pWhoWin);
bool AskContinue(int x, int y);