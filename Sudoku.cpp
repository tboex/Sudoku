#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <numeric>
#include <windows.h>
#include <string>
#define UNASSIGNED 0

using namespace std;
//-------------------------------------------
//Class Declaration
class Sudoku
{
private:
	int size; //size of array - usualy 9
	int delim;  //deliminator - usually 3
	int count;//Counter
	int count1; //Alternate counter
	int count2; //Alternate counter

	int **arr; //Main array for sudoku
	int **temparr; //Set equal to arr for solving purposes
	int *nums;  //Values in the sudoku - usually 1-9
	int temp;  //Temp
	int temp1;  //Alt temp
	int rando;  //Random val - usually 1-9

	bool status; //True - Solved | False - Not Solved
	bool playable; //True - Playable | False - Not Playable
public:
	Sudoku(); //Constructor
	~Sudoku(); //Deconstructor
	//Getter and Setter
	void setSize(int n); //Setter for Size
	void setStatus(bool b); //Setter for Status
	void integrateCount(); //Count++
	int getSize(); //Getter for Size
	int getCount(); //Getter for Count
	bool getStatus(); //Getter for Status
	bool getPlayable(); //Getter for Playable
	//Setup Methods
	void createboard(int k); //Creates 9x9 board
	void displayBoard(int row, int column); //Display for Input - Places X at current
	void displayBoard(); //Displays Board
	void fillBoard(); //Fills board with a full working sudoku
	void degrade(int option); //Degrades board to playable point
	//Checker Methods
	bool checkForInRow(int row, int num); //Checks if num is in row
	bool checkForInColumn(int column, int num); //Checks if num is in Column
	bool checkForInBox(int row, int column, int num); //Checks if num is in Box
	bool UsedInBox(int boxRow, int boxCol, int num); //Checks if num is in Box - Alternate
	bool tempCheckForInRow(int row, int n); //Checks if num is in row
	bool tempCheckForInColumn(int column, int n); //Checks if num is in Column
	bool tempCheckForInBox(int row, int column, int n); //Checks if num is in Box
	bool checkNotFull(int &row, int &col); //Checks if the Sudoku is Full
	bool checkSudoku(); //Checks if the Sudoku is Complete	
	bool isWorking(int row, int col, int num); //Checks if the Sudoku is Complete - Alternate
	bool checkPlayable(); //Checks if the Sudoku is Playable
	//Solve Methods
	void guessSudoku(); //Lets the User guess a value
	bool solveSudoku(); //Solves the Sudoku for the User 
	//Input Method
	void inputSudoku(); //Lets the User Input a Sudoku
	//File IO
	void importSudoku(); //Lets the User Import a Sudoku
	void importSudoku(int option); //Lets the User Import a premade Sudoku
	void exportSudoku(); //Lets the User Save their Sudoku
};
//------------------------------------------
//Constructor|Destructor
Sudoku::Sudoku() 
{
	std::cout << "Welcome to Sudoku" << endl;
}
Sudoku::~Sudoku()
{
	std::cout << "Sudoku is being Deleted" << endl;
}
// -----------------------------------------
//Reminders
/*---------------------------------------------
  --		Reminders						 --
  --										 --
  -- Be careful with system("cls")			 --
  -- hints not working - Fixed				 --
  -- Fill Bord might not work - Fixed		 --
  --										 --
  --										 --
  --										 --
  --------------------------------------------- */
//-----------------------------------------
//Main
void main()
{
	int input; //Used for input 
	bool created = false; //Checks if Board was Created
	bool c1 = false; // c1-c5 bools for completed methods
	bool c2 = false;
	bool c3 = false;
	bool c4 = false;
	bool c5 = false;
	bool saved = false; //Bool for saved 
	Sudoku sudo;	//Class instantiation
//WINDOWS EXCLUSIVE 
#ifdef _WIN32	
	system("color 02"); //Oooh Shiny colors
#endif
	sudo.setSize(9); //Sets size to 9
	sudo.createboard(9); //Creates a board 9x9 
	created = true; 
	c1 = true;
start: //Main Menu Loop
	input = 0;
	system("cls");
	//Shows Progress
		std::cout << "------------------------\n";
		std::cout << "--  Completed Tasks     \n";
		std::cout << "--                      \n";
		if (c2 == true && c3 != true)
		{
			std::cout << "-- Generated Sudoku     \n";
			std::cout << "--                      \n";
		}
		if (c3 == true)
		{
			std::cout << "-- Input Sudoku::     \n";
			std::cout << "--   *Size = " << sudo.getSize() << "\n";
			std::cout << "--   *Nums = " << "1-" << sudo.getSize() << "\n";
			std::cout << "--                      \n";
		}
		if (c4 == true)
		{
			std::cout << "-- Checked if Sudoku is working::     \n";
			if (sudo.getStatus() == true)
			{
				std::cout << "--   *Status = Working\n";
			}
			else
			{
				std::cout << "--   *Status = Not Working\n";
			}			
			std::cout << "--                      \n";
		}
		if (c5 == true)
		{
			std::cout << "-- Checked if Sudoku is playable::     \n";
			if (sudo.getPlayable() == true)
			{
				std::cout << "--   *Status = Playable\n";
			}
			else
			{
				std::cout << "--   *Status = Not Playable\n";
			}
			std::cout << "--                      \n";
		}
		std::cout << "----------------------------------\n";
		if (created == false)
		{
			std::cout << "*Make sure to Create Sudoku first*\n\n";
		}
		//MAIN MENU
		std::cout << "1:Generate Sudoku\n";
		std::cout << "2:Input Sudoku\n";
		std::cout << "3:Check Sudoku\n";
		std::cout << "4:Solve it yourself\n";
		std::cout << "5:Computer Solve\n";
		std::cout << "6:Save your Sudoku\n";
		std::cout << "7:Exit\n";
		std::cout << " :";
	std::cin >> input;
	//Switch for Option Inputs
	switch (input) {
	case 1: 
		system("cls");
		sudo.fillBoard();
		int input;
		std::cout << "Input your Difficulty\n" << endl;
		std::cout << " -1 to exit \n\n";
		std::cout << "1 - Easy - 2 Hard) \n\n";
		std::cout << "------------------\n";
		std::cout << "::";
		cin >> input;
		sudo.degrade(input);
		c2 = true;
		goto start;
		break;
	case 2:
		int inp;
		system("cls");
		std::cout << "Input Sudoku\n-------------\n";
		std::cout << "\n";
		std::cout << "Enter your option\n";
		std::cout << "1:Keep your Current Sudoku\n";
		std::cout << "2:Create a new one\n";
		std::cout << "3:Import a Sudoku from a file\n";
		std::cout << " :";
		cin >> inp; 
		if (inp == 2){
			sudo.setSize(9);
			sudo.createboard(9);
			sudo.inputSudoku();
			c3 = true;
			goto start;
			break;
		}
		else if (inp == 1)
		{
			sudo.inputSudoku();
			c3 = true;
			goto start;
			break;
		}
		else if (inp == 3)
		{
			system("cls");
			std::cout << "Import Sudoku\n-------------\n";
			std::cout << "\n";
			std::cout << "Enter your option\n";
			std::cout << "1:Import your own\n";
			std::cout << "2:Import a prebuilt\n";
			std::cout << " :";
			cin >> inp;
			if (inp == 1)
			{
				sudo.importSudoku();
			}
			else
			{
				system("cls");
				std::cout << "Prebuilt Sudoku\n-------------\n";
				std::cout << "\n";
				std::cout << "Enter your option\n";
				std::cout << "1:Easy\n";
				std::cout << "2:Meduim\n";
				std::cout << "3:Hard\n";
				std::cout << " :";
				cin >> inp;
				sudo.importSudoku(inp);
			}
			c3 = true;
			goto start;
			break;
		}
		else{
			c3 = true;
			goto start;
			break;
		}		
	case 3:
		system("cls");
		std::cout << "Check Sudoku\n-------------\n";
		std::cout << "\n";
		std::cout << "Enter your option\n";
		std::cout << "1:Check if playable\n";
		std::cout << "2:Check if solved\n";
		std::cout << " :";
		cin >> inp;
		if (inp == 1){
			sudo.checkPlayable();
			c5 = true;
			goto start;
			break;
		}
		else if (inp == 2)
		{
			sudo.checkSudoku();
			c4 = true;
			goto start;
			break;
		}
		else{
			goto start;
			break;
		}		
	case 4:
		system("cls");
		std::cout << "Solve your Sudoku\n-------------\n";
		std::cout << "\n";
		sudo.guessSudoku();
		goto start;
		break;
	case 5:
		system("cls");
		std::cout << "Computer Solve\n-------------\n";
		std::cout << "\n";
		if (sudo.checkPlayable())
		{
			sudo.solveSudoku();
		}
		else
		{
			std::cout << "Not Solvable\n";
			system("pause");
			goto start;
			break;
		}
		sudo.displayBoard();
		system("pause");
		goto start;
		break;
	case 6:
		system("cls");
		std::cout << "Save your Sudoku\n-------------\n";
		std::cout << "\n";
		sudo.exportSudoku();
		saved = true;
		goto start;
		break;
	case 7:
		system("cls");
		std::cout << "Exit\n-------------\n";
		std::cout << "Are you sure you want to exit\n";
		std::cout << "1:Yes\n";
		std::cout << "2:No\n";
		std::cout << "::";
		cin >> inp; 
		//Exit Loop
		if (inp == 1 && saved == false)
		{
			system("cls");
			std::cout << "Do you want to save before you exit?\n";
			std::cout << "1:Yes\n";
			std::cout << "2:No\n";
			std::cout << "::";
			cin >> inp;
			if (inp == 2)
			{
				sudo.~Sudoku();
				exit(EXIT_FAILURE);
				
			}
			if (inp == 1)
			{
				sudo.exportSudoku();
				sudo.~Sudoku();
				exit(EXIT_FAILURE);
			}
		}
		if (inp == 1 && saved == true)
		{
			sudo.~Sudoku();
			exit(EXIT_FAILURE);
		}
		goto start;
		break;
	default:
		system("cls");
		goto start;
	}

}
//-----------------------------------------
//Setter|Getter
void Sudoku::setSize(int n)//Sets Size
{
	size = n;
	delim = sqrt(size);
} 
void Sudoku::setStatus(bool b)//Sets Status
{
	status = b;
} 
void Sudoku::integrateCount() //Integrates Count
{
	count++;
}
int Sudoku::getSize() //Gets Size
{
	return size;
}
int Sudoku::getCount() //Gets Count
{
	return count;
}
bool Sudoku::getStatus() //Gets Status
{
	return status;
}
bool Sudoku::getPlayable() //Gets Playable
{
	return playable;
}
//-----------------------------------------
//Create Board
void Sudoku::createboard(int k) //Creates a board for KxK
{ 
	srand(time(NULL)); //Sets new Random Seed
	arr = new int *[k];
	temparr = new int*[k];
	// memory allocated for  elements of each column.  
	for (int i = 0; i < k; i++) 
	{
		arr[i] = new int[k];
		temparr[i] = new int[k];
	}
	//Makes 9 by 9
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{	
			temparr[i][j] = 0;
			arr[i][j] = 0;
		}
	}
}
//-----------------------------------------
//Show Board
void Sudoku::displayBoard(int row,int column) //Displays Board for Input Function - X where current Val is
{
	
	//Diplays the Sudoku
	//All of this is just special formatting for how it displays
	for (int i = 0; i < size; i++)
	{
		if (i % 3 == 0){
			for (int k = 0; k <= ((size/delim)*8); k++)
			{
				std::cout << "-";
			}
		}
		std::cout << "\n";
		for (int j = 0; j < size; j++)
		{
			if (j % 3 == 0)
			{
				std::cout << "| ";
			}
			if (i == row && j == column)
			{
				std::cout << "X ";
			}
			else
			{
				std::cout << arr[i][j] << " ";
			}
				
		}
		std::cout << "|";
		std::cout << "\n";
	}
	for (int k = 0; k <= ((size / delim) * 8); k++)
	{
		std::cout << "-";
	}
	std::cout << "\n";
}
void Sudoku::displayBoard() //Displays Board
{

	//Printer
	// All of this is just special formatting for how it displays
	std::cout << "  ";
	for (int k = 0; k < size; k++)
	{
		if (k % 3 == 0 && k != 0)
		{
			std::cout << " ";
			std::cout << " ";
		}
		std::cout << " ";		
		std::cout << k;
		
	}
	std::cout << "\n ";

	for (int i = 0; i < size; i++)
	{
		if (i % 3 == 0)
		{
			for (int k = 0; k <= ((size / delim) * 8); k++)
			{
				std::cout << "-";
			}
		}
		std::cout << "\n";
		std::cout << i;
		for (int j = 0; j < size; j++)
		{
			if (j % 3 == 0)
			{
				std::cout << "| ";
			}
			std::cout << arr[i][j] << " ";

		}
		std::cout << "|";
		std::cout << "\n ";
	}
	for (int k = 0; k <= ((size / delim) * 8); k++)
	{
		std::cout << "-";
	}
	std::cout << "\n ";
}
//-----------------------------------------
//Fill Board
void Sudoku::fillBoard()  //Fills the Board with a working Sudoku then generates a unique Sudoku
{
	int numA1, numA2, numB1, numB2, numC1, numC2, numE1, numE2;
	int i;
	std::ifstream is("startingboard.txt");     // open file

	//Fills arr with values from the sudoku file
	char c;
	for (int m = 0; m < 9; m++){
		for (int n = 0; n < 9; n++)
		{
			is.get(c);
			i = c - '0';
			arr[m][n] = i;
		}
	}
	is.close();                // close file
	srand(time(NULL));
	// pick four number pairs to be swapped
	do {		
		numA1 = ((rand() % 8) + 1);
		numA2 = ((rand() % 8) + 1);
	} while (numA1 == 0 || numA2 == 0 || numA1 == numA2);

	do {		
		numB1 = ((rand() % 8) + 1);
		numB2 = ((rand() % 8) + 1);
	} while (numB1 == numA1 || numB1 == numA2 || numB2 == numA1 || numB2 == numA2);

	do {
		numC1 = ((rand() % 8) + 1);
		numC2 = ((rand() % 8) + 1);
	} while (numC1 == numC2 || numC1 == numB1 || numC1 == numB2 || numC2 == numB1 || numC2 == numB2 || numC1 == numA1 || numC1 == numA2 || numC2 == numA1 || numC2 == numA2);

	do {
		numE1 =((rand() % 8) + 1);
		numE2 = ((rand() % 8) + 1);
	} while (numE1 == numE2 || numE1 == numC1 || numE1 == numC2 || numE2 == numC1 || numE2 == numC2 || numE1 == numB1 || numE1 == numB2 || numE2 == numB1 || numE2 == numB2 || numE1 == numA1 || numE1 == numA2 || numE2 == numA1 ||numE2 == numA2);
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (arr[i][j] == numA1){
				arr[i][j] = numA2;
			}
			else if (arr[i][j] == numA2){
				arr[i][j] = numA1;
			}
		}
	}
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (arr[i][j] == numB1){
				arr[i][j] = numB2;
			}
			else if (arr[i][j] == numB2){
				arr[i][j] = numB1;
			}
		}
	}
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (arr[i][j] == numC1){
				arr[i][j] = numC2;
			}
			else if (arr[i][j] == numC2){
				arr[i][j] = numC1;
			}
		}
	}
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (arr[i][j] == numE1){
				arr[i][j] = numE2;
			}
			else if (arr[i][j] == numE2){
				arr[i][j] = numE1;
			}
		}
	}
	//Refills if the sudoku isn't working
	if (checkSudoku() == false)
	{
		std::cout << "Not working" << endl;
		system("pause");
		fillBoard();
	}
	


}	
void Sudoku::degrade(int option) //Degrades the Sudoku until it is playable
{
	srand(time(NULL));
	int i = 0;
	int x = 0;
	int temp;
	switch (option)
	{
	case 0:
	{
			  do
			  {
				  rando = (rand() % 9);
				  int rando1 = (rand() % 9);
				  if (arr[rando][rando1] != 0)
				  {
					  temp = arr[rando][rando1];
					  arr[rando][rando1] = 0;
					  if (checkPlayable())
						  i++;
					  else
						  arr[rando][rando1] = temp;
				  }
				  x++;
			  } while (i < 10 || x < 120);
			  break;
	}
	case 1:
	{
			  do
			  {
				  rando = (rand() % 9);
				  int rando1 = (rand() % 9);
				  if (arr[rando][rando1] != 0)
				  {
					  temp = arr[rando][rando1];
					  arr[rando][rando1] = 0;
					  if (checkPlayable())
						  i++;
					  else
						  arr[rando][rando1] = temp;
				  }
				  x++;
			  } while (i < 45 || x < 120);
			  break;
	}
	case 2:
	{
			  do
			  {
				  rando = (rand() % 9);
				  int rando1 = (rand() % 9);
				  if (arr[rando][rando1] != 0)
				  {
					  temp = arr[rando][rando1];
					  arr[rando][rando1] = 0;
					  if (checkPlayable())
						  i++;
					  else
						  arr[rando][rando1] = temp;
				  }
				  x++;
			  } while (i < 52 || x < 120);
			  break;
	}
	default:
	{
	  break;
	}
	}
}
//-----------------------------------------
//Generate Board
bool Sudoku::checkForInRow(int row, int num)  //Checks for Num
{
	for (int col = 0; col < 9; col++){
		if (arr[row][col] == num){
			return true;
		}
	}	
	return false; 
}
bool Sudoku::checkForInColumn(int column, int num)  //Checks column for num
{
	for (int row = 0; row < 9; row++){
		if (arr[row][column] == num){
			return true;
		}
	}
	return false;
}
bool Sudoku::checkForInBox(int row, int column, int n) //Checks Box for Num
{
	
	for (int i = row; i < (row + delim); i++)
	{
		for (int j = column; j < (column+delim); j++)
		{
			if (arr[i][j] == n){
				return true;
			}
		}
	}
	return false;

	
}
bool Sudoku::tempCheckForInRow(int row, int n)
{
	for (int j = 0; j < size; j++)
	{
		if (temparr[row][j] == n)
		{
			temp = j;
			temp1 = row;
			return true;
		}
	}

	return false;
}
bool Sudoku::tempCheckForInColumn(int column, int n)
{
	for (int j = 0; j < size; j++)
	{
		if (temparr[j][column] == n)
		{
			temp = column;
			temp1 = j;
			return true;
		}
	}
	return false;
}
bool Sudoku::tempCheckForInBox(int row, int column, int n)
{

	for (int i = row; i < (row + delim); i++)
	{
		for (int j = column; j < (column + delim); j++)
		{
			if (temparr[i][j] == n){
				temp = i;
				temp1 = j;
				return true;
			}
		}
	}
	return false;
}
bool Sudoku::checkPlayable() //Checks if Sudoku is playable
{
	int tempcheck = 0;
	//Checking numbers 1-9
	for (int i = 1; i <= size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{

				//Sets the temp array to the num for solving

				if (arr[j][k] == i)
				{
					//Rows
					for (int n = 0; n < size; n++)
					{
						temparr[n][k] = 10;
					}
					//Column
					for (int n = 0; n < size; n++)
					{
						temparr[j][n] = 10;
					}
					//Box
					for (int n = ((j / 3) * 3); n < (((j / 3) * 3) + 3); n++)
					{
						for (int m = ((k / 3) * 3); m < (((k / 3) * 3) + 3); m++)
						{
							temparr[n][m] = 10;
						}
					}
					//Checks where a solution might be
					//Rows Check
					tempcheck = 0;
					string c = "";
					int g = 0;
					for (int n = 0; n < size; n++)
					{
						if (tempCheckForInRow(n, 0) == true)
						{
							g = n;
							tempcheck++;
						}
					}
					if (tempcheck == 1)
					{
						playable = true;
						return true;
					}
					tempcheck = 0;
					//Column Check
					for (int n = 0; n < size; n++)
					{
						if (tempCheckForInColumn(n, 0) == true)
						{
							g = n;
							tempcheck++;
						}
					}
					if (tempcheck == 1)
					{
						playable = true;
						return true;
					}
					tempcheck = 0;
					//Box
					int h = 0;
					for (int n = 0; n < size; n = n + delim)
					{
						for (int m = 0; m < size; m = m + delim)
						{
							if (tempCheckForInBox(n, m, 0) == true)
							{
								g = n;
								h = m;
								tempcheck++;
							}
						}
					}
					if (tempcheck == 1)
					{
						playable = true;
						return true;
					}

				}//end-if

			}
		}
	}
	playable = false;
	return false;	
}
bool Sudoku::checkSudoku() //Checks if Sudoku is complete
{
	bool overall = false; 
	count = 0;	
	int tempcount = 0;
	int totalcheck = 0;

	//1st Check Box
	
	for (int i = 0; i < size; i = i + delim)
	{
		for (int n = 0; n < size; n = n + delim)
		{
			for (int j = 1; j <= size; j++)
			{
				tempcount++;
				if (checkForInBox(i, n, j) == true)
				{
					integrateCount();
				}
			}
		}
	}
	

	//2nd Check Row

	for (int n = 0; n < size; n++)
	{
		for (int j = 1; j <= size; j++)
		{
			tempcount++;
			if (checkForInRow(n, j) == true)
			{
				integrateCount();
			}
		}
	}
	

	//3rd Check Column

	for (int n = 0; n < size; n++)
	{
		for (int j = 1; j <= size; j++)
		{
			tempcount++;
			if (checkForInColumn(n, j) == true)
			{
				integrateCount();
			}
		}
	}
	if (count == 243)
	{
		setStatus(true);
		return true;
	}
	else
	{
		setStatus(false);
		return false;
	}
}
bool Sudoku::isWorking(int row, int col, int num) //Checks if the Sudoku is Working
{
	return !checkForInRow(row, num) && !checkForInColumn(col, num) && !UsedInBox(row - row % 3, col - col % 3, num);
}
bool Sudoku::UsedInBox(int boxRow, int boxCol, int num) //Checks if the Num was Used in the Box - ALT
{
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			if (arr[row + boxRow][col + boxCol] == num){
				return true;
			}
		}
	}
	return false;
}
bool Sudoku::checkNotFull(int &row, int &col)  //Checks if the Sudoku isn't full
{
	for (row = 0; row < 9; row++){
		for (col = 0; col < 9; col++){
			if (arr[row][col] == UNASSIGNED){
				return true;
			}
		}
	}
	return false;
}
//-----------------------------------------
//Input a Sudoku
void Sudoku::inputSudoku() // Lets the User input a Sudoku
{
	int input;
	std::cout << "Input your Sudoku\n" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
		top:
			system("cls");
			std::cout << " -1 to exit \n\n";
			displayBoard(i,j);
			std::cout << "------------------\n";
			std::cout << "Input: " << i << "," << j << " \n";
			std::cout << "::";
			cin >> input;
			if (input == -1)
			{
				break;
			}
			else if (input<=9 && input>=0)
			{
				arr[i][j] = input;
			}
			else
			{
				cout << "Not in Nums Range\n";
				system("pause");
				goto top;
			}
			
		}
		if (input == -1)
		{
			break;
		}
	}
}
//-----------------------------------------
//Input Values into the Sudoku
void Sudoku::guessSudoku()  // Lets the User input values
{
	int x = 0;
	int y = 0;
	int z = 0;
	std::cout << "Solve your Sudoku\n" << endl;
	while (x != -1 && y != -1 && z != -1)
	{
			system("cls");
			std::cout << " -1 to exit \n\n";
			displayBoard();
			std::cout << "------------------\n";
			std::cout << "Rows:0-8" << endl;
			std::cout << "Columns:0-8" << endl;
			std::cout << "Input: (x,y)" << endl; 
			std::cout << "";
			cin >> x;
			if (x == -1)
			{
				break;
			}
			std::cout << ",\n";
			cin >> y;
			if (y == -1)
			{
				break;
			}
			std::cout << " = ";
			cin >> z;	
			if (z == -1)
			{
				break;
			}
			if (z<=9 && z>=0)
			{
				arr[y][x] = z;
			}
			else
			{
				cout << "Not in Nums Range\n";
				system("pause");
				guessSudoku();
			}

	}
}
//-----------------------------------------
//Solve Sudoku
bool Sudoku::solveSudoku() //Solves the Sudoku for the User
{
	int row = 0;
	int col =0;

	// If there is no unassigned location, we are done
	if (checkNotFull( row, col) == false)
		return true; // success!
	// consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		// if looks promising
		if (isWorking(row, col, num))
		{
			// make tentative assignment
			arr[row][col] = num;

			// return, if success, yay!
			if (solveSudoku())
				return true;

			// failure, unmake & try again
			arr[row][col] = UNASSIGNED;
		}
	}
	return false;
}
//File IO
void Sudoku::importSudoku()  //Lets the user import a Sudoku
{
	char str[256];
	int i;
	std::cout << "Enter the name of an existing text file (Don't forget the .txt) : ";
	std::cin >> str;    // get c-string

	std::ifstream is(str);     // open file

	char c;
	for (int m = 0; m < 9; m++){
		for (int n = 0; n < 9; n++)
		{
				is.get(c);
				i = c-'0';
				arr[m][n] = i;			
		}
	}
	is.close();                // close file
	
	

	
}
void Sudoku::importSudoku(int option)  //Imports a Sudoku of various difficulty to the user
{
	string str;
	int i;
	srand(time(NULL));
	rando = (rand() % 5);
	switch (option)
	{
	case 1:
		rando = rando;
		break;
	case 2:
		rando = rando + 5;
		break;
	case 3:
		rando = rando + 10;
		break;
	}
	str = "Sudoku" + to_string(rando) + ".txt.";
	std::ifstream is(str.c_str());     // open file

	char c;
	for (int m = 0; m < 9; m++){
		for (int n = 0; n < 9; n++)
		{
			is.get(c);
			i = c - '0';
			arr[m][n] = i;
		}
	}
	is.close();                // close file




}
void Sudoku::exportSudoku() //Saves the Sudoku
{
	char x[256];
	cout << "Enter a filename (Don't forget .txt)\n";
	cout << ":: ";
	cin >> x;
	ofstream myfile(x);
	if (myfile.is_open())
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				myfile << arr[i][j];
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	
}