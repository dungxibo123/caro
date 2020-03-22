#pragma once
#include "Data.h"
#include "View.h"
#include "Model.h"

//Game's process
void StartGame(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int& _COMMAND, int& _X, int& _Y);
void RunGame(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int& _COMMAND, int& _X, int& _Y);
void SaveGame(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN);
void LoadGame(string filename, _POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool & _TURN, int &_COMMAND, int &_X, int &_Y);
void ExitGame(bool& run);
//Move
bool MoveLeft(_POINT _A[][BOARD_SIZE], int& _X, int& _Y);
bool MoveRight(_POINT _A[][BOARD_SIZE], int& _X, int& _Y);
bool MoveDown(_POINT _A[][BOARD_SIZE], int& _X, int& _Y);
bool MoveUp(_POINT _A[][BOARD_SIZE], int& _X, int& _Y);
//Menu's process
void RunMainMenu(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int& _COMMAND, int& _X, int& _Y, bool& run, int option);
void RunEscMenu(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN, int option, bool& runGame);
string RunLoadingMenu(int option);
char RunYesNoMenu(int option);
int SelectMenu(_MENU menu);