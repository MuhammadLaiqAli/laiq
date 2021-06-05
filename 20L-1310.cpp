// -_-_-_-_-_-_-_-_-_-_-_-_-_- SUBMITTED BY _-_-_-_-_-_-_-_-_ MUHAMMAD LAIQ ALI ( 20L-1310 ) -_-_-_-__-_____

// -_-_-_-_-_-_-_-_-_-_-_-_-_- SUBMITTED TO _-_-_-_-_-_-_-_-_ TAZEEM HAIDER -_-_-_-__-_____

#include"Header.h"
#include<stdlib.h>

void GRIG_MAKER();  //  THIS FUNCTION MAKE GRID IN THE FILE
void GRID_SEARCH(); // THIS FUNCTION SEARCH WORDS FROM FILE

int main()
{
	cout << "------------------  WELCOME TO PUZZLE GAME  ------------------" << endl << endl;
	cout << "\tMENU" << endl << endl;
	cout << "1. CREATE YOUR GRID. ENTER (C)" << endl <<"2. SEARCH WORDS FROM GRID. ENTER (S)" 
		 << endl << "3. QUIT FROM PUZZLE. ENTER (Q)" << endl << endl;
	char menu;
	cout << "ENTER ANY CHARACTER ACCORDING TO ABOVE OPTION = ";
	cin >> menu;
	while(menu != 'Q' && menu != 'q')
	{
		if(menu == 'C' || menu == 'c')
		{
			GRIG_MAKER();
		}
		if(menu == 'S' || menu == 's')
		{
			GRID_SEARCH();
		}

		cout << "IF YOU WANT TO RETURN TO HOME SCREEN. ENTER ANY KEY .................." << endl;
		cin >> menu;
		system("cls");
		if(menu)
		{
			cout << "------------------  WELCOME TO PUZZLE GAME  ------------------" << endl << endl;
			cout << "\tMENU" << endl << endl;
			cout << "1. CREATE YOUR GRID. ENTER (C)" << endl <<"2. SEARCH WORDS FROM GRID. ENTER (S)" 
				 << endl << "3. QUIT FROM PUZZLE. ENTER (Q)" << endl << endl;
			cout << "ENTER ANY CHARACTER ACCORDING TO ABOVE OPTION = ";
			cin >> menu;
		}
		if(menu == 'q' || menu == 'Q')
			   break;
	}

	system("pause");
	return 0;
}

 //  THIS FUNCTION MAKE GRID IN THE FILE
void GRID_SEARCH()
{
	SEARCH_GRID_START();
}

// THIS FUNCTION SEARCH WORDS FROM FILE
void GRIG_MAKER()
{
	Grid_Work Grid; //MAKE AN OBJECT IN Drid_wORK CLASS
	Grid.INPUT_COMPLETE_GRID();
}