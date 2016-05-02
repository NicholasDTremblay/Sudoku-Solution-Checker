/*****
placement.h

contains classes for sudoku

Nicholas Tremblay
24/01/2013
*****/
#ifndef PLACEMENT_H
#define PLACEMENT_H

#include <iostream> // input/output

using namespace std;

/*****
placement

class for individual placements

Nicholas Tremblay
24/01/2013
*****/
class placement
{
public:
	bool flagged;        // flagged varaible if value is a problem value
	placement(char num); // overwritten constructor
	char number;		 // number in the placement
};
/*****
grouping

super-class of groupings for placements

Nicholas Tremblay
24/01/2013
*****/
class grouping
{
public:
	placement* myList[9];
	void check();
};
/*****
row

class for row groups

Nicholas Tremblay
24/01/2013
*****/
class row : public grouping
{

};
/*****
column

class for column groups

Nicholas Tremblay
24/01/2013
*****/
class column : public grouping
{

};
/*****
squares

class for square groups

Nicholas Tremblay
24/01/2013
*****/
class square : public grouping
{

};

#endif