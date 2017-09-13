//
//  list.h -	Generic Sorted Singly Linked List Template  
//				 
// Purpose - This file contains the templated implementation of a finite generic sorted singly linked list.
//			  A linkedlist is a collection of Nodes. Each Node in the list has 2 components - data(place to
//			  contain the information) and link to the next Node. The head of a linkedlist points to the
//			  first Node of the list.  The last Node will have the link as null value to indicate the end.
//			  The linked list dynamically grows and needs no reallocation as the data is not stored 
//			   contigously as in arrays.
//			  This list can be used to easily implement other data structures like stacks and queues
//			  The list can be used to store any object type - eg, double, employee 
//			  Data is inserted into the list in sorted order. This means that the objects being stored
//			  in the list should have the following operators overloaded - ==, !=, <, >, <<
//			  
//			  The linked list provides the following basic functions
//			   - insert a new item
//				- retrieve an existing item
//				- remove an existing item
//				-  merge(union) 2 lists into the existing list
//				-  intersect 2 lists into the existing list
//				
// Assumptions:
//				- The Object stored in the Node of the linked list should have overloaded operators 
//					==, !=, <, >, <<
//				-  The list can have duplicate values
//			    - There is no dummy head Node. The head always points to a valid Node in case of 
//				   non-empty list
//				- Any operation on the list will maintain the list in sorted order
//				- The head pointer of the list always points to the first Node in the list
//				- The list is sorted using the insertion algorithm
//			    - List doesnot allow random access
//				- The list will not validate or read the file in buildList. It is the responsibility
//					of the datatype the list contains to read the file. 
// Analysis:
//				 Find an item in linked list -  O(n) 
//				 Insert/delete at beginning - O(1)
//			     Insert/delete at end - O(n)		
//				
//Author: Reshma Sivakumar
//Date: 11/1/2016

#ifndef list_h
#define list_h

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;
//
// begin - Header definition for list template 
//
template <class Object>   //template takes any object
class list {			//class list

	//overload the << operator - no need of specifying template
	//Operator << overloaded: Display the contents of the list
	//			Empty list is displayed as {}
	//PRE: None
	//POST: Displays elements of this set within {}
	friend ostream& operator <<(ostream& out, const list<Object>& list) {
		Node* current = list.head;  //start from head Node
		if (list.isEmpty())
		{
			out << "{}" << endl;
			return out;
		}
		while (current != NULL) {		//while not end of list
			out << *current->data << " ";	//print data in current node
			current = current->next;		//traverse to next node
		}
		out << endl;			
		return out;
	}

//public members of list class	
public:
	list();						//default constructor
	list(const list<Object>&);	//copy constructor
	~list();					//destructor
	void buildList(ifstream&);	//create list from file
	bool insert(Object&);		//insert a new object in sorted order
	bool insertFirst(Object&);			//append a new object 
	bool isEmpty() const;		//check if list empty
	bool remove(const Object&);	//remove an element from list
	bool remove(const Object&, Object&);//remove an element from list and pass deleted object as reference
	bool retrieve(const Object&, Object&) const;//retrieve an element from list
	bool retrieve(const Object&) const; //retrieve an element from list and pass deleted object as reference
	int getSize() const;				//return size of element
	void merge(list<Object>&, list&);	//set this list to union of 2 lists
	void makeEmpty();					//clear this list
	void makeEmpty(list<Object>&) const; //clear list passed 
	void intersect(const list&, const list&);//common elements in 2 sets
	list<Object> operator +(const list<Object>&) const; //overload + operator
	list<Object>& operator =(const list<Object>&);//overload = operator
	bool operator ==(const list<Object>&) const;//overload == operator
	bool operator !=(const list<Object>&) const;//overload != operator

// private members of list class
private:
	//template <class TBA>  //node can store generic data
	struct Node {			//node structure
		Object* data;		//node data generic type	
		Node* next;  //link to next node
	};

	Node* head;			//head pointer to first element in list
	int size;					//size of list
	void copy(const list<Object>&);  //helper method to copy elements of list passed to this list
};

/*-------------template implementation*/
// Default constructor: Creates an empty instance of list class and sets head to NULL.
//						Does not create empty node
// PRE:  none
// POST: An empty list object is created
template <class Object>
list<Object>::list() {
	head = NULL;
	this->size = 0;
}

// Copy Constructor - constructs a new list object by making a deep copy of the list passed
// PRE: other list is a valid sorted list
// POST: This list object is created with the same elements in the input list object passed
template <class Object>
list<Object>::list(const list<Object> &other) {
	if (!other.isEmpty())
	{
		this->head =NULL;
		copy(other);
	}
	else
	{
		cout << "Empty object list passed" << endl;
	}

}

//Destructor - destroys this list object and sets the head to NULL
//PRE: None
//POST: The list object is destroyed
template <class Object>
list<Object> :: ~list() {
	makeEmpty ();

}

//buildList - reads an input file that contains list data and creates a sorted list
//			 The input file will contain data of the type of data called. For eg
//			 for nodedata object type  format will be
//			 <intvalue> <char>
//			 100 g
//			 The buildList method will not validate the values in the file nor will 
//			 read the inputs from the file. Its the responsibility of the Object class
//			to know how to read the file. 
//			The input file object is read and data inserted into the list in sorted order
//PRE: Pass a valid ifstream object which contains the data that is read from an input file
//POST: The list object is destroyed
template <class Object>
void list<Object>::buildList(ifstream& infile) {
	Object* ptr;   //pointer to store a record in filestream object
 
	if (!infile) {		//if file is not valid
		cout << "File could not be opened" << endl;
		return;
	}

	while (!infile.eof()) {  //read data from filestream object
		ptr = new Object;	// create new Object
		//call setData method to set the Node data to record read
		bool success = ptr->setData(infile); 
		if (infile.eof()) {				//if end of file
			delete ptr;					//delete the pointer
			break;					
		}
		if (success) {					//if data read successfully
			if (!insert(*ptr)) {		// insert data
				delete ptr;				//if insertion failed  delete pointer
				break;					//stop file read
			}

		}
		else
		{							    //if data not read successfully 
			delete ptr;					//delete pointer and break
			break;
		}


	}
	ptr = NULL;							//set ptr to null
	infile.close();						//close file stream
 
}

//isEmpty - check if this list is empty
//PRE: None
//POST: returns true(1) if empty, false(0) otherwise
template <class Object>
bool list<Object>::isEmpty() const {
	return (head == NULL);  //If head is null, list is empty
}

//insertFirst - adds the passed object as first node
//PRE: Valid node data passed
//POST: returns true(1) if value successfully inserted, false(0) otherwise
template <class Object>
bool list<Object>::insertFirst(Object& dataPtr) {
	 
	Node *newPtr = new Node; //create new node
	 
	newPtr->data = &dataPtr;		//set new node data to value passed
	if (this->head == NULL)			// if empty list
	{
		this->head = newPtr;		//point head to new node
		newPtr->next = NULL;		//set next to null
	}
	else                              //if list not empty
	{
		Node *current = head;	//point head in current
		newPtr->next = current;			//new node pointer points to current (head)
		this -> head = newPtr;			//head of this list points to new node
	}

	return true;
}

//insert - inserts an Object into the correct sorted position in the list
//			The list is sorted using insertion sort algorithm with pseudo code as follows
//			The list is imaginary divided into sorted part and unsorted part. The sorted
//			part contains the first element in the list and the rest are the unsorted part
//			The algortihm takes the first element in the unsorted parts and inserts in the
//			right position in the sorted part and continues with the second element and so
//			on till list becomes empty
//PRE: Valid node data passed
//POST: returns true(1) if value successfully inserted, false(0) otherwise
template <class Object>
bool list<Object>::insert(Object& dataPtr) {
	Node* ptr = new Node; //create new node
	if (ptr == NULL) return false;     //check for out of memory

	ptr->data = &dataPtr;   // new node data set to input
	if (!ptr->data)        //check if input reference has valid data
		return false;
	this->size++;			//set size of list


	//if (isEmpty() || *ptr->data < *this->head->data) { //if empty or first node data less than head
	if (isEmpty()  ) {
		ptr->next = head;				// insert new node as first node, firstnode link to head
		head = ptr;						//set head to new node
		
	}
	else {			//if not empty list
		Node* current = head->next;  //set current to second node - unsorted part
		Node* previous = head;		  // set previous to head - sorted part

		//till list becomes empty, traverse list  till current data is greater than new node
		while (current != NULL  ) { 
			previous = current;		   
			current = current->next;
		}
		// reached the point where new node needs to be inserted (insert before current)
		ptr->next = current;    //set new node link to current
		previous->next = ptr;   //previous node to new node
		current = NULL;
		previous = NULL;
	}
	
	ptr = NULL;
	return true;
}


//facade pattern - remove
template <class Object>
bool list<Object>::remove(const Object &dataPtr) {
	Object deletedPtr; //passing null value when return object not needed
	return remove(dataPtr, deletedPtr);

}

//remove - remove an Object from sorted list
//		  
//PRE: Valid Object to be removed is passed, an empty/non-empty Object is passed
//	   by reference so the Object removed will be stored in this Object and referenced
//		from calling program
//POST: returns true(1) if value successfully removed, false(0) otherwise
//		stores the deletedobject in the passed object reference

template <class Object>
bool list<Object>::remove(const Object& dataPtr, Object &deletedNode) {
	if (dataPtr == NULL) {  //if null object passed
		//cout << "Error: Object passed is NULL" << endl;
		return false;
	}
	if (isEmpty()) {   //if empty nothing to remove
		return false;
	}
	//if list has single node and if node matches input 
	
	if (head->next == NULL && *head->data == dataPtr) {
		deletedNode = *head->data; //store data in deletenode
		delete head;		//remvoe the data
		head = NULL;
		this->size--;		//decrement size
		return true;
	}
	else {	//list contains >1 elements, traverse list to find element
		Node* current = head;  //set current to head
		Node* previous = head;  //prev to head

		if (*current->data == dataPtr) // check if first node to delete
		{

			head = current->next;			//head points to the next node after matched
			deletedNode = *current->data;  //store matched data to deletednode
			delete current;					//delete the matched node
			current = NULL;
			previous = NULL;
			this->size--;
			return true;
		}
		else {  //if not first node matched, traverse rest of list
			while (current != NULL) { //till empty
				if (*current->data == dataPtr) // if data matches current node
				{
					previous->next = current->next; //set prev pointer next to current next
					deletedNode = *current->data;  
					delete current;
					current = NULL;
					previous = NULL;
					this->size--;
					return true;
				}
				previous = current;      //no match continue
				current = current->next;

			}

		}
	}
	//cout << "No matching data to remove" << endl;
	return false;
}


template <class Object>
bool list<Object>::retrieve(const Object& dataPtr) const {
	Object retrievedPtr = NULL;
	return retrieve(dataPtr, retrievedPtr);
}

//retrieve - retrieve an Object from sorted list
//		  
//PRE: Valid Object to be found is passed, an empty/non-empty Object is passed
//	   by reference so the Object found will be stored in this Object and referenced
//		from calling program
//POST: returns true(1) if value successfully found false(0) otherwise
//		stores the deletedobject in the passed object reference
template <class Object>
bool list<Object>::retrieve(const Object& dataPtr, Object& retrievedPtr) const {
	if (dataPtr == NULL) {  //if null object passed
		//cout << "Error: Object passed is NULL" << endl;
		return false;
	}
	if (isEmpty()) {  //if isempty
		//cout << "Error: Cannot retrieve from empty list!" << endl;
		return false;
	}
	if (*head->data == dataPtr) {  //if first node matches input
		if (retrievedPtr != NULL)		  //if not null object 
			retrievedPtr = *head->data;  //store head data to pass back 
		return true;
	}

	//traverse rest
	Node *current = head;   

	//traverse till reach the end of list and data not equal input
	while (current -> next != NULL && *current->data != dataPtr)
		current = current->next;
	 
	if (*current->data == dataPtr) { //if data found
			if (retrievedPtr != NULL)
				retrievedPtr = *current->data; //pass back
			return true;
	}
		 
	delete current;
	current = NULL;
	//cout << "No matching data to retrive!" << endl;
	return false;
}

//getSize - return size of list
//PRE - None
//POST - returns size
template <class Object>
int list<Object>::getSize() const {
	return this->size;
}

//merge - takes 2  sorted lists and merge into one sorted list and assigns the 
//			new sorted merged list as this list. The input lists will be emptied
//			Duplicates are allowed.
//PRE - None
//POST - merges the 2 lists passed and stores it into this list
template <class Object>
void list<Object>::merge(list<Object> &list1, list<Object> &list2) {
	if (list1.isEmpty() && list2.isEmpty())
	{
		cout << "Error: Both lists are empty. No action" << endl;
		return;
	}

	if (list1.isEmpty() && this != &list2) //if list1 is empty & not self reference
	{
		this->head = list2.head;  //this will be set as  list2
		list2.head = NULL;			//list2 is empty
		return;
	}
	if (list2.isEmpty() && this != &list1) //if list2 is empty & not self reference
	{
		this->head = list1.head;
		list1.head = NULL;
		return;
	}
	Node *newHead = NULL;
	Node *current = NULL;
	Node *list1ptr = list1.head; //traverse list1
	Node *list2ptr = list2.head; //traverse list2
	while (list2ptr != NULL)  //while list2 till end
	{
		 if (*list1ptr->data < *list2ptr->data) {  //compare values of list1 and list2 node
													//list1 < list2
			if (newHead == NULL) {					//if first iteration				
				newHead = list1ptr;					//set newhead to list1 
				current = list1ptr;					//current is list1
			}
			else {
				current->next = list1ptr;          //not first iteration, set current to list1
				current = list1ptr;
			}
			list1ptr = list1ptr->next;   //traverse list1
		}
		else {								//reverse previous logic to traverse list2
			if (newHead == NULL) {			//new head now points to list2
				newHead = list2ptr;
				current = list2ptr;
			}
			else {
				current->next = list2ptr;
				current = list2ptr;
			}
			list2ptr = list2ptr->next;   //traverse list2
		}

	}//end while
	if (newHead == NULL)           
		newHead = list1ptr;                 
	else
		current->next = list1ptr;

	 //lists are merged remove pointers

	if (this != &list1) //delete only if not self reference
	{
		list1.head = NULL;
	}

	if (this != &list2)
	{
		list2.head = NULL;
	}
	this->head = newHead;

 	if (this != &list1)
		list1.head = NULL;
	if (this != &list2)
		list2.head = NULL;
	cout << "ending" << endl;
}
 

template <class Object>
void list<Object>::makeEmpty() {
	if (!isEmpty())
		makeEmpty(*this);
}

//makeempty - clear this list
//PRE
//POST - list is emptied, head set to NULL
template <class Object>
void list<Object>::makeEmpty(list<Object>& other) const {
	if (isEmpty()) {
		cout << "Error: Cannot empty an empty list! " << endl;
		return;
	}
	
		Node* currentPtr = other.head; //traverse the list
		Node* nextPtr = other.head;
		//traverse list and delete each node
		while (currentPtr != NULL) {
			nextPtr = currentPtr->next;  //set next to next node
			delete currentPtr; //delete current node traversed
			currentPtr = nextPtr;
		}
		other.head = NULL;
		delete currentPtr;
		currentPtr = NULL;
		delete nextPtr;
		nextPtr = NULL;
	 
}

//Copy - copies every element in passed list to this list
//Pre - valid input
//Post - input list copied into this
template <class Object>
void list<Object>::copy(const list<Object>& other) {
	if (other.isEmpty()) {
		cout << "List passed is empty!" << endl;
		return;
	}
	 
	Node *current = other.head;
 
	//traverse each node of other and insert into this
	while (current != NULL)
	{
		insert(*current->data);
	 		
		current = current->next;

	}
	delete current;
	current = NULL;
}

//intersect - takes 2  sorted lists and finds common elements, clears this list and inserts
//			the common elements to this. The input lists will not be emptied
//			Duplicates are allowed.
//PRE - None
//POST - intersects the 2 lists passed and stores it into this list
template <class Object>
void list<Object>::intersect(const list <Object>&list1, const list<Object> &list2) {

	if (list1.isEmpty() || list2.isEmpty())
	{
		cout << "One/both list(s) are empty, no common items" << endl; //if either empty return empty set
		makeEmpty();
		return;
	}

	//traversal similar to merge algorithm 
	Node *newHead = NULL;
	Node *current = NULL;
	Node *list1ptr = list1.head;
	Node *list2ptr = list2.head;

	while (list2ptr != NULL)
	{
		if (*list1ptr->data < *list2ptr->data) {  
			Node* newNode = new Node; 
			newNode->data = list1ptr->data;

			if (newHead == NULL) {
				newHead = newNode;
				current = newNode;
			}
			else {
				current->next = newNode;
				current = newNode;
			}-
			list1ptr = list1ptr->next;   //traverse list1
		 	list2ptr = list2ptr->next;   //traverse list2
		}
		else if (*list1ptr->data < *list2ptr->data)
			list1ptr = list1ptr->next;
		else
			list2ptr = list2ptr->next;

	}//end while
	if (!isEmpty())
	{
		makeEmpty();
	}

	this->head = newHead;
	//cout << "endddd" << endl;
	list1ptr = NULL;
	list2ptr = NULL;
	current = NULL;
	newHead = NULL;	
	//cout << "endddd222" << endl;
}

template <class Object>
list<Object> list<Object>::operator +(const list<Object> &other) const {

	if (isEmpty() && other.isEmpty())
	{
		cout << "Error: Both lists are empty. No action" << endl;
		return *this;
	}

	list temp;
	if (other.isEmpty()) {
		temp.copy(*this);

	}
	else if (isEmpty())
	{
		temp.copy(other);
	}
	else {
		temp.copy(*this);
		Node *current = other.head;
		while (current != NULL)
		{
			temp.insert(*current->data);
			current = current->next;
		}
	}
	return temp;
}

template <class Object>
list<Object>& list<Object>::operator =(const list<Object> &other) {
	

	if (this == &other) // if trying to copy same lists
		return *this;

	if (!isEmpty())
		makeEmpty();

	Node *current = other.head;
	while (current != NULL)
	{
		insert(*current->data);
		current = current->next;

	}
 
	delete current;
	current = NULL;
	return *this;
}

template <class Object>
bool list<Object>::operator ==(const list<Object>& other)const {
	if (isEmpty() && other.isEmpty())
		return true;
	if (isEmpty() || other.isEmpty())
		return false;
	if (size != other.getSize())
		return false;
	Node *current = head;
	Node *otherCurrent = other.head;

	while (current != NULL) {
		if (current->data != otherCurrent->data)
			return false;
		current = current->next;
		otherCurrent = otherCurrent->next;
	}
	return true;
}

template <class Object>
bool list<Object>::operator !=(const list<Object>& other)const
{
	if (isEmpty() && other.isEmpty())
		return false;
	if (isEmpty() || other.isEmpty())
		return true;
	if (size != other.getSize())
		return true;
	Node *current = head;
	Node *otherCurrent = other.head;

	while (current != NULL) {
		if (current->data == otherCurrent->data)
		{
			current = current->next;
			otherCurrent = otherCurrent->next;
		}
		else
			return true;
	}
	return false;
}



 
#endif /* list_hpp */
#pragma once
#pragma once
