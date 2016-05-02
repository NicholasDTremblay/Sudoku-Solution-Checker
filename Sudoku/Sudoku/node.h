/*********************
node.h 

container class for a single linked list
Implementations done inline to adapt to needs of Template

Brian McGee
24 April, 2012
**********************/

#ifndef _NODE_H
#define _NODE_H

// this is the node or container class
// it will hold the content for the linked list
// using templates 
template <class T>
class node
{
public:
	T content;
	node* next;
	//node* previous;

	/*********************
	node 

	constructor

	Brian McGee
	24 April, 2012
	**********************/
	node() 
	{ 
		content = NULL;
		next = NULL;
	//	previous = NULL;
	}

	/*********************
	node 
	args: T - content for this node

	constructor
	Note using templates

	Brian McGee
	24 April, 2012
	**********************/

	node(T name) 
	{ 
		content = name; 
		next = NULL;
	//	previous = NULL;
	}
};

#endif