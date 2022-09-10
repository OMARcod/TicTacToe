#include <iostream>

//void DisplayArray(char anArray[][3], int row, int column);
void ChangeArray(char a[][3], char letter);
void ChangeArrayAtLocation(char a[][3], char letter, int index, int player);
void DipslayArray(char a[][3]);
int AskForInput();
int CheckInput();
bool CheckIndexIsUsed(int index);
bool CheckIfFull();
int const arraySize = 9;
int usedSpace[arraySize]{ 0 };
bool CheckIfWin();

bool CheckVerticalWin();


enum class Player
{
	O = 1,
	X = 2,
};
//
//int o = static_cast<int>(Player::O);
//int x = static_cast<int>(Player::X);

int main()
{
	const int row = 3, column = 3;
	char array2D[3][3];
	int index = 0;

	//DisplayArray(array2D, 3, 3);

	std::cout << "Type the the number of the box that you want to use:" << std::endl;

	ChangeArray(array2D,' ');
	DipslayArray(array2D);

	bool isPlaying = true;
	bool firstPlayer = true;

	while (isPlaying)
	{
		index = AskForInput();
		if (CheckIndexIsUsed(index))
		{
			std::cout << "this box is used! Pleas chose another box" << std::endl;
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
				std::cout << "The second Player (O) have Won!" << std::endl;
				isPlaying = false;
			}
			else
			{
				std::cout << "The first Player (X) have Won!" << std::endl;
				isPlaying = false;
			}
		}
		else if (CheckIfFull())
		{
				std::cout << "The box is full" << std::endl;
				isPlaying = false;
		}
		
	}



	return 0;
}

int AskForInput()
{
	int index = 0;
	std::cout << "Your Input: ";

	index = CheckInput();
	while (index < 1 || index > arraySize)
	{
		std::cout << "Pleas Enter a number between 1 and 9 ...." << std::endl;
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
			break;
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
	

	int nrOfBox = 0;
	bool isWin = false;
	while (nrOfBox < arraySize)
	{
		if (usedSpace[nrOfBox] == 1 && usedSpace[nrOfBox + 1] == 1 &&  usedSpace[nrOfBox + 2] == 1)
		{
			isWin = true;
			break;
		}
		else if (usedSpace[nrOfBox] == 2 && usedSpace[nrOfBox + 1] == 2 && usedSpace[nrOfBox + 2] == 2)
		{
			isWin = true;
			break;
		}
		nrOfBox += 3;
	}
	return isWin;
}

bool CheckVerticalWin()
{
	return true;
}
//bool CheckHorisontalWin();
//bool CheckCurvedLineWin();

//How to pass the 2d array in a function
//how to display and change the array inside a function inside a forloop

