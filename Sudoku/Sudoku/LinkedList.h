/*********************
LinkedList.h 

a single linked list
Implementations done inline to adapt to needs of Template

Brian McGee
24 April, 2012

Edited by: Nicholas Tremblay
25/04/2012
**********************/

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "node.h"

template <class R>
class LinkedList
{
public:

	/*********************
	size 

	returns	int (# of nodes in list)


	Brian McGee
	24 April, 2012
	**********************/
	int size() 
	{ 
		return this->length;
	}

	/*********************
	LinkedList 

	constructor

	Brian McGee
	24 April, 2012
	**********************/
	LinkedList() 
	{ 
		first=NULL; 
		length=0;
	}

	/*********************
	insert 

	args	R (value to save to the list)
	Note that value type is a template

	inserts new value at the beginning of the list


	Brian McGee
	24 April, 2012
	**********************/
	void insert(R value)
	{
		// this will the the only item in the list
		if (first== NULL)
		{
			first = new node<R>(value);
		}
		// other things int he list; put this ahead of them
		else
		{
			// point to current first item
			node<R>* temp = first;
			//made a brand new node pointed to by first
			first = new node<R>(value);
			// nake that brand new node's next point to the former first
			first->next = temp;
			temp=NULL;
		}
		// track size change
		length++;
	}
/*********************
	push_back 

	args	R (value to save to the list)
	returns none

	inserts new value at the end of the list


	Nicholas Tremblay
	25 April, 2012
	**********************/
	void push_back(R value)
	{
		if(first == NULL)//if there is nothing in list
		{
			first = new node<R>(value);//first item = new item
		}
		else
		{
			node<R>* temp = first;//temporary value equal to the first item
			int count = 0;

			while(count < size()-1)//count to end of list
			{
				count++;
				temp = temp->next;
			}
			temp->next = new node<R>(value);//set the 'next' value equal to the new item
			temp=NULL;
		}
		length++;//add 1 to length
	}

	/*********************
	~LinkedList 

	destructor. Cleans up memory

	Brian McGee
	24 April, 2012
	**********************/
	~LinkedList()
	{
		// look at first node
		node<R>* temp = first;

		// so long at the nood we're looking at exists
		while(temp!=NULL)
		{
			// note the current node
			node<R>* kill = temp;
			// look to the next node
			temp = temp->next;
			// recover memory from the current node
			delete kill;
			kill=NULL;
		}

		// extra cleanup. Not really necessary for 
		// a destructor but it keeps things neat
		first = NULL;
		length=0;
	}

	/*********************
	at 

	args	int (location in list to nab a value)

	returns	R (content of node at set location)
	Note that value type is a template

	list starts at 0. Asking for a non-existant node throws an exception

	Brian McGee
	24 April, 2012

	Edited By: Nicholas Tremblay
	25/04/2012
	**********************/
	R* at(int location)
	{
		if (location >= length)//throw wasn't working so i changed the logic
		{
			location = length-1;//if length or above, sets equal to length - 1
			throw "Out of Range";
		}
		if(location < 0)//if lower than 0, sets it to 0
		{
			location = 0;
			throw "Out of Range";
		}
		if(length == 0)//if the list is empty
		{
			//first = new node<R>(value);//creates an item to put into the list...this is done to avoid crashing.
			//length++;
			throw "empty";
		}

		int count=0;
		node<R>* look = first;
		// look is an ITERATOR - item designed to wander through a list
	
		// wander list until count == location
		while (count<location)
		{
			count++;
			look = look->next;
		}
		// done wandering the list; at correct location now
		return &look->content;
	}
	/*********************
	Overloaded operator []

	args	int (location in list to nab a value)

	returns	R (content of node at set location)
	Note that value type is a template

	list starts at 0. Asking for a non-existant node throws an exception

	Nicholas Tremblay
	30/04/2012
	**********************/
	R operator [] (int location)
	{
		if (location >= length)//throw wasn't working so i changed the logic
		{
			//location = length-1;//if length or above, sets equal to length - 1
			throw exception("BAD");
		}
		if(location < 0)//if lower than 0, sets it to 0
		{
			//location = 0;
			throw exception("BAD");
		}
		if(length == 0)//if the list is empty
		{
			//first = new node<R>(value);//creates an item to put into the list...this is done to avoid crashing.
			//length++;
			throw exception("BAD");
		}

		int count=0;
		node<R>* look = first;
		// look is an ITERATOR - item designed to wander through a list
	
		// wander list until count == location
		while (count<location)
		{
			count++;
			look = look->next;
		}
		// done wandering the list; at correct location now
		return look->content;
	}
	/*********************
	pop 

	args	none
	returns R (what is deleted)

	deletes value at the end of the list


	Nicholas Tremblay
	25 April, 2012
	**********************/
	R pop()
	{
		node<R>* temp = first;
		int count = 0;
		int newcount = 0;

		while(count < size()-1)//counts to end of list
		{
			temp = temp->next;
			count++;
		}
		length--;//adjust the length
		R t = temp->content;
		delete temp;
		temp = first;
		while(newcount < size()-1)
		{
			temp = temp->next;
			newcount++;
		}
		temp->next = NULL;
		return t;
	}
	/*********************
	clear

	args	none
	returns none

	empties the list

	Nicholas Tremblay
	25 April, 2012
	**********************/
	void clear()
	{
		// look at first node
		node<R>* temp = first;

		// so long at the nood we're looking at exists
		while(temp!=NULL)
		{
			// note the current node
			node<R>* kill = temp;
			// look to the next node
			temp = temp->next;
			// recover memory from the current node
			delete kill;
			kill=NULL;
		}
		first = NULL;
		length=0;
	}
	/*********************
	sort

	args	none
	returns none

	sorts the list

	Nicholas Tremblay
	01 May, 2012
	**********************/
	void sort()
	{
		node<R>* temp = first;
		//int temp;
		node<R>* temptemp = first;
		int templength = length;
		bool swap;

		for(int acount = 0; acount < templength; acount++)
		{
			temp = first;
			temptemp = first;
			do
			{
					swap = false;
				if(temp->next != NULL)
				{
					if(temp->content > temp->next->content)
					{
						swap = true;
						
						if(temp->next->next==NULL)
						{
							temptemp->next = temp->next;
							temp->next->next = temp;
							temp->next = NULL;
						}
						else
						{
							temptemp->next = temp->next;
							temptemp = temp;
							temp->next = temp->next->next;
							temp->next->next = temp;
						}
					}
					if(!swap)
					{
						temptemp = temp;
						temp = temp->next;
					}
				}
			}while(temp->next != NULL);
		}																																																																																																																			
	}
	/*********************
	reversesort

	args	none
	returns none

	sorts the list from largest to smallest

	Nicholas Tremblay
	09 May, 2012
	**********************/
	void reversesort()
	{
		node<R>* temp = first;
		//int temp;
		node<R>* temptemp = first;
		int templength = length;
		bool swap;

		for(int acount = 0; acount < templength; acount++)
		{
			temp = first;
			temptemp = first;
			do
			{
					swap = false;
				if(temp->next != NULL)
				{
					if(temp->content < temp->next->content)
					{
						swap = true;
						
						if(temp->next->next==NULL)
						{
							temptemp->next = temp->next;
							temp->next->next = temp;
							temp->next = NULL;
						}
						else
						{
							temptemp->next = temp->next;
							temptemp = temp;
							temp->next = temp->next->next;
							temp->next->next = temp;
						}
					}
					if(!swap)
					{
						temptemp = temp;
						temp = temp->next;
					}
				}
			}while(temp->next != NULL);
		}																																																																																																																			
	}
	/*********************
	includeAT

	args	R (what is to be included)
			int (where to include it)
	returns none

	inserts an item into the selcted position

	Nicholas Tremblay
	01 May, 2012
	**********************/
	void includeAT(R variable, int place)
	{
		if(length == 0 && place == 0)
		{
			first = new node<R>(variable);
			first->next = NULL;
		}
		else if(place >= length||place < 0)
		{
			throw "Out of Range";
		}
		else
		{
			node<R>* temp = first;//temporary value equal to the first item
			int count = 0;

			while(count < place-1)//count to end of list
			{
				count++;
				temp = temp->next;
			}
			if(temp->next != NULL)
			{
				node<R>* nexttemp = temp->next;
				temp->next = new node<R>(variable);//set the 'next' value equal to the new item
				temp->next->next = nexttemp;
				temp = NULL;
			}
			else
			{
				temp->next = new node<R>(variable);
				temp->next->next = NULL;
				temp = NULL;
			}
		}
		length++;
	}
		/*********************
	removeAT

	args	int (where to include it)
	returns R (what is deleted)

	removes an item out of the selcted position

	Nicholas Tremblay
	02 May, 2012
	**********************/
	R removeAT(int place)
	{
		if(length == 0 && place == 0)
		{
			throw "Out of Range";
		}
		else if(place >= length||place < 0)
		{
			throw "Out of Range";
		}
		else
		{
			node<R>* temp = first;
			node<R>* temptemp = first;
			int count = 0;

			while(count < place)//counts to end of list
			{
				temptemp = temp;
				temp = temp->next;
				count++;
			}
			R t = temp->content;
			temptemp->next = temp->next;
			delete temp;//then delete the item
			length--;//adjust the length
			return t;
		}
	}


private:
	int length;
	node<R>* first;


};

#endif
