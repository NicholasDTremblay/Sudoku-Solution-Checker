/*****
placement.cpp

contains class methods for sudoku

Nicholas Tremblay
24/01/2013
*****/
#include "placement.h" // connect to placement.h
/*****
placement::placement

overwritten constructor for placements

Args: char
Retn: none

Nicholas Tremblay
24/01/2013
*****/
placement::placement(char num)
{
	number = num; // placement number is now number given

	flagged = false; // set flagged to false for default
}
/*****
grouping::check

checks if there are any faults with the grouping

Args: None
Retn: none

Nicholas Tremblay
24/01/2013
*****/
void grouping::check()
{
	for(int i = 0; i < 9; i++)							//for each placement in group
	{
		for(int k = i + 1; k < 9; k++)					//for each placement that hasn't been checked yet
		{
			if(myList[i]->number == myList[k]->number)  //if the values of the two placements are the same
			{
				myList[i]->flagged = true;				//flag one
				myList[k]->flagged = true;				//flag the other
			}
		}
	}
}