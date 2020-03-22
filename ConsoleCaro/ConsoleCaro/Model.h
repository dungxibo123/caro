#pragma once
#include "Data.h"
#include "View.h"

//Data Handling
void ResetData(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int& _COMMAND, int& _X, int& _Y);
void SaveData(string filename, _POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN);
void LoadData(string filename, _POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool & _TURN, int &_COMMAND, int &_X, int &_Y);
std::vector<string> LoadFiles();
bool CheckFileExistence(string filename); //Kiem tra file save da ton tai hay chua
//Check to board chess
int CheckBoard(_POINT _A[][BOARD_SIZE], bool _TURN, int cRow, int cCol);
//Win, lose, draw process
bool CheckWin(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol);
bool HorizontalCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol);
bool VerticalCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol);
bool ForwardSlashCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol);
bool BackwardSlashCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol);
bool CheckTie(_POINT _A[][BOARD_SIZE]);
int TestBoard(_POINT _A[][BOARD_SIZE], bool _TURN, int cRow, int cCol);
//Player's handling
void SetPlayer(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2);
std::vector<_PLAYER> GetPlayerList();
int CheckPlayerExistence(_PLAYER player);
void SavePlayer(_PLAYER player);
_PLAYER LoadPlayer(_PLAYER player);
void SetPlayerRank(_PLAYER& player);
//Get Board Index
int GetRowIndex(int pY);
int GetColIndex(int pX);
//Algorithms
void SortPlayerList(std::vector<_PLAYER>& playerList);
