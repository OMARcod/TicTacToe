#include <iostream>
#include<random>

std::random_device seed;
std::mt19937 rndEngine(seed());

void ChangeArray(char a[][3], char letter);
void ChangeArrayAtLocation(char a[][3], char letter, int index, int player);
void DipslayArray(char a[][3]);
int AskForInputGame(std::string playerName);
int AskForInputMenu();
int CheckInput();
bool CheckIndexIsUsed(int index);
bool CheckIfFull();
bool CheckIfWin();
bool CheckHorisontalWin();
bool CheckVerticalWin();
bool CheckCurvedLineWin();
bool CheckThisRow(int beginIndex, int player, int toAdd);
void ShowMenu();
void ResetTheGame(char array[][3]);
int RandomIndex();
int EasyEnemi();
int RandomNumber(int aMin, int aMax);
int RandomIndex();
int returnEmptyIndex();
void PlayTicTacToe();


static int const arraySize = 9;
static int usedSpace[arraySize]{ 0 };

enum class Player
{
	X = 1,
	O = 2,
};
int playerO = static_cast<int>(Player::O);
int playerX = static_cast<int>(Player::X);

int main()
{
	PlayTicTacToe();
	return 0;
}

void PlayTicTacToe()
{
	const int row = 3, column = 3;
	char array2D[3][3];
	int index = 0;


	bool isPlaying = true;
	bool firstPlayer = true;
	ShowMenu();
	index = AskForInputMenu();

	std::string player1 = "";
	std::string player2 = "";

	bool GameNotExit = true;

	if (index == 0)
	{
		GameNotExit = false;
	}
	else
	{
		system("cls");
		std::cout << "First Player Name: ";
		std::cin >> player1;


		system("cls");
		ChangeArray(array2D, ' ');
		DipslayArray(array2D);
		std::cout << "Type the the number of the box that you want to use:" << std::endl;
	}
	bool wantToPlay = true;

	while (GameNotExit)
	{
		while (wantToPlay)
		{
			while (isPlaying)
			{
				if (firstPlayer)
				{
					index = AskForInputGame(player1);
				}
				else
				{
					index = returnEmptyIndex();
				}
				if (CheckIndexIsUsed(index))
				{
					std::cout << index << ": box is used! Pleas chose another box" << std::endl;
				}
				else
				{
					if (firstPlayer)
					{
						ChangeArrayAtLocation(array2D, 'X', index, static_cast<int>(Player::X));
						firstPlayer = false;
					}
					else
					{
						ChangeArrayAtLocation(array2D, 'O', index, static_cast<int>(Player::O));
						firstPlayer = true;
					}
					DipslayArray(array2D);
				}
				if (CheckIfWin())
				{
					if (firstPlayer)
					{
						std::cout << "the comp have Won!" << std::endl;
						isPlaying = false;
					}
					else
					{
						std::cout << player2 << " You Won!" << std::endl;
						isPlaying = false;
					}
				}
				else if (CheckIfFull())
				{
					std::cout << "The box is full" << std::endl;
					isPlaying = false;
				}
			}

			std::cout << "==========================" << std::endl;
			std::cout << "Do you want to play again?" << std::endl;
			std::cout << "1. Yes" << std::endl;
			std::cout << "0. No!" << std::endl;
			if (AskForInputMenu() == 0)
			{
				wantToPlay = false;
				ResetTheGame(array2D);
			}
			else
			{
				isPlaying = true;
				ResetTheGame(array2D);
			}
		}

		ShowMenu();
		index = AskForInputMenu();
		if (index == 0)
		{
			GameNotExit = false;
		}
		else
		{
			wantToPlay = true;
			isPlaying = true;
			system("cls");
			std::cout << "First Player Name: ";
			std::cin >> player1;
			std::cout << "Secund Player Name: ";
			std::cin >> player2;

			system("cls");
			ChangeArray(array2D, ' ');
			DipslayArray(array2D);
			std::cout << "Type the the number of the box that you want to use:" << std::endl;
		}
	}



}

void ResetTheGame(char array[][3])
{
	for (int i = 0; i < arraySize; i++)
	{
		usedSpace[i] = 0;
	}
	ChangeArray(array, ' ');
	DipslayArray(array);
}

int AskForInputGame(std::string playerName)
{
	int index = 0;
	std::cout << playerName <<" Input: ";

	index = CheckInput();
	while (index < 1 || index > arraySize)
	{
		std::cout << "Pleas Enter a number between 1 and 9 ...." << std::endl;
		std::cout << "Your Input: ";
		index = CheckInput();
	}
	return  index;
}

int EasyEnemi()
{
	int index = 0;

	index = RandomIndex();
	while (index < 1 || index > arraySize)
	{
		std::cout << "Pleas Enter a number between 1 and 9 ...." << std::endl;
		std::cout << "Your Input: ";
		index = RandomIndex();
	}
	return  index;
}

int RandomIndex()
{
	
	int lastIndex = arraySize -1;
	int index = RandomNumber(1, lastIndex);
	bool isUsed = true;
	while (isUsed)
	{
		if (usedSpace[index] > 0 && usedSpace[index] < 3)
		{
			index = RandomNumber(1, lastIndex);
		}
		else
		{
			return index;
		}
	}
}

int RandomNumber(int aMin, int aMax)
{
	
	std::uniform_int_distribution<int> rndDist(aMin, aMax);
	int randomNr = rndDist(rndEngine);
	return randomNr;
}

int returnEmptyIndex()
{
	int RandomLoop = RandomNumber(0, 10);
	
	
	int random = 5;

	for (int i = 0; i < 5; i++)
	{
		if (!(CheckIndexIsUsed(random)))
		{
			return random;
		}
		random = RandomNumber(1, 9);
	}

	if (RandomLoop > 5)
	{
		for (int i = 1; i < arraySize + 1; i++)
		{
			if (!(CheckIndexIsUsed(i)))
			{
				return i;
			}
		}
	}
	else
	{
		for (int i = arraySize; i > 0; i--)
		{
			if (!(CheckIndexIsUsed(i)))
			{
				return i;
			}
		}
	}
	
}

int AskForInputMenu()
{
	int index = 0;
	std::cout << "Your Input: ";

	index = CheckInput();
	while (index < 0 || index > 1 )
	{
		std::cout << "Pleas Enter 0 or 1 ...." << std::endl;
		std::cout << "Your Input: ";
		index = CheckInput();
	}
	return  index;
}

int CheckInput()
{
	int input;
	std::cin >> input;
	while (true)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "You have entered wrong input" << std::endl;
			std::cin >> input;
		}
		if (!std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			break;
		}
	}
	return input;
}

void DipslayArray(char a[][3])
{
	int boxNr = 1;

	system("cls");
	std::cout << "-----------------" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			std::cout << " | " << a[i][k];
		}
		std::cout << " | "; //last 

		//other box
		std::cout << "\t\t";
		for (int i = 0; i < 3; i++)
		{
			std::cout << " | " << boxNr;
			boxNr++;
		}
		std::cout << " | "; //last 
		
		
		std::cout << "\n-----------------" << std::endl;
	}
}

void ChangeArray(char a[][3],char letter)
{
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			a[i][k] = letter;
		}
	}
}

bool CheckIndexIsUsed(int index)
{
	bool isUsed = false;
	if (usedSpace[index - 1] == 1 || usedSpace[index - 1] == 2)
	{
		isUsed = true;
	}
	return isUsed;
}

void ChangeArrayAtLocation(char a[][3], char letter, int index, int player)
{
	int row = 0;
	int column = 0;

	switch (index)
	{
	case 1:
		row = 0;
		column = 0;
		usedSpace[index-1] += player;

		break;
	case 2:
		row = 0;
		column = 1;
		usedSpace[index - 1] += player;

		break;
	case 3:
		row = 0;
		column = 2;
		usedSpace[index - 1] += player;
		break;
	case 4:
		row = 1;
		column = 0;
		usedSpace[index - 1] += player;
		break;
	case 5:
		row = 1;
		column = 1;
		usedSpace[index - 1] += player;
		break;
	case 6:
		row = 1;
		column = 2;
		usedSpace[index - 1] += player;
		break;
	case 7:
		row = 2;
		column = 0;
		usedSpace[index - 1] += player;
		break;
	case 8:
		row = 2;
		column = 1;
		usedSpace[index - 1] += player;
		break;
	case 9:
		row = 2;
		column = 2;
		usedSpace[index - 1] += player;
		break;
	default:
		break;
	}

	a[row][column] = letter;
}

bool CheckIfFull()
{
	bool isFull = false;
	int nrOfBoxesUsed = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (usedSpace[i] == 1 || usedSpace[i] == 2)
		{
			nrOfBoxesUsed++;
		}
	}
	if (nrOfBoxesUsed >= arraySize)
	{
		isFull = true;
	}
	return isFull;
}

bool CheckIfWin()
{
	bool isWin = CheckHorisontalWin();

	if (!isWin) 
	{
		isWin = CheckVerticalWin();

		if (!isWin)
		{
			isWin = CheckCurvedLineWin();
		}
	}
	
	return isWin;
}

bool CheckHorisontalWin()
{
	bool isWin = false;
	int beginIndex = 0;
	int row = 3;
	for (int i = 0; i < row; i++)
	{
		if (CheckThisRow(beginIndex, playerX, 1))
		{
			isWin = true;
			break;
		}
		else if (CheckThisRow(beginIndex, playerO, 1))
		{
			isWin = true;
			break;
		}
		beginIndex += 3;
	}
	
	return isWin;
}

bool CheckVerticalWin()
{
	bool isWin = false;
	int beginIndex = 0;
	int column = 3;
	for (int i = 0; i < column; i++)
	{
		if (CheckThisRow(beginIndex, playerX, 3))
		{
			isWin = true;
			break;
		}
		else if (CheckThisRow(beginIndex, playerO, 3))
		{
			isWin = true;
			break;
		}
		beginIndex += 1;
	}
	return isWin;
}

bool CheckThisRow(int beginIndex, int player, int toAdd)
{
	if (usedSpace[beginIndex] == player && usedSpace[beginIndex + toAdd] == player && usedSpace[beginIndex + (toAdd*2)] == player)
	{
		return true;
	}
	return false;
}

bool CheckCurvedLineWin()
{
	bool isWin = false;
	int line = 2;
	int secuondLine = 2; //box that begin in indix 2
	int firstLine = 0; //box that begin at index 0
	for (int i = 0; i < line; i++)
	{
		
		if (CheckThisRow(firstLine, playerX, 4))
		{
			isWin = true;
			break;
		}
		else if (CheckThisRow(firstLine, playerO, 4))
		{
			isWin = true;
			break;
		}
	}
	for (int i = 0; i < line; i++)
	{
		if (CheckThisRow(secuondLine, playerX, 2))
		{
			isWin = true;
			break;
		}
		else if (CheckThisRow(secuondLine, playerO, 2))
		{
			isWin = true;
			break;
		}
	}
	return isWin;
}

void ShowMenu()
{
	system("cls");
	std::cout << "================================" << std::endl;
	std::cout << "Welcome to the Tic Tac Toe Game!" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << "1. Play New Game" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

// extra
// show score
// option to start new game or play the same 
