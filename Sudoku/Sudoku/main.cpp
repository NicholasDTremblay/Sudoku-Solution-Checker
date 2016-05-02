/*****
Sudoku Checker

By : Nicholas Tremblay

This project was to create an optimal
sudoku solution checker. My solution
loads a text file or allows the user
to input their own sudoku and choose
whether of not to save it to a file.
It outputs the sudoku given with problem
numbers highlighted.

for: Stephen Johnson
24/01/2013
*****/
#include <iostream>                                                                                 //input output
#include <fstream>                                                                                  // file stream
#include <conio.h>                                                                                  // getch
#include <string>                                                                                   // string handling
#include <Windows.h>                                                                                // set colours
#include "placement.h"																				// placement class file

using namespace std;

void set_colour(short int);																			// prototype for colour function
/*****
main

main function that runs the program

Args: None
Retn: int

Nicholas Tremblay
24/01/2013
*****/
int main()
{
	fstream myfile;																					// file stream

	char temp;																						// temporary char used for getting characters from a file

	row* therows[9];																				// array of row groupings

	for(int i = 0; i < 9; i ++)																		// for each space in the array create a new row
	{
		therows[i] = new row();
	}

	column* thecolumns[9];																			// array of column groupings

	for(int i = 0; i < 9; i ++)																		// for each space in the array create a new column
	{
		thecolumns[i] = new column();
	}

	square* thesquares[9];																			// array of square groupings

	for(int i = 0; i < 9; i ++)																		// for each space in the array create a new square
	{
		thesquares[i] = new square();
	}

	char cmenu = ' ';																				// first menu selection variable
	char lmenu = ' ';																				// load menu selection variable
	char savemenu = ' ';																			// save menu selection variable
	char savespot = ' ';																			// save menu selection variable for which file to save to

	bool rowbad = false;																			// variable for checking if the user has made a bad row whilst writing a solution
	bool problem = true;																			// variable for checking each char the user types to see if there is a problem (not a number from 1 to 9)

	placement* thegrid[9][9];																		// 2d array containing each placement in the sudoku puzzle

	string currentrow;																				// string the user writes to to create a solution

	do																								// do while the user does not quit
	{
		system("cls");																				// clear the screen

		cout << "Menu: \n\n";																		//output menu
		cout << "1. Load puzzle from file \n";
		cout << "2. Write your own puzzle\n";
		cout << "Q. quit\n";

		cmenu = _getch();																			//get user input

		switch(cmenu)																				// switch for menu options
		{
		case '1':																					// load puzzle from a file
			do
			{
				system("cls");																		// clear screen
				cout << "Which file would you like to load\n";										// output load file choices
				cout << "1. Preloaded answer one\n";
				cout << "2. Preloaded answer two\n";
				cout << "3. Preloaded answer three\n";
				cout << "4. Saved answer one\n";
				cout << "5. Saved answer two\n";
				cout << "6. Saved answer three\n";

				lmenu = _getch();																	// get user input

				switch(lmenu)																		// switch for what file user wanted to load from
				{
				case '1':
					myfile.open("answer1.txt");														// load pre-loaded answer 1
					break;
				case '2':
					myfile.open("answer2.txt");														// load pre-loaded answer 2
					break;
				case '3':
					myfile.open("answer3.txt");														// load pre-loaded answer 3
					break;
				case '4':
					myfile.open("save1.txt");														// load saved answer 1
					break;
				case '5':
					myfile.open("save2.txt");														// load saved answer 1
					break;
				case '6':
					myfile.open("save3.txt");														// load saved answer 1
					break;
				}

				if(myfile.is_open())																// make sure file opened properly
				{
					for(int i = 0; i < 9; i++)														// for each row
					{
						for(int k = 0; k < 9; k++)													// and each column
						{
							myfile >> temp;															// load next value
							thegrid[i][k] = new placement(temp);									//make a placement of that value a x,y = i,k
							therows[i]->myList[k] = thegrid[i][k];									//add new placement to proper row group
							thecolumns[k]->myList[i] = thegrid[i][k];								// add new placement to proper column group
																									// overly complicated solution for determining the square the placement belongs to
							if(i < 3)																// if in first 3 rows
							{
								if(k < 3)															// if in first three columns
								{
									thesquares[(k/3)]->myList[k + (3*i)] = thegrid[i][k];			// put placement in correct square group
								}
								else if(k < 6)														// if in next three columns
								{
									thesquares[(k/3)]->myList[k - 3 + (3*i)] = thegrid[i][k];		// put placement in correct square group
								}
								else if(k < 9)														// if in last three columns
								{
									thesquares[(k/3)]->myList[k - 6 + (3*i)] = thegrid[i][k];		// put placement in correct square group
								}
							}
							else if(i < 6)															// if in next three rows
							{
								if(k < 3)															// if in first three columns
								{
									thesquares[((k)/3)+3]->myList[k + (3*(i-3))] = thegrid[i][k];   // put placement in correct square group
								}
								else if(k < 6)														// if in next three columns
								{
									thesquares[((k)/3)+3]->myList[k - 3 + (3*(i-3))] = thegrid[i][k];// put placement in correct square group
								}
								else if(k < 9)														// if in next last three columns
								{
									thesquares[((k)/3)+3]->myList[k - 6 + (3*(i-3))] = thegrid[i][k];// put placement in correct square group
								}
							}
							else if(i < 9)															// if in last three rows
							{
								if(k < 3)															// if in first three columns
								{
									thesquares[((k)/3)+6]->myList[k + (3*(i-6))] = thegrid[i][k];   // put placement in correct square group
								}
								else if(k < 6)														// if in next 3 columns
								{
									thesquares[((k)/3)+6]->myList[k - 3 + (3*(i-6))] = thegrid[i][k];// put placement in correct square group
								}
								else if(k < 9)														// if in last 3 columns
								{
									thesquares[((k)/3)+6]->myList[k - 6 + (3*(i-6))] = thegrid[i][k]; // put placement in correct square group
								}
							}
						}
					}

					myfile.close();																	// close file, we don't need it anymore
					for(int i = 0; i < 9;i++)														// for each space in our arrays of groupings
					{
						therows[i]->check();														//check if there are problem numbers in the row
						thecolumns[i]->check();														// check if there are problem numbers in the column
						thesquares[i]->check();														// check if there are problem numbers in the square
					}
					system("cls");																	// clear the screen
					for(int i = 0; i < 9; i++)														// for each row
					{
						for(int k = 0; k < 9; k++)													// and each column
						{
							if(thegrid[i][k]->flagged == true)										// if value at row,column is flagged bad make print red
							{
								set_colour(12);
							}
							else																	// otherwise set print to normal
							{
								set_colour(7);
							}
							cout << thegrid[i][k]->number;											// output the number
						}

						cout << endl;																// if we hit the end of our row, we want to jump to the next line
					}
					system("pause");																// pause so player may see results

					set_colour(7);																	// set colour back to normal

					for(int i = 9; i > 0; i--)														//delete each item in our grid because we are done with them
					{
						for(int k = 9; k > 9; k--)
						{
							delete thegrid[i][k];
						}
					}
				}


			}while(lmenu != '1' && lmenu != '2' && lmenu != '3' && lmenu != '4' && lmenu != '5' && lmenu != '6');
			break;
		case '2':																					// player chose to write their own solution
			do																						// while the user doesn't press a valid key
			{
				system("cls");																		// clear the screen
				cout << "Would you like to save this answer?\n";									// output menu
				cout << "1. Yes\n";
				cout << "2. No\n";

				savemenu = _getch();																// get user input

			}while(savemenu != '1' && savemenu != '2');
			if(savemenu == '1')																		// if user chooses to save their solution
			{
				do																					// while the user doesn't press a valid key
				{
					system("cls");																	// clear the screen
					cout << "Where would you like to save?\n";										// output menu
					cout << "1. Save one\n";
					cout << "2. Save two\n";
					cout << "3. Save three\n";

					savespot = _getch();															// get input
				}while(savespot != '1' && savespot != '2' && savespot != '3');

				switch(savespot)																	// switch for which file they'd like to save to
				{
				case '1':
					myfile.open("save1.txt", fstream::out | fstream::trunc);						// open file 1
					break;
				case '2':
					myfile.open("save2.txt", fstream::out | fstream::trunc);						// open file 2
					break;
				case '3':
					myfile.open("save3.txt", fstream::out | fstream::trunc);						// open file 3
					break;
				}
				if(myfile.is_open())																// if file opened properly
				{
					for(int i = 0; i < 9; i++)														// for each row
					{
						do																			// while the row the user typed is not valid for sudoku
						{
							problem = false;														// set problem variable to false
							system("cls");															// clear the screen
							cout << "Please write line " << i + 1 << " using 9 numbers from 1 to 9: "; // output to tell the user to make a row
							getline(cin, currentrow);												// user inputs row

							if(currentrow.size() == 9)												// if the row is the correct size
							{
								for(int j = 0; j < 9; j++)											// for each item in the row
								{
									cout << endl << currentrow.at(j);

									if(currentrow.at(j) == '1')										// check value, if 1 to 9 output the number
									{
										cout << "This is a 1";
									}
									else if(currentrow.at(j) == '2')
									{
										cout << "This is a 2";
									}
									else if(currentrow.at(j) == '3')
									{
										cout << "This is a 3";
									}
									else if(currentrow.at(j) == '4')
									{
										cout << "This is a 4";
									}
									else if(currentrow.at(j) == '5')
									{
										cout << "This is a 5";
									}
									else if(currentrow.at(j) == '6')
									{
										cout << "This is a 6";
									}
									else if(currentrow.at(j) == '7')
									{
										cout << "This is a 7";
									}
									else if(currentrow.at(j) == '8')
									{
										cout << "This is a 8";
									}
									else if(currentrow.at(j) == '9')
									{
										cout << "This is a 9";
									}
									else																	// if not valid number
									{
										problem = true;														// set problem to true
										cout << "there is a problem";										// output that there is a problem
									}
								}
							}
							else																			// if the row was incorrect size
							{
								problem = true;																// set problem to true
							}

							rowbad = problem;																// get value from problem to see if we should exit loop

						}while(rowbad == true);

						for(int k = 0; k < 9; k++)															// for each column
						{
							myfile << currentrow[k];														// save value to file
							if(k != 8)																		// if not the end of the row
							{
								myfile << ' ';																// add a space to the file
							}
							else																			//otherwise
							{
								myfile << endl;																// go to next line in file
							}
							thegrid[i][k] = new placement(currentrow[k]);									// make new placement with current value at x,y = i,k
							therows[i]->myList[k] = thegrid[i][k];											// add new placement to proper row
							thecolumns[k]->myList[i] = thegrid[i][k];										// add new placement to proper column
							if(i < 3)																		// if first three rows
							{
								if(k < 3)																	// if first three columns
								{
									thesquares[(k/3)]->myList[k + (3*i)] = thegrid[i][k];					// add placement to proper square
								}
								else if(k < 6)																// if next three columns
								{
									thesquares[(k/3)]->myList[k - 3 + (3*i)] = thegrid[i][k];				// add placement to proper square
								}
								else if(k < 9)																// if last three columns
								{
									thesquares[(k/3)]->myList[k - 6 + (3*i)] = thegrid[i][k];				// add placement to proper square
								}
							}
							else if(i < 6)																	// if next three rows
							{
								if(k < 3)																	// if first three columns
								{
									thesquares[((k)/3)+3]->myList[k + (3*(i-3))] = thegrid[i][k];			// add placement to proper square
								}
								else if(k < 6)																// if next three columns
								{
									thesquares[((k)/3)+3]->myList[k - 3 + (3*(i-3))] = thegrid[i][k];		// add placement to proper square
								}
								else if(k < 9)																// if last three columns
								{
									thesquares[((k)/3)+3]->myList[k - 6 + (3*(i-3))] = thegrid[i][k];		// add placement to proper square
								}
							}
							else if(i < 9)																	// if last three rows
							{
								if(k < 3)																	// if first three columns
								{
									thesquares[((k)/3)+6]->myList[k + (3*(i-6))] = thegrid[i][k];			// add placement to proper square
								}
								else if(k < 6)																// if next three columns
								{
									thesquares[((k)/3)+6]->myList[k - 3 + (3*(i-6))] = thegrid[i][k];		// add placement to proper square
								}
								else if(k < 9)																// if last three columns
								{
									thesquares[((k)/3)+6]->myList[k - 6 + (3*(i-6))] = thegrid[i][k];		// add placement to proper square
								}
							}
						}

						rowbad = false;																		// reset the check for row validity for next row
					}
					
					myfile.close();																			// close file, we are don't with it
				}
			}
			else																							// if saving is not wanted, do the above block minus the saving bit (I really don't want to comment it again)
			{
				for(int i = 0; i < 9; i++)
				{
					do
					{
						problem = false;
						system("cls");
						cout << "Please write line " << i + 1 << " using 9 numbers from 1 to 9: ";
						getline(cin, currentrow);

						if(currentrow.size() == 9)
						{
							for(int j = 0; j < 9; j++)
							{
								cout << endl << currentrow.at(j);

								if(currentrow.at(j) == '1')
								{
									cout << "This is a 1";
								}
								else if(currentrow.at(j) == '2')
								{
									cout << "This is a 2";
								}
								else if(currentrow.at(j) == '3')
								{
									cout << "This is a 3";
								}
								else if(currentrow.at(j) == '4')
								{
									cout << "This is a 4";
								}
								else if(currentrow.at(j) == '5')
								{
									cout << "This is a 5";
								}
								else if(currentrow.at(j) == '6')
								{
									cout << "This is a 6";
								}
								else if(currentrow.at(j) == '7')
								{
									cout << "This is a 7";
								}
								else if(currentrow.at(j) == '8')
								{
									cout << "This is a 8";
								}
								else if(currentrow.at(j) == '9')
								{
									cout << "This is a 9";
								}
								else
								{
									problem = true;
									cout << "there is a problem";
								}
							}
						}
						else
						{
							problem = true;
						
						}

						rowbad = problem;

					}while(rowbad == true);

					for(int k = 0; k < 9; k++)
					{
						thegrid[i][k] = new placement(currentrow[k]);
						therows[i]->myList[k] = thegrid[i][k];
						thecolumns[k]->myList[i] = thegrid[i][k];
						if(i < 3)
						{
							if(k < 3)
							{
								thesquares[(k/3)]->myList[k + (3*i)] = thegrid[i][k];
							}
							else if(k < 6)
							{
								thesquares[(k/3)]->myList[k - 3 + (3*i)] = thegrid[i][k];
							}
							else if(k < 9)
							{
								thesquares[(k/3)]->myList[k - 6 + (3*i)] = thegrid[i][k];
							}
						}
						else if(i < 6)
						{
							if(k < 3)
							{
								thesquares[((k)/3)+3]->myList[k + (3*(i-3))] = thegrid[i][k];
							}
							else if(k < 6)
							{
								thesquares[((k)/3)+3]->myList[k - 3 + (3*(i-3))] = thegrid[i][k];
							}
							else if(k < 9)
							{
								thesquares[((k)/3)+3]->myList[k - 6 + (3*(i-3))] = thegrid[i][k];
							}
						}
						else if(i < 9)
						{
							if(k < 3)
							{
								thesquares[((k)/3)+6]->myList[k + (3*(i-6))] = thegrid[i][k];
							}
							else if(k < 6)
							{
								thesquares[((k)/3)+6]->myList[k - 3 + (3*(i-6))] = thegrid[i][k];
							}
							else if(k < 9)
							{
								thesquares[((k)/3)+6]->myList[k - 6 + (3*(i-6))] = thegrid[i][k];
							}
						}
					}

					rowbad = false;
				}
			}

			
			for(int i = 0; i < 9;i++)																// for each space in our arrays of groupings
			{
				therows[i]->check();																//check if there are problem numbers in the row
				thecolumns[i]->check();																// check if there are problem numbers in the column
				thesquares[i]->check();																// check if there are problem numbers in the square
			}
			system("cls");																			// clear the screen
			for(int i = 0; i < 9; i++)																// for each row
			{
				for(int k = 0; k < 9; k++)															// and each column
				{
					if(thegrid[i][k]->flagged == true)												// if value at row,column is flagged bad make print red
					{
						set_colour(12);
					}
					else																			// otherwise set print to normal
					{
						set_colour(7);
					}
					cout << thegrid[i][k]->number;													// output the number
				}

				cout << endl;																		// if we hit the end of our row, we want to jump to the next line
			}
			system("pause");																		// pause so player may see results

			set_colour(7);																			// set colour back to normal

			for(int i = 9; i > 0; i--)																//delete each item in our grid because we are done with them
			{
				for(int k = 9; k > 9; k--)
				{
					delete thegrid[i][k];
				}
			}
			break;
		}

	}while(cmenu != 'q');

	for(int i = 8; i > 0; i--)																		// for each grouping in thier respective arrays we delete them to free up the memory
	{
		delete therows[i];
		delete thecolumns[i];
		delete thesquares[i];
	}

	return 0;																						// end of program
}

/******************
* set_colour
* arg:	short int (code for colour to use)
*
* sets the colour for future outputs to the screen
*
* by Brian McGee
* created 14 Sept 2007
******************/

void set_colour(short int a)
{
     // don't worry about these details; you'll learn them soon enough
     HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE ); // Make a handle
     SetConsoleTextAttribute( handle, a ); // Set the colour of the text
}