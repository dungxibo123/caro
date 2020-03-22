#include "Control.h"

void RunMainMenu(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int& _COMMAND, int& _X, int& _Y, bool& run, int option)
{
	int loadOption;
	switch (option)
	{
	case 1:
		SetPlayer(_PLAYER1, _PLAYER2);
		StartGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
		RunGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
		break;
	case 2:
		system("cls");
		loadOption = SelectMenu(LoadingMenu());
		if (loadOption == -1) break;
		else
		{
			LoadGame(RunLoadingMenu(loadOption), _A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
			RunGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
			break;
		}
	case 3:
		do
		{
			ShowRank();
		} while (_getch() != ESC);
		break;
	case 4:
		do
		{
			ShowHelp();
		} while (_getch() != ESC);
		break;
	case 5:case -1:
		ExitGame(run);
		break;
	}
}

void RunEscMenu(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN, int option, bool& runGame)
{
	switch (option)
	{
	case 1: case -1:
		system("cls");
		DrawBoard(BOARD_SIZE, BOARD_SIZE, 3, 1, LEFT, TOP);
		DrawLoaded(_A);
		ShowTurn(_A, _PLAYER1, _PLAYER2, _TURN);
		break;
	case 2:
		SaveGame(_A, _PLAYER1, _PLAYER2, _TURN);
		runGame = false;
		break;
	case 3:
		runGame = false;
		break;
	}
}

string RunLoadingMenu(int option)
{
	string filename;
	std::vector<string> files;

	files = LoadFiles();
	filename = files.at(option - 1);

	return filename;
}

char RunYesNoMenu(int option)
{
	switch (option)
	{
	case 1:
		return 'Y';
	case 2:
		return 'N';
	}
}

int SelectMenu(_MENU menu)
{
	int cursor = 1;
	char key;

	PrintText("--->", menu.cursorColor, menu.x - 4, menu.y);

	do
	{
		key = _getch();
		if (key == ARROW_UP && cursor > 1)
		{
			PrintText("    ", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
			cursor--;
			PrintText("--->", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
		}
		else if (key == ARROW_DOWN && cursor < menu.options)
		{
			PrintText("    ", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
			cursor++;
			PrintText("--->", menu.cursorColor, menu.x - 4, menu.y + cursor - 1);
		}
		else if (key == ESC)
		{
			return -1;
		}
	} while (key != ENTER);

	return cursor;
}

void StartGame(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int& _COMMAND, int& _X, int& _Y)
{

	SetPlayerRank(_PLAYER1);
	SetPlayerRank(_PLAYER2);
	ResetData(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
	system("cls");
	DrawBoard(BOARD_SIZE, BOARD_SIZE, 3, 1, LEFT, TOP);
	ShowTurn(_A, _PLAYER1, _PLAYER2, _TURN);
	GotoXY(_X, _Y);
}

void RunGame(_POINT _A[][BOARD_SIZE], _PLAYER & _PLAYER1, _PLAYER & _PLAYER2, bool & _TURN, int & _COMMAND, int & _X, int & _Y)
{
	bool validEnter = true;
	bool runGame = true;
	int escOption;

	PlaySoundA("NhacGame.wav", NULL, SND_ASYNC | SND_LOOP);
	while (runGame)
	{
		ShowPlayerInfo(_A, _PLAYER1, _PLAYER2);
		GotoXY(_X, _Y);
		_COMMAND = toupper(_getch());
		if (_COMMAND == ESC)
		{
			escOption = SelectMenu(EscMenu(_A));
			RunEscMenu(_A, _PLAYER1, _PLAYER2, _TURN, escOption, runGame);
		}
		else
		{
			if (_COMMAND == 'W' || _COMMAND == ARROW_UP) MoveUp(_A, _X, _Y);
			else if (_COMMAND == 'S' || _COMMAND == ARROW_DOWN) MoveDown(_A, _X, _Y);
			else if (_COMMAND == 'A' || _COMMAND == ARROW_LEFT) MoveLeft(_A, _X, _Y);
			else if (_COMMAND == 'D' || _COMMAND == ARROW_RIGHT) MoveRight(_A, _X, _Y);
			else if (_COMMAND == ENTER || _COMMAND == SPACE)
			{
				switch (CheckBoard(_A, _TURN, GetRowIndex(_Y), GetColIndex(_X)))
				{
				case P_X:
					PrintText("X", 252, _X, _Y);
					break;
				case P_O:
					PrintText("O", 250, _X, _Y);
					break;
				case 0:
					validEnter = false;
					break;
				}
				if (validEnter)
				{
					switch (ProcessFinish(_A, _PLAYER1, _PLAYER2, _TURN, TestBoard(_A, _TURN, GetRowIndex(_Y), GetColIndex(_X))))
					{
					case P_X:case P_O:case 0:
						DrawBoard(1, 1, 30, 8, _A[0][BOARD_SIZE - 1].x + 58, Y_CENTER - 7);
						PrintText("Do you want to continue?", 249, _A[0][BOARD_SIZE - 1].x + 62, Y_CENTER - 4);
						if (AskContinue(_A[0][BOARD_SIZE - 1].x + 65, Y_CENTER - 2))
						{
							StartGame(_A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
							PlaySoundA("NhacGame.wav", NULL, SND_ASYNC | SND_LOOP);
						}
						else
						{
							runGame = false;
						}
						break;
					}
				}
			}
			validEnter = true;
		}
	}
	PlaySoundA("NoSound.wav", NULL, SND_ASYNC);
}

void SaveGame(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN)
{
	bool overwrite = false;
	bool save = true;
	string filename;
	char key;
	int option;

	do
	{
		system("cls");
		PrintText("Nhap ten muon luu game: ", 245, X_CENTER - 30, Y_CENTER);
		std::getline(cin, filename);
		filename += ".txt";
		if (CheckFileExistence(filename))
		{
			PrintText("Ten da ton tai", 245, X_CENTER - 30, Y_CENTER + 2);
			PrintText("Ban co muon luu de?", 245, X_CENTER - 30, Y_CENTER + 4);
			option = SelectMenu(YesNoMenu(X_CENTER - 15, Y_CENTER + 5));
			key = RunYesNoMenu(option);
			if (key == 'Y')
			{
				overwrite = true;
				save = false;
			}
		}
		else save = false;
	} while (save);

	SaveData(filename, _A, _PLAYER1, _PLAYER2, _TURN);

	if (!overwrite)
	{
		std::fstream saveFile;
		saveFile.open(SAVED_LIST, std::fstream::app);

		saveFile << filename << "\n";

		saveFile.close();
	}
}

void LoadGame(string filename, _POINT _A[][BOARD_SIZE], _PLAYER & _PLAYER1, _PLAYER & _PLAYER2, bool & _TURN, int & _COMMAND, int & _X, int & _Y)
{
	system("cls");
	LoadData(filename, _A, _PLAYER1, _PLAYER2, _TURN, _COMMAND, _X, _Y);
	SetPlayerRank(_PLAYER1);
	SetPlayerRank(_PLAYER2);
	DrawBoard(BOARD_SIZE, BOARD_SIZE, 3, 1, LEFT, TOP);
	ShowTurn(_A, _PLAYER1, _PLAYER2, _TURN);
	DrawLoaded(_A);
	GotoXY(_X, _Y);
}

void ExitGame(bool & run)
{
	run = false;
	system("cls");
	DrawBigText("End.txt", 94, 15, Y_CENTER - 7);
	Sleep(3000);
}

bool MoveLeft(_POINT _A[][BOARD_SIZE], int& _X, int& _Y)
{
	if (_X > _A[0][0].x)
	{
		_X -= HORIZONTAL_DISTANCE;
		GotoXY(_X, _Y);
		return true;
	}
	return false;
}

bool MoveRight(_POINT _A[][BOARD_SIZE], int& _X, int& _Y)
{
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		_X += HORIZONTAL_DISTANCE;
		GotoXY(_X, _Y);
		return true;
	}
	return false;
}

bool MoveDown(_POINT _A[][BOARD_SIZE], int& _X, int& _Y)
{
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += VERTICAL_DISTANCE;
		GotoXY(_X, _Y);
		return true;
	}
	return false;
}

bool MoveUp(_POINT _A[][BOARD_SIZE], int& _X, int& _Y)
{
	if (_Y > _A[0][0].y)
	{
		_Y -= VERTICAL_DISTANCE;
		GotoXY(_X, _Y);
		return true;
	}
	return false;
}
