//
//  list.cpp
//  Assignment_3
//
//  Created by Reshma Maduri on 10/22/16.
//  Copyright � 2016 Reshma Sivakumar. All rights reserved.
//

#include "stdafx.h"
#ifndef list_cpp_
#define list_cpp_	

 /*

template <class Object>
list<Object>::list() {
	head = NULL;
	this->size = 0;
}

template <class Object>
list<Object>::list(const list<Object> &other) {
	if (!other.isEmpty())
	{
		copy(other);
	}
	else
	{
		cout << "Empty object list passed" << endl;
	}

}

template <class Object>
list<Object> :: ~list() {
	//makeEmpty ();

}

template <class Object>
void list<Object>::buildList(ifstream& infile) {
	Object* ptr;
	//bool success;
	//bool successfulRead;

	if (!infile) {
		cout << "File could not be opened" << endl;
		exit(0);
	}

 	while (!infile.eof()) {
		ptr = new Object;
		bool success = ptr->setData(infile);
		if (infile.eof()) {
			delete ptr;
			break;
		}
		if (success) {
			if (!insert(*ptr)) {
				delete ptr;
				break;
			}

		}
		else
		{
			delete ptr;
			break;
		}


	}
	infile.close();
}


bool list::isEmpty() const {
	return (head == NULL);
}

bool list::insert(nodedata& dataPtr) {
	Node* ptr = new Node;
	if (ptr == NULL) return false;     //check for out of memory

	ptr->data = &dataPtr;
	if (!ptr->data)        //check if input reference has valid data
		return false;
	this->size++;
	

	if (isEmpty() || *ptr->data < *this->head->data) { //if empty or less than head
		ptr->next = head;
		head = ptr;
	}
	else {
		Node* current = head->next;
		Node* previous = head;

		while (current != NULL && *current->data < *ptr->data) {
			previous = current;
			current = current->next;
		}
		ptr->next = current;
		previous->next = ptr;

	}
	return true;
}
 
bool list::remove(const nodedata& dataPtr) {
	nodedata *deletedPtr = NULL;
	return remove(dataPtr, deletedPtr);

}

bool list::remove(const nodedata& dataPtr, nodedata*& deletedNode) {
	if (isEmpty()) {

		return false;
	}

	if (head->next == NULL && *head->data == dataPtr) {
		deletedNode = head->data;
		delete head;
		head = NULL;
		this->size--;
		return true;
	}
	else {
		Node* current = head;
		Node* previous = head;

		if (*current->data == dataPtr) // check if first node to delete
		{

			head = current->next;
			deletedNode = current->data;
			delete current;
			current = NULL;
			previous = NULL;
			this->size--;
			return true;
		}
		else {
			while (current != NULL) {
				if (*current->data == dataPtr)
				{
					previous->next = current->next;
					deletedNode = current->data;
					delete current;
					current = NULL;
					previous = NULL;
					this->size--;
					return true;
				}
				previous = current;
				current = current->next;

			}

		}
	}
	//cout << "No matching data to remove" << endl;
	return false;
}

bool list::retrieve(const nodedata& dataPtr) const {
	nodedata *retrievedPtr = NULL;
	return retrieve(dataPtr, retrievedPtr);
}

bool list::retrieve(const nodedata& dataPtr, nodedata*& retrievedPtr) const {
	if (dataPtr == NULL) {
		cout << "Error: Object passed is NULL" << endl;
		return false;
	}
	if (isEmpty()) {
		cout << "Error: Cannot retrieve from empty list!" << endl;
		return false;
	}
	if (this->size == 1 || *head->data == dataPtr) {
		if (retrievedPtr != NULL)
			retrievedPtr = head->data;
		return true;
	}
	Node *current = head;
	while (current != NULL) {
		if (*current->data == dataPtr) {
			if (retrievedPtr != NULL)
				retrievedPtr = current->data;
			return true;
		}
		current = current->next;
	}
	delete current;
	current = NULL;
	//cout << "No matching data to retrive!" << endl;
	return false;
}

int list::getSize() const {
	return this->size;
}

template <class Object>
void list<Object>::merge(list<Object> &list1, list<Object> &list2) {
if (list1.isEmpty() && list2.isEmpty())
{
cout << "Error: Both lists are empty. No action" << endl;
return;
}


if (list1.isEmpty()) {

copy(list2);

}
else if (list2.isEmpty()) {

copy(list1);

}
else
{

copy(list1);
Node* current = list2.head;
while (current != NULL)
{
insert(*current->data);
current = current->next;
}


}
if ( this != &list1)  //check if list1 is not self
makeEmpty(list1); // if so empty list1
if (this != &list2) //check if list2 is not self
makeEmpty(list2);//if so empty list2

}

void list::intersect(const list &list1, const list &list2) {

	if (list1.isEmpty() || list2.isEmpty())
	{
		cout << "One/both list(s) are empty, no common items" << endl; //if either empty return empty set
		makeEmpty();
	}

	Node *current;
	if (this != &list1 && this != &list2) //if not same list passed
	{
		makeEmpty();                       //clear this list
		copy(list1);                       //copy contents of list1
	}

	current = head;
	while (current != NULL) {
		cout << *current->data << endl;
//		if (!list2.retrieve(*current->data)) //check if contents of list1 in list2
	//		remove(*current->data);          //remove if found
		current = current->next;
	}
	delete current;
	current = NULL;


}

void list::copy(const list& other) {
	if (other.isEmpty()) {
		cout << "List passed is empty!" << endl;
		return;
	}

	if (this == &other) // if trying to copy same lists
		return;

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
}

void list::makeEmpty(list& other) const {
	if (isEmpty()) {
		cout << "Error: Cannot empty an empty list! " << endl;
		exit(0);
	}
	if (this != &other) {

		Node* currentPtr = other.head;
		Node* nextPtr = other.head;
		while (currentPtr != NULL) {
			nextPtr = currentPtr->next;
			delete currentPtr;
			currentPtr = nextPtr;
		}
		other.head = NULL;
	}
}

void list::makeEmpty() {
	if (!isEmpty())
		makeEmpty(*this);
}


template <class Object>
ostream& operator <<(ostream& out, const list<Object>& list) {
	list<Object>::Node* current = list.head;
	while (current != NULL) {
		out << *current->data;
		current = current->next;
	}
	out << endl;
	return out;
}



list list::operator +(const list &other) const {

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

list& list::operator =(const list &list1) {
	copy(list1);
	return *this;
}

bool list::operator ==(const list& other)const {
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


bool list::operator !=(const list& other)const {
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
}*/
#endif