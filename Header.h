#pragma once

// -_-_-_-_-_-_-_-_-_-_-_-_-_- SUBMITTED BY _-_-_-_-_-_-_-_-_ MUHAMMAD LAIQ ALI ( 20L-1310 ) -_-_-_-__-_____

// -_-_-_-_-_-_-_-_-_-_-_-_-_- SUBMITTED TO _-_-_-_-_-_-_-_-_ TAZEEM HAIDER -_-_-_-__-_____


#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include<string>
#include<cstdlib>

using namespace std;


//   -_-_-_-_-_-_-_-_-_-_-_-_-_- QUESTION NUMBER 1 _-_-_-_-_-_-_-_-_ FUNCTIONS -_-_-_-__-_____


class GRID_MAKER
{
public:	
	GRID_MAKER();		// CONSTRUCTOR
	char char_array[50];	
	int Random_Row;		
	int Random_Column;		
	char Puzzle_Grid[100][100];	
};

class Grid_Work: public GRID_MAKER
{
public:

	void PrintGrid(ofstream & fout,int,int);   
	void Make_complete_puzzle(string* string_array, int, int, int);	
	void Filling_Remaining_space(int &rows, int &cols);	
	void INPUT_COMPLETE_GRID();  
	
	// PLACEMENT OF WORDS IN GRID BY CHECKING 8 CONDITIONS

	bool CHECK_LEFT_TO_RIGHT(int , int ,int , int , int  ,char char_array[]);
	bool CHECK_RIGHT_TO_LEFT(int , int ,int , int , int ,char char_array[]);
	bool CHECK_BOTTOM_TO_TOP(int , int ,int , int , int ,char char_array[]);
	bool CHECK_TOP_TO_BOTTOM(int , int ,int , int , int  ,char char_array[]);
	bool CHECK_BOTTOMLEFT_TO_TOPRIGHT(int , int ,int , int , int  ,char char_array[]);
	bool CHECK_BOTTOMRIGHT_TO_TOPLEFT(int , int ,int , int , int  ,char char_array[]);
	bool CHECK_TOPLEFT_TO_BOTTOMRIGHT(int , int ,int , int , int  ,char char_array[]);
	bool CHECK_TOPRIGHT_TO_BOTTOMLEFT(int , int ,int , int , int  ,char char_array[]);
};

GRID_MAKER::GRID_MAKER()
{
	//Constructor to initialize all the variables and Grid
	Random_Row = 0;
	Random_Column = 0;	
	char_array[49] = '\0';
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			Puzzle_Grid[i][j] = '\0';
		}			
	}
}

void Grid_Work::INPUT_COMPLETE_GRID()     //input characters from input file
{

	//Takes words in temp buffer and then according to their strlen , passes to charlength , checks the largest word and length.
	//Also converts from char** to string* and returnns string.
	ifstream fin;
	ofstream fout;
	string file_name;
	cout << "ENTER NAME OF FILE WHERE YOU WANT TO INPUT NAMES (i.e. input.txt) = ";
	cin >> file_name;
	fin.open(file_name);
		
	int total_words = 0, rows = 0, columns = 0;

	cout << "ENTER NUMBERS OF WORDS PRESENT IN FILE = ";
	cin >> total_words;

	while(total_words < 1)
	{
		cout << "ENTER NUMBER OF WORDS GREATER THAN 1. THANKS............";
		cin >> total_words;
	}
		
	cout << "ENTER NUMBER OF ROWS YOU WANT IN YOUR GRID = ";
	cin >> rows;

	while( rows < 2)
	{
		cout << "ENTER NUMBER OF ROWS YOU WANT IN YOUR GRID ( AGAIN. DUE TO WRONG INPUT ) = ";
		cin >> rows;
	}
		
	cout << "ENTER NUMBERS OF COLUMNS PRESENT IN FILE = ";
	cin >> columns;
	
	while( columns < 2)
	{
		cout << "ENTER NUMBER OF COLUMNS YOU WANT IN YOUR GRID ( AGAIN. DUE TO WRONG INPUT ) = ";
		cin >> columns;
	}

	cout << "ENTER NAME YOUR FILE NAME WHERE YOU WANT TO STORE THE OUTPUT GRID (i.e. OUTPUT.TXT)  = ";
	cin >> file_name;
	fout.open(file_name);

	char TEMPORARY_Buffer_ARRAY[100][80] = {};

	int char_length = 0;
	int max_length = 0;
	if (fin.is_open())        //storing in temporaray 2d array
	{
		for(int k = 0; k < total_words; k++)
		{
			fin.getline( TEMPORARY_Buffer_ARRAY[k], 80);
			char_length = strlen(TEMPORARY_Buffer_ARRAY[k]);
			
			if (char_length > max_length)
			{
				max_length = char_length;
			}
		}
		fin.close();
	}
	else
	{
		cout << endl << "COULD NOT FIND THE FILE" << endl;
	}

	if(max_length > rows && max_length > columns)
	{
		cout << "SORRY INPUT VALUES like TOTAL ROWS AND COLUMNS ARE  SMALLER THAN MAXIMUM LENGTH OF THE INPUT WORD.........." << endl;
        return;
	}
	char** Primary_array = new char* [total_words];    //storing in dynamic array
	char** temporay_helper = Primary_array;
	for (int i = 0; i < total_words; i++)
	{
		int length_of_row = strlen(TEMPORARY_Buffer_ARRAY[i]);

		Primary_array[i] = new char[length_of_row + 1];
		int j = 0;

		for (char* temporay_Source = TEMPORARY_Buffer_ARRAY[i]; *temporay_Source != '\0'; temporay_Source++, j++)
		{
			temporay_helper[i][j] = *temporay_Source;
		}
		temporay_helper[i][j] = '\0';
	}

	string* GRID_MAKE = new string[total_words];  //memory allocation on heap

	for (int i = 0; i < total_words; i++)
	{
		GRID_MAKE[i] = Primary_array[i];
	}
	if(GRID_MAKE != 0)
	{
		Make_complete_puzzle(GRID_MAKE, total_words, rows, columns);		// call for placemen function
		PrintGrid(fout, rows, columns);	//Call for output function	
		cout << "CONGRATULATION YOUR GRID IS NOW SAVED IN YOUR SPECIFIED FILE ............." ;
	}
	
	if(GRID_MAKE)
		delete[] GRID_MAKE; //deallocation

	fin.close();
	fout.close();
	cout << endl << endl;

}



void Grid_Work::Filling_Remaining_space(int &rows, int &cols)
{
	//This function fills the remaining spaces with random characters
	for (int i = 0; i < rows; i++)
	{
		for (int k = 0; k < cols; k++)
		{
			if (Puzzle_Grid[i][k] == '\0')
			{
				Puzzle_Grid[i][k] = rand() % 26 + 65;
			}			
		}		
	}	
}

// THIS FUNCTION CHECK_LEFT_TO_RIGHT
bool Grid_Work:: CHECK_LEFT_TO_RIGHT(int string_length, int rows,int cols, int y, int x, char array[])
{	
		if (x + string_length > cols)
			return false;
	
		for (int i = 0; i < string_length; i++) 
			if ( Puzzle_Grid[y][x + i] != '\0' && Puzzle_Grid[y][x + i] != array[i])
				       return false;
				
		for (int i = 0; i < string_length; i++)
			Puzzle_Grid[y][x + i] = array[i];
		
	return true;		
}

// THIS FUNCTION CHECK_RIGHT_TO_LEFT

bool Grid_Work:: CHECK_RIGHT_TO_LEFT(int string_length, int rows,int cols, int y, int x, char array[])
{	
	if (x - string_length + 1 < 0)
		return false;
	
	for (int i = 0; i < string_length; i++)
		if ( Puzzle_Grid[y][x - i] != '\0' && Puzzle_Grid[y][x - i] != array[i])
			return false;
	
	for (int i = 0; i < string_length; i++)
		Puzzle_Grid[y][x - i] = array[i];	
		
	return true;				
}

// THIS FUNCTION CHECK_BOTTOM_TO_TOP
bool Grid_Work:: CHECK_BOTTOM_TO_TOP(int string_length, int rows,int cols, int y, int x, char array[])
{
	if (y + string_length > rows)
			return false;
	
	for (int i = 0; i < string_length; i++)
		if ( Puzzle_Grid[y + i][x] != '\0' && Puzzle_Grid[y + i][x] != array[i])
			return false;
	
	for (int i = 0; i < string_length; i++)
		 Puzzle_Grid[y + i][x] = array[i];

	return true;			
}

// THIS FUNCTION CHECK_TOP_TO_BOTTOM
bool Grid_Work::CHECK_TOP_TO_BOTTOM(int string_length, int rows,int cols, int y, int x, char array[])
{
	if (y - string_length + 1 < 0)
			return false;
	
	for (int i = 0; i < string_length; i++)
		if (Puzzle_Grid[y - i][x] != '\0' && Puzzle_Grid[y - i][x] != array[i])
			       return false;
				
	for (int i = 0; i < string_length; i++)
		Puzzle_Grid[y - i][x] = array[i];

	return true;			
}

// THIS FUNCTION CHECK_BOTTOMLEFT_TO_TOPRIGHT
bool Grid_Work::CHECK_BOTTOMLEFT_TO_TOPRIGHT(int string_length, int rows,int cols, int y, int x, char array[])	
{
	if (y - string_length + 1 < 0 || x + string_length > cols)
			return false;
	
	for (int i = 0; i < string_length; i++)
		if ( Puzzle_Grid[y - i][x + i] != '\0' && Puzzle_Grid[y - i][x + i] != array[i])
			return false;
				
	for (int i = 0; i < string_length; i++)
		      Puzzle_Grid[y - i][x + i] = array[i];

	return true;	
}

// THIS FUNCTION CHECK_BOTTOMRIGHT_TO_TOPLEFT

bool Grid_Work::CHECK_BOTTOMRIGHT_TO_TOPLEFT(int string_length, int rows,int cols, int y, int x, char array[])	
{
	if (y - string_length + 1 < 0 || x - string_length + 1 < 0)
			return false;
	
	for (int i = 0; i < string_length; i++)
		if ( Puzzle_Grid[y - i][x - i] != '\0' && Puzzle_Grid[y - i][x - i] != array[i])
			return false;
				
	for (int i = 0; i < string_length; i++)
		Puzzle_Grid[y - i][x - i] = array[i];

	return true;
}

// THIS FUNCTION CHECK_TOPLEFT_TO_BOTTOMRIGHT

bool Grid_Work::CHECK_TOPLEFT_TO_BOTTOMRIGHT(int string_length, int rows,int cols, int y, int x, char array[])	
{	
	if (y + string_length > rows || x + string_length > cols)
		return false;
	
	for (int i = 0; i < string_length; i++)
		if ( Puzzle_Grid[y + i][x + i] != '\0' && Puzzle_Grid[y + i][x + i] != array[i])
			   return false;
	
	for (int i = 0; i < string_length; i++)
		       Puzzle_Grid[y + i][x + i] = array[i];

	return true;			
}

// THIS FUNCTION CHECK_TOPRIGHT_TO_BOTTOMLEFT

bool Grid_Work::CHECK_TOPRIGHT_TO_BOTTOMLEFT(int string_length, int rows,int cols, int y, int x, char array[])	
{
	if (y + string_length > rows || x - string_length + 1 < 0)
			return false;
	
	for (int i = 0; i < string_length; i++)
		if (Puzzle_Grid[y + i][x - i] != '\0' && Puzzle_Grid[y + i][x - i] != array[i])
			return false;
	
	for (int i = 0; i < string_length; i++)
		    Puzzle_Grid[y + i][x - i] = array[i];

	return true;			
}

// THIS FUNCTION MAKES COMPLETE GRID PUZZLE
		
void Grid_Work ::Make_complete_puzzle(string* string_array, int number_of_words, int Rows,int Cols)
{
	int count = 0, X, Y, temporary_arrangement , wordLength = 0;

	if (string_array == NULL || Puzzle_Grid == NULL)
		return;
	
	for (int i = 0; i < number_of_words;)
	{
		X = rand() % Cols;
		Y = rand() % Rows;
		temporary_arrangement = rand() % 8;
		wordLength = string_array[i].length();
		strcpy_s(char_array, string_array[i].c_str());
		
		if (temporary_arrangement  == 0)
		{
			if ( CHECK_LEFT_TO_RIGHT(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement  == 1) 
		{
			if ( CHECK_RIGHT_TO_LEFT(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement  == 2)
		{
			if( CHECK_BOTTOM_TO_TOP(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement == 3) 
		{
			if (CHECK_TOP_TO_BOTTOM(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement == 4)
		{
			if (CHECK_BOTTOMLEFT_TO_TOPRIGHT(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement  == 5) 
		{
			if (CHECK_BOTTOMRIGHT_TO_TOPLEFT(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement == 6)
		{
			if (CHECK_TOPLEFT_TO_BOTTOMRIGHT(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		else if (temporary_arrangement == 7)
		{
			if (CHECK_TOPRIGHT_TO_BOTTOMLEFT(wordLength, Rows, Cols, Y, X, char_array)) {
				count = 0;
				i++;
			}
			else count++;
		}

		if (count == (100 * Rows *Cols)) {
			cout << endl << string_array[i] << " WAS SKIPPED BECAUSE THEY DID NOT FIT IN THE LIST";
			count = 0;
			i++;
		}
	}

	Filling_Remaining_space(Rows, Cols);
	
}

//THIS FUNCTION PRINT THE GRID IN FILE

void Grid_Work::PrintGrid(ofstream &out,int Rows,int Columns)
{
	//Simply output the Grid
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (Puzzle_Grid[i][j] >= 97 && Puzzle_Grid[i][j] <= 122)
			{
				Puzzle_Grid[i][j] = Puzzle_Grid[i][j] - 32;
			}
			out << Puzzle_Grid[i][j] << " ";
		}
		out << '\n';
	}
}


//   -_-_-_-_-_-_-_-_-_-_-_-_-_- QUESTION NUMBER 2 _-_-_-_-_-_-_-_-_ FUNCTIONS -_-_-_-__-_____


// THIS FUNCTION DEALLOCATED DOUBLE POINTER MATRIX
void DeallocateMatrix(char** string_array, int& size) 
{
	for (int i = 0; i < size; i++)
		if (string_array[i] != NULL)
			delete[] string_array[i];
	
	if(string_array != NULL)
		delete[] string_array;
}

// THIS FUNCTION RETURNS STRING LENGTH
int String_Length(char* string) {
	int length = 0, counter = 0;
	for (; string[length] != '\0'; length++, counter++)
		if (string[length] == ' ') counter--;

	return counter;
}

// THIS FUNCTION CONVERTS SMALL CHARACTER TO LARGE
char CAPITALIZATION(char character) {
	if (character >= 'a' && character <= 'z')
		return character - 32;

	return character;
}

//THIS FUNCTION RETURN COPY OF STRINGS WITH SPACE
char* string_copy(char* string)
{
	int counter = 0;
	int length = String_Length(string);
	char* New_String = new char[length + 1];

	for (int i = 0; string[i] != '\0'; i++)
		if (string[i] != ' ')
			New_String[counter++] = CAPITALIZATION(string[i]);

	New_String[length] = '\0';

	return New_String;
}

//THIS FUNCTION TAKES INPUT FROM FILE
char* Input_String(ifstream & fin)
{
	char* temporary_array = new char[80];
	fin.getline(temporary_array, 80, '\n');

	char* resultant_array = string_copy(temporary_array);

	delete[] temporary_array;
	return resultant_array;
}

//THIS FUNCTION TAKES INPUT FROM USERS
char* Input_String()
{
	char* temporary_array = new char[80];
	cin.getline(temporary_array, 80, '\n');

	char* resultant_array = string_copy(temporary_array);

	delete[] temporary_array;
	return resultant_array;
}

//THIS FUNCTION GETS GRID FROM FILE
char** Get_Grid_From_File(ifstream& fin, int& size, string grid_file) 
{
	size = 0;
	char* resultant_array;
	fin.open(grid_file);
	
	if (!fin) 
	{
		cout << "\nSORRY! FILE IS NOT OPENED....... TRY AGAIN .......\n";
		return 0;
	}

	while (!fin.eof()) 
	{
		resultant_array = Input_String(fin);
		delete[] resultant_array;
		size++;
	}

	fin.close();
	fin.open(grid_file);

	char** new_grid = new char* [size];
	for (int i = 0; i < size; i++)
		       new_grid[i] = Input_String(fin);

	fin.close();

	return new_grid;
}

// THIS FUNCTION GETS WORDS FROM ARRAY
char** Get_Words_From_Array(int& number_of_words)
{
	cout << "ENTER NUMBER OF WORDS (i.e. NUMBER > 0) = ";
	cin >> number_of_words;
	while (number_of_words < 1) {
		cout << "SORRY!! YOU ENTER NUMBER SMALLER THAN ONE....... PLEASE TRY AGAIN ........";
		cin >> number_of_words;
	}

	cin.ignore();
	char** new_grid = new char* [number_of_words];
	for (int i = 0; i < number_of_words; i++) 
	{
		cout << "ENTER ANY WORD: ";
		new_grid[i] = Input_String();
	}

	return new_grid;
}

//THIS FUNCTION GETS WORDS FROM FILE
char** Get_Words_From_Array(ifstream& fin, int& number_of_words, string string_file) 
{
	number_of_words = 0;
	char* temporary_array;
	fin.open(string_file);

	if (!fin) 
	{
		cout << "\nError: file not found, sending NULL\n";
		return NULL;
	}

	while (!fin.eof()) 
	{
		temporary_array = Input_String(fin);
		delete[] temporary_array;
		number_of_words++;
	}

	fin.close();
	fin.open(string_file);

	char** new_grid = new char* [number_of_words];
	for (int i = 0; i < number_of_words; i++)
		    new_grid[i] = Input_String(fin);

	fin.close();

	return new_grid;
}

// THIS FUNCTION Check_Left_To_Right
bool Check_Left_To_Right(char** word_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	for (int i = 0; i < length; i++)
		if (word_grid[Y][X + i] != string[i])
			   return false;

	return true;
}

// THIS FUNCTION Check_Right_To_Left
bool Check_Right_To_Left(char** new_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	if (X - length + 1 < 0)
		return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y][X - i] != string[i])
			return false;

	return true;
}

// THIS FUNCTION Check_Top_To_Bottom
bool Check_Top_To_Bottom(char** new_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	if (Y + length - 1 > size)
		return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y + i][X] != string[i])
			return false;

	return true;
}

// THIS FUNCTION Check_Bottom_To_Top
bool Check_Bottom_To_Top(char** new_grid, const int& size, char* string, const int& length, int Y, int X)
{
	if (Y - length + 1 < 0)
		return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y - i][X] != string[i])
			return false;

	return true;
}

// THIS FUNCTION Check_TopLeft_To_BottomRight
bool Check_TopLeft_To_BottomRight(char** new_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	if (Y + length - 1 > size)
		    return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y + i][X + i] != string[i])
			return false;

	return true;
}

//checks from bottom left to top right
bool Check_BottomLeft_To_TopRight(char** new_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	if (Y - length + 1 < 0)
		return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y - i][X + i] != string[i])
			return false;

	return true;
}

// THIS FUNCTION Check_TopRight_To_BottomLeft
bool Check_TopRight_To_BottomLeft(char** new_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	if (X - length + 1 < 0 || Y + length - 1 > size)
		return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y + i][X - i] != string[i])
			return false;

	return true;
}

// THIS FUNCTION Check_BottomRight_To_TopLeft
bool Check_BottomRight_To_TopLeft(char** new_grid, const int& size, char* string, const int& length, int Y, int X) 
{
	if (X - length + 1 < 0 || Y - length + 1 < 0)
		    return false;

	for (int i = 0; i < length; i++)
		if (new_grid[Y - i][X - i] != string[i])
			return false;

	return true;
}

// THIS FUNCTION SEARCH WORDS FROM GRID
void Search_Word_From_Grid(ofstream& fout, char** new_grid, const int& size, char* string) 
{
	if (new_grid == NULL)
		   return;

	fout << string << "\t";
	cout << string << "\t";

	int length = String_Length(string);
	bool check = false;

	for (int i = 0; i < size && !check; i++) 
		for (int j = 0; new_grid[i][j] != 0 && !check; j++)
			if (new_grid[i][j] == string[0])
			{
				check = true;
				if (Check_Left_To_Right(new_grid, size, string, length, i, j)) 
				{
					fout << "{" << i << ", " << j << "} {" << i << ", " << j + length - 1 << "}";
					cout << "{" << i << ", " << j << "} {" << i << ", " << j + length - 1 << "}";
				}
				else if (Check_Right_To_Left(new_grid, size, string, length, i, j)) 
				{
					fout << "{" << i << ", " << j << "} {" << i << ", " << j - length + 1 << "}";
					fout << "{" << i << ", " << j << "} {" << i << ", " << j - length + 1 << "}";
				}
				else if (Check_Top_To_Bottom(new_grid, size, string, length, i, j)) {
					fout << "{" << i << ", " << j << "} {" << i + length - 1 << ", " << j << "}";
					cout << "{" << i << ", " << j << "} {" << i + length - 1 << ", " << j << "}";
				}
				else if (Check_Bottom_To_Top(new_grid, size, string, length, i, j)) 
				{
					fout << "{" << i << ", " << j << "} {" << i - length + 1 << ", " << j << "}";
					cout << "{" << i << ", " << j << "} {" << i - length + 1 << ", " << j << "}";
				}
				else if (Check_TopLeft_To_BottomRight(new_grid, size, string, length, i, j)) 
				{
					fout << "{" << i << ", " << j << "} {" << i + length - 1 << ", " << j + length - 1 << "}";
					cout << "{" << i << ", " << j << "} {" << i + length - 1 << ", " << j + length - 1 << "}";
				}
				else if (Check_BottomLeft_To_TopRight(new_grid, size, string, length, i, j)) 
				{
					fout << "{" << i << ", " << j << "} {" << i - length + 1 << ", " << j + length - 1 << "}";
					cout << "{" << i << ", " << j << "} {" << i - length + 1 << ", " << j + length - 1 << "}";
				}
				else if (Check_TopRight_To_BottomLeft(new_grid, size, string, length, i, j))
				{
					fout << "{" << i << ", " << j << "} {" << i + length - 1 << ", " << j - length + 1 << "}";
					cout << "{" << i << ", " << j << "} {" << i + length - 1 << ", " << j - length + 1 << "}";
				}
				else if (Check_BottomRight_To_TopLeft(new_grid, size, string, length, i, j)) 
				{
					fout << "{" << i << ", " << j << "} {" << i - length + 1 << ", " << j - length + 1 << "}";
					cout << "{" << i << ", " << j << "} {" << i - length + 1 << ", " << j - length + 1 << "}";
				}
				else
					check = false;
			}

	if (!check) {
		fout << "NOT FOUND.";
		cout << "NOT FOUND.";
	}
	fout << "\n";
	cout << "\n";
}

// THIS FUNCTION TAKES INPUT FROM FILE AND CHECK WORD PRESENT IN GRID OR NOT AND PRINT IT
void SEARCH_GRID_START()
{ 
	ifstream fin;
	ofstream fout;
	string grid_File;
	string data_File;
	string output_File;
	cout << "ENTER NAME OF THE FILE WHICH HAS A GRID IN IT (i.e. INPUT_GRID.txt) = ";
	cin >> grid_File;

	cout << "ENTER NAME OF THE FILE WHICH HAS SEARCHED NAMES (i.e. SEARCHWORDS.txt) = ";
	cin >> data_File;

	cout <<"ENTER NAME OF THE WHERE LOCATION OF WORDS TO BE PLACED (i.e. OUTPUT.txt)";
	cin >> output_File;

	char** grid, **words;
	int gridSize, listSize, choice;

	grid = Get_Grid_From_File(fin, gridSize, grid_File);
	
	cout << "Enter 0 to input words by yourself else it will take input from file 'wordList'\n"
		 << "ENTER CHOICE: ";
	cin >> choice;
     
	if (!choice)
		words = Get_Words_From_Array(listSize);
	else {
		words = Get_Words_From_Array(fin, listSize, data_File);
		cout << endl;
	}

	if(grid != NULL && words != NULL){
		fout.open(output_File);

		for (int i = 0; i < listSize; i++)
			   Search_Word_From_Grid(fout, grid, gridSize, words[i]);

		cout << "\nResult successfully stored in 'output.txt'.\n";
		fout.close();
	}

	DeallocateMatrix(grid, gridSize);
	DeallocateMatrix(words, listSize);
}
