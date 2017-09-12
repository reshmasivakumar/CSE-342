/*
Program 4: PixelContainer.cpp
Author: Reshma Maduri Sivakumar
Design Due Date: 03/08/2017

Purpose:			Purpose: This is a container class for storing a set of image pixels and
					additional support information related to the pixels such as the list size, 
					seed pixel, count of all pixels RGB values (redpixelcount, greenpixelcount 
					and bluepixelcount). The container class is implemented as linked list which 
					has data members as 
						- struct PixelNode {    
							 NodeData* data; // pointer to Node data(pixel) class
							 PixelNode *next;
						  }
			
						- head which is pointer of type PixelNode  //head of the list
						- seed which is type pixel
						- size which int value to store the size of the list(container)
						- redPixelCount, greenPixelCount, bluePixelCount which are int values that 
						  store the pixel counts of all RGB color values in all the nodes of the list.

					The container class implements the following member operations: 
						- constructor and copy constructor
						- overloaded operators =, ==, !=, <<
						- destructor which deallocates the list 
						- methods to create new node in the list and add an existing node to list
					    - merge a given list to the list.
						- set and get the seed pixel
						- methods that returns the average of the RGB color values of all the 
						  pixels in the list.


*/

#include "ImageLib.h"
#include "Image.h"
#include "PixelContainer.h"
#include "NodeData.h"
#include <iostream>
 
/*
PixelContainer:		Default Constructor that constructs a
					PixelContainer object with a dummy head
					node and other data members: seed and size
				    set to default values.
						
Precondition:		Must be valid integer values for the 
					data members, seed and size.

Postcondition:		A PixelContainer object is created with default
					values:
					1) seed: The pixel's row, col, red, green and blue values 
							 are all set to 0.
					2) size: Size is set to 0 as the list is still empty.
					3) head: the head node is set to NULL.

*/

PixelContainer::PixelContainer() {
	head = new NodeData;
	head->setNext(NULL);
	this->size = 0;
	// To mark this as an unused seed
	this->seed = { 0,0,0 };
}

/*
PixelContainer:		Copy constructor that calls the private function
					copy to construct a PixelContainer object with
					its data members copied from other PixelContainer object.
					The copy function traverses through the other list and copies the nodes
					to this list and thus creating a copy. Size is set to
					the size of other and the values for the seed pixel are
					copied from other.

Precondition:		Other should not be an empty list. Must have valid integer
					values for seed pixel.

Postcondition:		A PielContainer object is created with its data members copied  
*/
PixelContainer::PixelContainer(const PixelContainer& other) {
	this->size = 0;
	copy(other);
}

/*
Operator= :			The assignment constructor is overloaded to copy all the nodes 
					other data members of other to this object. It does so by
					checking for self assignment and if not, calls deleteContainer()
					to delete the pre existing container in this linkedlist (if any)
					and calls copy() to copy all the nodes to this. Then, it copies
					all the values from seed pixel of other object to the seed pixel
					of this object.

Precondition:		Other should have valid values for its data members. 

PostCondition:	    Operator return *this if the opeator is called on this object. Otherwise,
					calls deleteContainer() to delete the contents of this list and copies the
					linkedlist and seed pixel from other to this object.
*/

PixelContainer& PixelContainer::operator=(const PixelContainer& other) {
	if (*this != other) {
		
		deleteContainer();
		copy(other);
	}
	return *this;
}

/*
Operator<<:			The cout operator is overloaded to print the following to the console:
					The total size of the list and the average 
					color values of the pixel group.

Precondition:		Valid values for the data members in other object.

Postcondition:		Prints to console the other object's seed pixel's row and column, 
					the total size of the other object's list and the average color values
					of the pixel group.
*/

ostream& operator<<(ostream& out, const PixelContainer& other) {
	cout << "Number of pixels " << other.getSize()  << endl;
	cout << "Average Red color " << other.getRedAverageColor() << endl;
	cout << "Average Blue color " << other.getBlueAverageColor() << endl;
	cout << "Average Green color " << other.getGreenAverageColor() << endl;
	int avgColor = other.getRedAverageColor() + other.getBlueAverageColor() + other.getGreenAverageColor();
	cout << "Average color " << avgColor << endl;

 	return out;
}

/*
Operator==:			The equal to operator is overloaded to check if all the
					data members of this object is equal that in other object.
					The operator traverses through the other's list and checks if '
					every single node is equal to the list in this object. The function
					also checks if the the other seed pixel's row, col and RGB values
					are similiar to this object's seed pixel.

Precondition:		Valid values for the other objects data members.

Postcondition:		Returns true of both objects are equal. Returns false if not.
*/


bool PixelContainer::operator==(const PixelContainer& other)const{
	if (this->size != other.size)
		return false;
	if (this->size == 0 && other.size == 0)
		return true;
	if (this->size == 0 || other.size == 0)
		return false;
	if (this->seed.blue != other.getSeed().blue ||
		this->seed.red != other.getSeed().red || 
		this->seed.green != other.getSeed().green  )
		return false;
	if (this->getRedAverageColor() != other.getRedAverageColor() ||
		this->getGreenAverageColor() != other.getGreenAverageColor() ||
		this->getBlueAverageColor() != other.getBlueAverageColor())
		return false;
	else {
		NodeData *current = head;
		NodeData *otherCurrent = other.head;

		while (current != NULL) {
			if (current != otherCurrent)
				return false;
			current = current->getNext();
			otherCurrent = otherCurrent->getNext();
		}
		delete current;
		delete otherCurrent;
		current = NULL;
		otherCurrent = NULL;
		return true;
	}
}

/*
Operator!=:				The not equal to operator is overloaded to call the operator==
						and return the !(not).

Precondition:			Valid values for the other objects data members.

Postcondition:			Returns true if both the objects are not equal, and false if they are.
*/

bool PixelContainer::operator!=(const PixelContainer& other)const
{
	return !(*this == other);
}

/*
createPixelNode:		The createPixelNode() creates a new node and sets its data to the the other
						pixel object and adds the node to this object's linkedlist. The new node is
						added to the begining of the list and hence the head is set to this newly
						created node. The method also increments the redPixelCount, greenPixelCount
						and bluePixelCount when each node is added. The size of the linked list increments
						by one when each node is added.

Precondition:			The pixel object cannot be NULL and valid integer data for row and col.

Postcondition:			A new node is created and added to this linkedlist. Head is set to the newly
						created node. The size is incremented by 1 and sums the redPixelCount,
						bluePixelCount and greenPixelCount.
*/

void PixelContainer::createPixelNode(const pixel& other, int row, int col)
{
	 
	NodeData* newNode = new NodeData();
 	int red = other.red;
	int blue = other.blue;
	int green = other.green;
	pixel newPixel = { red, green, blue };

 	newNode->setData(newPixel, row, col);
 	
	if (this->head == nullptr) {
		head = newNode;
		head->setNext(NULL);
		this->size=1;
 
	}
	else {
		newNode->setNext( this->head);
		this->head = newNode;
		this->size++;
	
	}
	
	this->redPixelCount += other.red;
	this->greenPixelCount += other.green;
	this->bluePixelCount += other.blue;

}

/*
addPixelNode:			This method creates a new node and copies the rgb values and 
						the row and col from the other pixelNode and computes the sum of redPixelCount,
						greenPixelCount and bluePixelCount. This new node is added to the beginning
						of the list.

Precondition:			other cannot be null and must have valid values for row and col.

Postcondition:			A new pixel node is created with values copied from other and is added
						to the begininng of this list. The size and redPixelCount,
						bluePixelCount and greenPixelCount values are updated.
					
*/

void PixelContainer::addPixelNode(const NodeData* other)
{
	//cout << "Inside addPixelNode" <<  endl;
	if (other ==nullptr )
		return;
	NodeData* newNode = new NodeData;
	 //get data of other node
	pixel newPixel = other->getNodeData();
	int row = other->getRow();
	int col = other->getCol();
	//create instance of newNodeData 
	NodeData* newNodeData = new NodeData();
	newNodeData->setData(newPixel, row, col);
	newNode = newNodeData;
	//set new node to head if first node
	if (this->getSize() == 0) {
		head = newNode;
		newNode->setNext(NULL);
	}
	else {
		//add node to list with next as head
		newNode->setNext(this->head);
		this->head = newNode;
	}

	this->size++;
	//increment pixelcounts
	this->redPixelCount += other->getRedPixel();
	this->greenPixelCount += other->getGreenPixel();
	this->bluePixelCount += other->getBluePixel();
 }

/*
setSeed():				Setter method that sets otherSeed pixel to this seed pixel and all 
						the RGB values, rows and cols are also set.

Precondition:			The passed pixel cannot be NULL and must have valid values for the RGB
						values and the row and col. 

Postcondition:			Sets the seed pixel to otherSeed.
*/

void PixelContainer::setSeed(const pixel& otherSeed) {
	this->seed = otherSeed;
}

/*
getSize:				getSize returns the size of this pixel group (linkedlist).

Precondition:			None.

PostCondition:			Returns the value of this->size.
*/
int PixelContainer::getSize() const {
	return this->size;
}

/*
getSeed:				getSeed returns the seed pixel of this object.

Precondition:			None.

PostCondition:			Returns the value of this->seed.

*/

pixel PixelContainer::getSeed() const {
	return this->seed;
}

/*
getRedAverageColor:		getRedAverageColor computes the average of red pixel color
						by dividing the redPixelCount instance variable by size of the pixel group.

Precondition:			Size cannot be zero as it will result in divide by zero error.

PostCondition:			Computes and returns the average red pixel color value.

*/

int PixelContainer::getRedAverageColor() const {
	int averageRed = redPixelCount / size;
	return averageRed;
}

/*
getBlueAverageColor:		getBlueAverageColor computes the average of blue pixel color
							by dividing the bluePixelCount instance variable by size of the pixel group.

Precondition:				Size cannot be zero as it will result in divide by zero error.

PostCondition:				Computes and returns the average blue pixel color value.

*/

int PixelContainer::getBlueAverageColor() const {
	int averageBlue = bluePixelCount / size;
	return averageBlue;
}

/*
getGreenAverageColor:		getGreenAverageColor computes the average of green pixel color
							by dividing the greenPixelCount instance variable by size of the pixel group.

Precondition:				Size cannot be zero as it will result in divide by zero error.

PostCondition:				Computes and returns the average green pixel color value.

*/

int PixelContainer::getGreenAverageColor() const {
	int averageGreen = greenPixelCount / size;
	return averageGreen;
}

/*
merge:				The merge method adds the nodes from other object's list by calling
					the addPixelNode method and merges the other objects list to this. 

Preconditions:		Both lists cannot be empty and cannot merge itself.

Poatconditions:		All the nodes from other is added to the end of this list.
					The size and the redPixelCount, bluePixelCount and greenPixelCount
					sums are updated to this. 
*/

void PixelContainer::merge(const PixelContainer& other) {
 
	if (this->size == 0 && other.size == 0)
	{
		cout << "Error: Both lists are empty. No action" << endl;
		return;
	}

	if (this->size == 0) {
		copy(other);
	}

	else
	{
		NodeData* current = other.head;
		while (current != NULL)
		{
			addPixelNode(current);
			current = current->getNext();
		}
	}
	 
//cout << "leaving merge " << endl;
}

/*
deleteContainer():		The delete container method traverses through this list and 
						deletes every node until the list is empty.

Precondition:			List cannot be null

Postcondition:			Safely deletes the nodes in this linked list.
*/
void PixelContainer::deleteContainer() {
	 
 	if (this->size == 0)
		return;
	NodeData *current = this->head;
	
	while (current != NULL) {
		head = head->getNext();
		delete current;
		current = head;
	}
	delete current;
	
	current = NULL;
	 
	size = 0;
	seed.blue = 0;
	seed.green = 0;
	seed.red = 0;
	redPixelCount = 0;
	greenPixelCount = 0;
	bluePixelCount = 0;
 
}

/*
Copy:				The private copy method calls addPixelNode to copy the contents
					of other objects likedlist to this. Te addPixelNode method increments
					the size of the list and the redPixelCount, bluePixelCount and greenPixelCount
					values. 

Precondition:		Cannot be an empty list and cannot copy if the method is called on itself.

Postcondition:		All the nodes from other object is copied to this and the method jsut returns
					and does nothing if the copy method is called on itself.
*/

void PixelContainer::copy(const PixelContainer& other) {
	
	if (other.size == 0) {
		cout << "List passed is empty!" << endl;
		return;
	}
	if (this == &other) // if trying to copy same lists
		return; 
	NodeData *current = other.head;
	while (current != NULL)
	{
 		addPixelNode(current);
 		current = current->getNext();
 	}
	 
 }

/*
getNextData():   This method is used to get pixel data the head points to, and the row and col stored 
                  with the data. The head is set to point to next.
The method takes the  pixel variable and row and col as reference input variables and returns the
pixel data of the head node. The head read of the  list and head is set to next node


Precondition: Three valid  reference variables to return back the  color pixel values of red, ble and green pixels and
int reference variables for row and col
Postcondition: The head node is read from the list and the pixel data in the head node is returned . The input reference variables
are set to the row and col stored with the pixel data in the head node.


*/
 
void PixelContainer::getNextData(pixel& pixel, int& row, int& col)
{
	NodeData *current = head;
 	if (current != NULL)
	{
		pixel = current->getNodeData();
 		row = current->getRow();
		col = current->getCol();
		head = current->getNext();
	 
	}
 	current = NULL;
}

/*
~PixelContainer:		Destructor that calls deletContainer() to safely delete this linked list
						and deletes the head node.

Precondition:			None.

Postcondition:			All the nodes in this linked list are deleted and this->head is also deleted. 
*/

PixelContainer::~PixelContainer() {
	deleteContainer();
}

 
