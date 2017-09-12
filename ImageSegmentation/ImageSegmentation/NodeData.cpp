/*
Program 4: NodeData.cpp
Author: Reshma Maduri Sivakumar
Design Due Date: 03/08/2017

Purpose:  This program contains the implementation of the methods in the NodeData header file.

*/

#include "NodeData.h"
#include <iostream>
#include <fstream>

using namespace std;

/*
NodeData:		A default constructor with its data members, pixels, row and col
				set to default values.
				pixel: The red, green and blue values of pixel is set to 0.
				row: Row is set to default location at 0.
				col: Col is set to default location at 0.

Precondition:	Valid integer values for the pixels RGB values, row and col.

Postcondition:	A nodedata object is created with the instance variable pixel's
				red, blue and green color values set to 0. The row and col is
				also set to 0.
*/

NodeData::NodeData() {
	 pdata.red = 0;
	 pdata.blue = 0;
	 pdata.green = 0;
	 row = 0;
	col = 0;
	next = NULL;
}

/*
NodeData:			A copy constructor to construct a NodeData object with
					its data members' values copied from the other NodeData
					object.The pixel's red, blue and green values are set to
					the other object pixel's red blue and green values. The
					row and col values are copied from other object's row and col.

Precondition:		Other pixel cannot be null and must have valid values for for
					row and col.

Postcondition:		A NodeData object is constructed with its data members copied from
					the other NodeData object. 

*/

NodeData::NodeData(const NodeData& other) {
	int red = other.pdata.red;
	int blue = other.pdata.blue;
	int green = other.pdata.green;
	this->pdata.red = red;
	this->pdata.blue = blue;
	this->pdata.green = green;
	this->row = other.row;
	this->col = other.col;
	this->next = NULL;
}

/*
operator=:			The assignment operator is overloaded to assign all the data
					member values from other NodeData object to this. The operator
					checks for self assignment before assigning the values.

Precondition:		All data member values in other object must have valid integer 
					values.

Postcondition:		All the values from the other is assigned to this.
*/

NodeData& NodeData::operator=(const NodeData other) {
	if (*this != other) {
		this->pdata.red = other.pdata.red;
		this->pdata.blue = other.pdata.blue;
		this->pdata.green = other.pdata.green;
		this->row = other.row;
		this->col = other.col;
		this->next = other.next;
	}
	return *this;
}

/*
operator==:			The equal to operator is overloaded to check if all the
					data members of this object is equal to the data members of
					the other object. Operator checks if pixel's red, blue and 
					green values are the same as the other pixel and also	
					checks if the row and col are the same in both objects.

Precondition:		Valid values for the other objects data members.

Postcondition:		Returns true of both objects are equal. Returns false if not.
*/

bool NodeData::operator==(const NodeData& other)const {
	if (this->pdata.red != other.pdata.red ||
		this->pdata.blue != other.pdata.blue ||
		this->pdata.green != other.pdata.green)
		return false;
	if (this->row != other.row ||this->col != other.col)
		return false;
	else
		return true;
}

/*
Operator!=:				The not equal to operator is overloaded to call the operator==
						and return the !(not).

Precondition:			Valid values for the other objects data members.

Postcondition:			Returns true if both the objects are not equal, and false if they are.
*/
bool NodeData::operator!=(const NodeData& other)const {
	return !(NodeData::operator==(other));
}

/*
setData:		Sets the node pixel data to the input pixel and the
row and col to the row and col passed. This represents the node
data in the LinkedList class

Precondition:	Valid pixel data, row and col with values greater than equal to 0

Postcondition:  The input pixel will be set as the pixel data along with the row and col
values as input row and col values.
*/
void NodeData::setData(const pixel& otherPixel, int otherRow, int otherCol) {
	if (otherRow < 0 || otherCol < 0)
		return;
	if (otherPixel.red < 0 || otherPixel.red > 255 ||
		otherPixel.green < 0 || otherPixel.green > 255 ||
		otherPixel.blue < 0 || otherPixel.blue > 255)
		return;
	int red = otherPixel.red;
	int blue = otherPixel.blue;
	int green = otherPixel.green;
	pdata.red = red;
	pdata.green = green;
	pdata.blue = blue;
	this->row = otherRow;
	this->col = otherCol;

 }

/*
setNext:		Sets the next pointer of this object to point to the input object.

Precondition:	Valid NodeData object

Postcondition:  next pointer object of this will be set to point to the object passed.
*/

void NodeData::setNext(NodeData *other) {
	  		this->next = other ;
}

/*
getNext():	Returns the pointer to the object that next pointer points to

Precondition:	None

Postcondition:	Returns the pointer to the object that next pointer points to
*/
NodeData* NodeData::getNext() const {
	return this->next;
}

/*
getRedPixel:			The getRedPixel method returns the pixel's red component.

Precondition:			Pixel should have valid RGB values.

Postcondition:			Returns the red value of this pixel object.
*/

int NodeData::getRedPixel() const{
	return this->pdata.red;
}

/*
getBluePixel:			The getBluePixel method returns the pixel's blue component.

Precondition:			Pixel should have valid RGB values.

Postcondition:			Returns the blue value of this pixel object.
*/

int NodeData::getBluePixel() const{
	return this->pdata.blue;
}


/*
getGreenPixel:			The getGreenPixel method returns the pixel's green component.

Precondition:			Pixel should have valid RGB values.

Postcondition:			Returns the green value of this pixel object.
*/

int NodeData::getGreenPixel() const{
	return this->pdata.green;
}

/*
getRow:					The getRow method returns the row value of this object

Precondition:			The row value must be a positive value.

Postcondition:			Returns the value at this->row.
*/

int NodeData::getRow() const {
	return this->row;
}


/*
getCol:					The getCol method returns the col value of this object

Precondition:			The col value must be a positive value.

Postcondition:			Returns the value at this->col.
*/

int NodeData::getCol() const {
	return this->col;
}

/*
getNodeData():	Returns the pixel object stored as node data

Precondition:	None

Postcondition:	Returns pixel object stored
*/
pixel NodeData::getNodeData() const
{

	return this->pdata;
}

/*
~NodeData() :	Destructor of NodeData object

Precondition:	None

Postcondition:	None
*/
NodeData::~NodeData() {
 	next = NULL;
	 
}

