#include "Model.h"

void SetPlayer(_PLAYER& _PLAYER1, _PLAYER& _PLAYER2)
{
	system("cls");
	do
	{
		PrintText("Enter Player1's name (2-10 characters): ", 252, X_CENTER - 24, Y_CENTER);
		std::getline(cin, _PLAYER1.name);
		DrawBox(255, 100, 1, X_CENTER, Y_CENTER);
	} while (_PLAYER1.name.length() < 2 || _PLAYER1.name.length() > 10);
	do
	{
		PrintText("Enter Player2's name (2-10 characters): ", 250, X_CENTER - 24, Y_CENTER);
		std::getline(cin, _PLAYER2.name);
		DrawBox(255, 100, 1, X_CENTER, Y_CENTER);
	} while (_PLAYER2.name.length() < 2 || _PLAYER2.name.length() > 10 || _PLAYER2 == _PLAYER1);

	_PLAYER1 = LoadPlayer(_PLAYER1);
	_PLAYER2 = LoadPlayer(_PLAYER2);
}

std::vector<_PLAYER> GetPlayerList()
{
	_PLAYER player;
	std::vector<_PLAYER> players;
	std::fstream playerList;
	std::string clear;
	std::string name;
	playerList.open(PLAYER_LIST, std::fstream::in);

	while (getline(playerList, player.name))
	{
		playerList >> player.wins;
		getline(playerList, clear);
		players.push_back(player);
	}

	playerList.close();

	return players;
}

int CheckPlayerExistence(_PLAYER player)
{
	std::vector<_PLAYER> players = GetPlayerList();

	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i) == player) return i;
	}

	return -1;
}

void SavePlayer(_PLAYER player)
{
	int exist = CheckPlayerExistence(player);
	std::vector<_PLAYER> players = GetPlayerList();
	std::fstream playerList;
	playerList.open(PLAYER_LIST, std::fstream::out);

	if (exist == -1) players.push_back(player);
	else players.at(exist).wins = player.wins;


	SortPlayerList(players);
	for (int i = 0; i < players.size(); i++)
	{
		playerList << players.at(i).name << "\n" << players.at(i).wins << "\n";
	}

	playerList.close();

}

_PLAYER LoadPlayer(_PLAYER player)
{
	std::vector<_PLAYER> players;
	players = GetPlayerList();
	int exist = CheckPlayerExistence(player);

	if (exist == -1)
	{
		player.wins = 0;
		SavePlayer(player);
		return player;
	}
	else return players.at(exist);
}

void SetPlayerRank(_PLAYER& player)
{
	int exist = CheckPlayerExistence(player);
	player.rank = exist + 1;
}

int GetRowIndex(int pY)
{
	int rowIndex;

	rowIndex = (pY - TOP - 1) / VERTICAL_DISTANCE;

	return rowIndex;
}

int GetColIndex(int pX)
{
	int colIndex;

	colIndex = (pX - LEFT - 2) / HORIZONTAL_DISTANCE;

	return colIndex;
}

void SortPlayerList(std::vector<_PLAYER>& playerList)
{
	_PLAYER key;
	int j;

	for (int i = 1; i < playerList.size(); i++)
	{
		key = playerList.at(i);
		j = i - 1;
		while (j >= 0 && playerList.at(j) < key)
		{
			playerList.at(j + 1) = playerList.at(j);
			j--;
		}
		playerList.at(j + 1) = key;
	}
}


void ResetData(_POINT _A[][BOARD_SIZE], _PLAYER & _PLAYER1, _PLAYER & _PLAYER2, bool & _TURN, int & _COMMAND, int & _X, int & _Y)
{
	//Khoi tao du lieu ban co
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//Trung hoanh do va tung do cua ma tran ban co voi console
			_A[i][j].x = LEFT + j * HORIZONTAL_DISTANCE + 2;
			_A[i][j].y = TOP + i * VERTICAL_DISTANCE + 1;

			_A[i][j].c = 0; //Tat ca vi tri deu chua danh
		}
	}
	//Khoi tao luot choi
	_TURN = FIRST;
	//Khoi tao phim
	_COMMAND = -1;
	//Khoi tao vi tri ban dau
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
}

void SaveData(string filename, _POINT _A[][BOARD_SIZE], _PLAYER _PLAYER1, _PLAYER _PLAYER2, bool _TURN)
{
	std::fstream saveFile;
	saveFile.open(filename, std::fstream::out);

	SavePlayer(_PLAYER1);
	SavePlayer(_PLAYER2);

	saveFile << _PLAYER1.name << "\n";
	saveFile << _PLAYER2.name << "\n";

	saveFile << _TURN << " \n";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			saveFile << _A[i][j].c << " ";
		}
		saveFile << "\n";
	}

	saveFile.close();
}

void LoadData(string filename, _POINT _A[][BOARD_SIZE], _PLAYER & _PLAYER1, _PLAYER & _PLAYER2, bool & _TURN, int & _COMMAND, int & _X, int & _Y)
{
	std::ifstream loadFile;
	loadFile.open(filename.c_str());

	getline(loadFile, _PLAYER1.name);
	_PLAYER1 = LoadPlayer(_PLAYER1);

	getline(loadFile, _PLAYER2.name);
	_PLAYER2 = LoadPlayer(_PLAYER2);

	loadFile >> _TURN;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = HORIZONTAL_DISTANCE * j + LEFT + 2; //Trung voi hoanh do ban co
			_A[i][j].y = VERTICAL_DISTANCE * i + TOP + 1; //Trung voi tung do ban co
			loadFile >> _A[i][j].c;
		}
	}
	loadFile.close();

	_COMMAND = -1;

	//Thiet lap lai toa do ban dau
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
}

std::vector<string> LoadFiles()
{
	std::vector<string> files;
	string filename;

	std::fstream savedFile;
	savedFile.open(SAVED_LIST, std::fstream::in);

	while (savedFile >> filename)
	{
		files.push_back(filename);
	}
	savedFile.close();

	return files;
}

bool CheckFileExistence(string filename)
{
	string name; // filename cua cac file da luu trong savedlist.txt
	std::fstream savedFile;
	savedFile.open(SAVED_LIST, std::fstream::in);

	while (savedFile >> name)
	{
		if (name == filename)
		{
			savedFile.close();
			return true;
		}
	}

	savedFile.close();
	return false;
}

int CheckBoard(_POINT _A[][BOARD_SIZE], bool _TURN, int cRow, int cCol)
{
	if (_A[cRow][cCol].c == 0)
	{
		_A[cRow][cCol].c = (_TURN) ? P_X : P_O;
		return _A[cRow][cCol].c;
	}
	else return 0;
}

bool CheckWin(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol)
{
	if (HorizontalCheck(_A, currentRow, currentCol) || VerticalCheck(_A, currentRow, currentCol) || BackwardSlashCheck(_A, currentRow, currentCol) || ForwardSlashCheck(_A, currentRow, currentCol))
		return true;
	else return false;
}

bool HorizontalCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol)
{
	int countWin = 1;
	bool blockRight = false;
	bool blockLeft = false;
	bool wall = false;
	int count = 1;
	bool keepCounting = true;

	if (currentCol == 0 || currentCol == BOARD_SIZE - 1) wall = true;

	while (currentCol + count < BOARD_SIZE)
	{
		if ((_A[currentRow][currentCol + count].c != 0) && (_A[currentRow][currentCol + count].c != _A[currentRow][currentCol].c))
		{
			blockRight = true;
			break;
		}
		else if ((_A[currentRow][currentCol + count].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentCol + count == BOARD_SIZE - 1) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	count = 1;
	keepCounting = true;

	while (currentCol - count > -1)
	{
		if ((_A[currentRow][currentCol - count].c != 0) && (_A[currentRow][currentCol - count].c != _A[currentRow][currentCol].c))
		{
			blockLeft = true;
			break;
		}
		else if ((_A[currentRow][currentCol - count].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentCol - count == 0) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	if (!blockLeft && !blockRight && !wall && (countWin == 4))
		return true;
	else if (countWin >= 5 && !(blockRight && blockLeft))
		return true;
	else
		return false;
}

bool VerticalCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol)
{
	int countWin = 1;
	bool blockUp = false;
	bool blockDown = false;
	bool wall = false;
	int count = 1;
	bool keepCounting = true;

	if (currentRow == 0 || currentRow == BOARD_SIZE - 1) wall = true;

	while (currentRow + count < BOARD_SIZE)
	{
		if ((_A[currentRow + count][currentCol].c != 0) && (_A[currentRow + count][currentCol].c != _A[currentRow][currentCol].c))
		{
			blockDown = true;
			break;
		}
		else if ((_A[currentRow + count][currentCol].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentRow + count == BOARD_SIZE - 1) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	count = 1;
	keepCounting = true;

	while (currentRow - count > -1)
	{
		if ((_A[currentRow - count][currentCol].c != 0) && (_A[currentRow - count][currentCol].c != _A[currentRow][currentCol].c))
		{
			blockUp = true;
			break;
		}
		else if ((_A[currentRow - count][currentCol].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentRow - count == 0) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	if (!blockUp && !blockDown && !wall && (countWin == 4))
		return true;
	else if (countWin >= 5 && !(blockUp && blockDown))
		return true;
	else
		return false;
}

bool ForwardSlashCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol)
{
	int countWin = 1;
	bool blockUp = false;
	bool blockDown = false;
	bool wall = false;
	int count = 1;
	bool keepCounting = true;

	if (currentCol == 0 || currentCol == BOARD_SIZE - 1 || currentRow == 0 || currentRow == BOARD_SIZE - 1) wall = true;

	while (currentRow + count < BOARD_SIZE && currentCol - count > -1)
	{
		if ((_A[currentRow + count][currentCol - count].c != 0) && (_A[currentRow + count][currentCol - count].c != _A[currentRow][currentCol].c))
		{
			blockDown = true;
			break;
		}
		else if ((_A[currentRow + count][currentCol - count].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentRow + count == BOARD_SIZE - 1 || currentCol - count == 0) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	count = 1;
	keepCounting = true;

	while (currentRow - count > -1 && currentCol + count < BOARD_SIZE)
	{
		if ((_A[currentRow - count][currentCol + count].c != 0) && (_A[currentRow - count][currentCol + count].c != _A[currentRow][currentCol].c))
		{
			blockUp = true;
			break;
		}
		else if ((_A[currentRow - count][currentCol + count].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentCol + count == BOARD_SIZE - 1 || currentRow - count == 0) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	if (!blockUp && !blockDown && !wall && (countWin == 4))
		return true;
	else if (countWin >= 5 && !(blockUp && blockDown))
		return true;
	else
		return false;
}

bool BackwardSlashCheck(_POINT _A[][BOARD_SIZE], int currentRow, int currentCol)
{
	int countWin = 1;
	bool blockUp = false;
	bool blockDown = false;
	bool wall = false;
	int count = 1;
	bool keepCounting = true;

	if (currentCol == 0 || currentCol == BOARD_SIZE - 1 || currentRow == 0 || currentRow == BOARD_SIZE - 1) wall = true;

	while (currentRow + count < BOARD_SIZE && currentCol + count < BOARD_SIZE)
	{
		if ((_A[currentRow + count][currentCol + count].c != 0) && (_A[currentRow + count][currentCol + count].c != _A[currentRow][currentCol].c))
		{
			blockDown = true;
			break;
		}
		else if ((_A[currentRow + count][currentCol + count].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentRow + count == BOARD_SIZE - 1 || currentCol + count == BOARD_SIZE - 1) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	count = 1;
	keepCounting = true;

	while (currentRow - count > -1 && currentCol - count > -1)
	{
		if ((_A[currentRow - count][currentCol - count].c != 0) && (_A[currentRow - count][currentCol - count].c != _A[currentRow][currentCol].c))
		{
			blockUp = true;
			break;
		}
		else if ((_A[currentRow - count][currentCol - count].c == _A[currentRow][currentCol].c) && keepCounting)
		{
			if (currentRow - count == 0 || currentCol - count == 0) wall = true;
			countWin++;
			count++;
		}
		else
		{
			count++;
			keepCounting = false;
		}
	}

	if (!blockUp && !blockDown && !wall && (countWin == 4))
		return true;
	else if (countWin >= 5 && !(blockUp && blockDown))
		return true;
	else
		return false;
}

bool CheckTie(_POINT _A[][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].c == 0) return false;
		}
	}
	return true;
}

int TestBoard(_POINT _A[][BOARD_SIZE], bool _TURN, int cRow, int cCol)
{
	if (CheckTie(_A)) return 0; //Hoa
	else
	{
		if (CheckWin(_A, cRow, cCol))
			return (_TURN == FIRST ? P_X : P_O); //-1 nghia la luot 'true' thang
		else
			return 2;
	}
}