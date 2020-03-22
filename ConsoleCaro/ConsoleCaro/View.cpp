#include "View.h"

void CreateConsoleWindow(int pWidth, int pHeight)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,240);
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, 0, 0, pWidth, pHeight, TRUE);
}

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void DrawTableLine(int numOfCol, char mainSym, char subSym, int width)
{
	for (int i = 0; i < numOfCol - 1; i++)
	{
		for (int i = 0; i < width; i++) cout << mainSym;
		cout << subSym;
	}
	for (int i = 0; i < width; i++) cout << mainSym;
}

void DrawBoard(int row, int col, int width, int height, int x, int y)
{
	GotoXY(x, y);
	cout << TOP_LEFT;
	DrawTableLine(col, HORIZONTAL_LINE, TOP_CROSS, width);
	cout << TOP_RIGHT;

	for (int i = 0; i < (row - 1) * (height + 1); i++)
	{
		GotoXY(x, y + i + 1);
		if ((i + 1) % (height + 1) != 0)
		{
			cout << VERTICAL_LINE;
			DrawTableLine(col, SPACE, VERTICAL_LINE, width);
			cout << VERTICAL_LINE;
		}
		else
		{
			cout << LEFT_CROSS;
			DrawTableLine(col, HORIZONTAL_LINE, CROSS, width);
			cout << RIGHT_CROSS;
		}
	}
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + (row - 1) * (height + 1) + 1 + i);
		cout << VERTICAL_LINE;
		DrawTableLine(col, SPACE, VERTICAL_LINE, width);
		cout << VERTICAL_LINE;
	}

	GotoXY(x, y + (row - 1) * (height + 1) + 1 + height);
	cout << BOTTOM_LEFT;
	DrawTableLine(col, HORIZONTAL_LINE, BOTTOM_CROSS, width);
	cout << BOTTOM_RIGHT;
}

void DrawLoaded(_POINT _A[][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			if (_A[i][j].c == P_X)
			{
				PrintText("X", 252, _A[i][j].x, _A[i][j].y);
			}
			else if (_A[i][j].c == P_O)
			{
				PrintText("O", 250, _A[i][j].x, _A[i][j].y);
			}
	}
}

_MENU MainMenu()
{
	_MENU menu;

	menu.options = 5;
	menu.x = X_CENTER - 13;
	menu.y = Y_CENTER + 10;
	menu.cursorColor = 219;

	system("cls");

	DrawBigText("Logo.txt", 253, 12, 1);
	DrawBox(221, 50, 13, X_CENTER - 25, Y_CENTER + 5);
	PrintText("***************************", 219, menu.x, menu.y - 3);
	PrintText("*    Welcome to Caroro    *", 219, menu.x, menu.y - 2);
	PrintText("***************************", 219, menu.x, menu.y - 1);
	PrintText("         Start Game        ", 219, menu.x, menu.y);
	PrintText("         Load Game         ", 219, menu.x, menu.y + 1);
	PrintText("          Ranking          ", 219, menu.x, menu.y + 2);
	PrintText("           Help            ", 219, menu.x, menu.y + 3);
	PrintText("         Exit Game         ", 219, menu.x, menu.y + 4);

	return menu;
}

_MENU LoadingMenu()
{
	_MENU menu;
	string name;


	std::vector<string> files;
	files = LoadFiles();

	menu.options = files.size();
	menu.x = X_CENTER - 15;
	menu.y = Y_CENTER - files.size() / 2;
	menu.cursorColor = 219;

	DrawBox(221, 100, menu.options + 10, X_CENTER - 50, Y_CENTER - 5);
	PrintText("[==========Saved Games===========]", 219, menu.x, menu.y - 2);
	for (int i = 0; i < files.size(); i++)
	{
		name = "         " + files.at(i);
		PrintText(name, 223, menu.x, menu.y + i);
	}

	return menu;
}

_MENU EscMenu(_POINT _A[][BOARD_SIZE])
{
	_MENU menu;

	menu.options = 3;
	menu.x = _A[0][BOARD_SIZE - 1].x + 65;
	menu.y = Y_CENTER + 3;
	menu.cursorColor = 75;

	//DrawBoard(1, 1, 62, 25, menu.x - 23, menu.y - 19);
	DrawBox(75, 63, 25, menu.x - 23, menu.y - 19);
	DrawBigText("EscLogo.txt", 75, menu.x - 22, menu.y - 17);
	PrintText("    Continue    ", 75, menu.x, menu.y);
	PrintText("    Save game   ", 75, menu.x, menu.y + 1);
	PrintText("    Exit game   ", 75, menu.x, menu.y + 2);

	return menu;
}

_MENU YesNoMenu(int x, int y)
{
	_MENU menu;

	menu.options = 2;
	menu.x = x;
	menu.y = y;
	menu.cursorColor = 249;

	PrintText("Yes", 245, menu.x, menu.y);
	PrintText("No", 245, menu.x, menu.y + 1);

	return menu;
}

void ShowTurn(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN)
{
	int start = _A[0][BOARD_SIZE - 1].x + 12;

	DrawBox(255, 30, 10, start, 2);

	DrawBigText((_TURN) ? "X.txt" : "O.txt", (_TURN) ? 252 : 250, start, 2);

	DrawBox(255, 20, 1, start - 2, 14);
	PrintText(((_TURN) ? _PLAYER1.name : _PLAYER2.name) + "'s turn!", (_TURN) ? 252 : 250, start - 2, 14);
}

void ShowPlayerInfo(_POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2)
{
	int start = _A[0][BOARD_SIZE - 1].x + 4;

	DrawBoard(3, 3, 10, 1, start, 17);

	PrintText(_PLAYER1.name, 253, start + 12, 18);
	PrintText(_PLAYER2.name, 253, start + 23, 18);
	PrintText("Win games", 253, start + 1, 20);
	PrintText(std::to_string(_PLAYER1.wins), 253, start + 12, 20);
	PrintText(std::to_string(_PLAYER2.wins), 253, start + 23, 20);
	PrintText("Rank", 253, start + 1, 22);
	PrintText(std::to_string(_PLAYER1.rank), 253, start + 12, 22);
	PrintText(std::to_string(_PLAYER2.rank), 253, start + 23, 22);
}

void ShowHelp()
{
	int x = X_CENTER - 15;
	int y = Y_CENTER - 10;
	string line;
	int i = 0;

	std::fstream helpFile;
	helpFile.open("Help.txt", std::fstream::in);

	system("cls");
	while (getline(helpFile, line))
	{
		PrintText(line, 243, x, y + i);
		i++;
	}
}

void ShowRank()
{
	int x = X_CENTER - 10;
	int y = Y_CENTER - 10;
	std::vector<_PLAYER> players = GetPlayerList();

	system("cls");

	PrintText("********************", 253, x, y);
	PrintText("* ~TOP 10 PLAYERS~ *", 253, x, y + 1);
	PrintText("********************", 253, x, y + 2);
	PrintText("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", 253, x - 10, y + 4);
	PrintText("[Master King] " + players.at(0).name, 252, x - 2, y + 6);
	PrintText("[King] " + players.at(1).name, 251, x - 2, y + 7);
	for (int i = 2; i < 10; i++)
	{
		PrintText("[Master] " + players.at(i).name, 249, x - 2, y + 6 + i);
	}

	PrintText("-Press Esc to turn back-", 253, x - 2, y + 16);
}

void GotoXY(int x, int y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBox(int color, int width, int height, int x, int y)
{
	SetColor(color);
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + i);
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
	}
	SetColor(240);
}

void SetColor(int color)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void PrintText(string text, int color, int x, int y)
{
	GotoXY(x, y);
	SetColor(color);
	cout << text;
	SetColor(240);
}

void DrawBigText(string filename, int color, int x, int y)
{
	std::fstream textFile;
	textFile.open(filename.c_str(), std::fstream::in);
	string line;
	std::vector<std::string> line1;
	int tempY = y;
	while (getline(textFile, line)) line1.push_back(line);
	if (filename == "XWin.txt" || filename == "OWin.txt" || filename == "Draw.txt")
	{
		int count = 0;
		while (count <= 48)
		{
			for (int i = 0; i < line1.size(); i++)
				PrintText(line1[i], color + count % 10, x, y++);
			y = tempY;
			Sleep(100);
			for (int i = 0; i < line1.size(); i++)
			{
				string templine = "";
				for (int j = 0; j < line1[i].length(); j++) templine += ' ';
				PrintText(templine, 240, x, y++);
			}
			Sleep(100);
			y = tempY;
			count++;
		}
	}
	for (int i = 0; i < line1.size(); i++)
		PrintText(line1[i], color, x, y++);
	textFile.close();
}

int ProcessFinish(_POINT _A[][BOARD_SIZE], _PLAYER& _PLAYER1, _PLAYER& _PLAYER2, bool& _TURN, int pWhoWin)
{
	switch (pWhoWin)
	{
	case P_X:
		_PLAYER1.wins++;
		PlaySoundA("WinSounds.wav", NULL, SND_ASYNC);
		DrawBox(111, 100, 12, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		DrawBigText("XWin.txt", 111, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		SavePlayer(_PLAYER1);
		break;
	case P_O:
		_PLAYER2.wins++;
		PlaySoundA("WinSounds.wav", NULL, SND_ASYNC);
		DrawBox(111, 100, 12, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		DrawBigText("OWin.txt", 111, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		SavePlayer(_PLAYER2);
		break;
	case 0:
		PlaySoundA("WinSounds.wav", NULL, SND_ASYNC);
		DrawBox(111, 100, 12, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		DrawBigText("Draw.txt", 111, _A[0][0].x + 1, _A[BOARD_SIZE - 1][0].y + 2);
		break;
	case 2:
		_TURN = !_TURN;
		ShowTurn(_A, _PLAYER1, _PLAYER2, _TURN);
		break;
	}
	return pWhoWin;
}

bool AskContinue(int x, int y)
{
	int option;

	option = SelectMenu(YesNoMenu(x, y));
	switch (RunYesNoMenu(option))
	{
	case 'Y':
		return true;
	case 'N':
		return false;
	}
}