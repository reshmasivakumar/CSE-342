 
/*
	Program 3: Rectangle.cpp
	Author: Reshma Maduri Sivakumar
	Due Date: 02/10/2017

	Purpose: Image class that implements Rectangle.h and creates an Rectangle object 
			 with dimensions of the Rectangle object as instance variables.
			  
			The class implements constructors, accessors, mutator(s), operator<<,
			operator==, operator!= and other methods in the header file.

*/


#include "Rectangle.h"
#include <iostream>

using namespace std;


/*
	Rectangle:	Constructor that creates a Rectangle object with default
			dimensions.

	Preconditions: None

	Postconditions:	A Rectangle object is created with top right and bottom
					left dimensions as (0,1) and (1,0) and height =2 and width=2
*/


Rectangle::Rectangle()
{
	topIndexes.x = 0, topIndexes.y = 1, bottomIndexes.x =1, bottomIndexes.y = 0, width = 2, height =2;
}

/*
	Rectangle:	Constructor that takes as input the top right, bottom left, height
				and width dimensions to create a Rectangle object.

	Preconditions: Input values must be greater than 0.

	Postconditions:	A Rectangle object is created with top right and bottom
					left dimensions as (0,1) and (1,0) and height =2 and width=2
*/


Rectangle::Rectangle(int topLeftRowIndex, int topLeftColIndex, int rows, int columns)
{
	if (topLeftRowIndex < 0 || topLeftColIndex < 0 || rows < 0 || columns < 0)
		throw exception("Invalid dimensions. Dimensions cannot be negative.");

	//set top right indexes of this object
	topIndexes.x = topLeftRowIndex;
	topIndexes.y = topLeftColIndex;

	width = columns;
	height = rows;
	//set bottom left indexes
	bottomIndexes.x = topLeftRowIndex + (height - 1);
	bottomIndexes.y = (topLeftColIndex + 1) - width;
		 
}

/*
operator<< :		cout has been overloaded to output the this Rectangle's
					dimensions - topleft (x,y) and bottomright(x,y)
btt
Precondition:		None.

Postcondition:		Outputs to console the values this Rectangle's
					dimensions - topleft (x,y) and bottomright(x,y)

*/

 ostream& operator<<(ostream& output, const Rectangle& Rect)
{
	cout << "{TopRightRow, TopRightCol} = {"
		<< Rect.getStartRowIndex() << ", " << Rect.getStartColIndex() << "}" << endl;

	cout << "{BottomLeftRow, BottomLeftCol} = {"
		<< Rect.getbottomRowIndex() << ", " << Rect.getbottomColIndex() << "}" << endl;

	cout << "{Height, Width} = {" << Rect.getHeight() << ", " << Rect.getWidth() << "}"
		<< endl;

	return output;
}

 /*
	Operator== :      The equal to operator is overloaded to check if the
				Rectangle object passed is equal to this object. The
				objects are compared based on the topleft and bottom
				right indexes and the height and width.

	Preconditions:	  otherRectangle and the instance object must have the
					same dimensions.

	Postconditions:   Returns false if the dimensions are not the same between
					otherRectangle and the instance object.
					Returns true if the dimensions match.
 */

 bool Rectangle::operator == (const Rectangle& otherRectangle) const {
	 if (otherRectangle.getStartRowIndex() == otherRectangle.getStartColIndex()
		 && otherRectangle.getbottomRowIndex() == otherRectangle.getbottomRowIndex()
		 && otherRectangle.getHeight() == otherRectangle.getHeight()
		 && otherRectangle.getWidth() == otherRectangle.getWidth())
		 return true;

	 else
		 return false;
 }


 /*
	 operator!= :    The not equal to operator is over loaded to check the
					inequality of the call theRectangle object passed is equal
					to this object.

	 Preconditions:	 otherRectangle and the instance object must not have the
					same dimensions.

	 Postconditions:  Returns true if the dimensions are not the same between
					 otherRectangle and the instance object.
					Returns false if the dimensions are the same.
 */

 bool Rectangle::operator != (const Rectangle& otherRectangle) const {
	 return !(*this == otherRectangle);

 }

/*
	 getStartRowIndex: Accessor method that returns the top right row index x

	Preconditions:	None

	Postconditions:	Returns value for top right rowIndex of this Rectangle.
*/

const int Rectangle::getStartRowIndex() const
{
	return topIndexes.x;
}

/*
	getStartColIndex: Accessor method that returns the top right col index y

	Preconditions:	None

	Postconditions:	Returns value for top right colIndex of this Rectangle.
*/

const int Rectangle::getStartColIndex() const
{
	return topIndexes.y;
}


/*
	getbottomRowIndex: Accessor method that returns the bottom left row
						index of this Rectangle object.

	Preconditions:	Rectangle object must be created and bottom left row
					index set to a positive value

	Postconditions:	Returns bottom left col index as const integer.
*/
  
const int Rectangle::getbottomRowIndex() const
{
	return bottomIndexes.x;
}

/*
	getbottomColIndex: Accessor method that returns the bottom left col index y

	Preconditions:	None

	Postconditions:	Returns value for bottom left colIndex of this Rectangle.
*/

const int Rectangle::getbottomColIndex() const
{
	return bottomIndexes.y;
}


/*
	getHeight: Accessor method that returns the height of this Rectangle object.

	Preconditions:	Rectangle object must be created and height set

	Postconditions:	Returns height as const integer.
*/

const int Rectangle::getHeight() const
{
	return height;
}

/*
	getWidth: Accessor method that returns the width of this Rectangle object.

	Preconditions:	Rectangle object must be created and width set to
				positive value

	Postconditions:	Returns width as const integer.
*/

const int Rectangle::getWidth() const
{
	return width;
}

  
/*
	setStartRowIndex: Mutator method that takes an int and sets the
					top right row index of this object.

	Preconditions:	 int passed should be positive integer.

	Postconditions:	Sets the top right row index of this object.
*/
void Rectangle::setStartRowIndex(int newRowIndex)
{
	if (newRowIndex < 0)
		throw exception("Invalid dimensions. Dimensions cannot be negative.");

	topIndexes.x = newRowIndex;
}

/*
	setStartColIndex: Mutator method that takes an int and sets the
					  top right col index of this object.

	Preconditions:	 int passed should be positive integer.

	Postconditions:	Sets the top right col index of this object.
*/

void Rectangle::setStartColIndex(int newColIndex)
{
	if (newColIndex < 0)
		throw exception("Invalid dimensions. Dimensions cannot be negative.");

	topIndexes.y = newColIndex;
}


/*
	setbottomRowIndex : Mutator method that sets the bottom left row index based on
						top right row index and the height of the instance object

	Preconditions:	   The top right row index and the height should exist for this
					 value to be calculated.

	Postconditions:     Sets the bottom left row index for this object.
*/
void Rectangle::setbottomRowIndex( )
{
	 
	bottomIndexes.x = getStartRowIndex() + (height - 1);
}

/*
	setbottomColIndex : Mutator method that sets the bottom left col index based on
						top right col index and the width of the instance object

	Preconditions:	   The top right col index and the width should exist for this
						value to be calculated.

	Postconditions:     Sets the bottom left col index for this object.
*/


void Rectangle::setbottomColIndex( )
{
	bottomIndexes.y =  getStartColIndex() - width + 1;
}

/*
	setHeight:		Mutator that takes an integer and sets the height of
					this object.

	Preconditions:	int passed should be positive integer.

	Postconditions:	Sets value of height for this object.
*/

void Rectangle::setHeight(int newHeight)
{
	if (newHeight < 0)
		throw exception("Invalid dimensions. Dimensions cannot be negative.");

	height = newHeight;
}

/*
	setWidth:		Mutator that takes an integer and sets the width of
				this object.

	Preconditions:	int passed should be positive integer.

	Postconditions:	Sets value of width for this object.
*/
void Rectangle::setWidth(int newWidth)
{
	if (newWidth < 0)
		throw exception("Invalid dimensions. Dimensions cannot be negative.");


	width = newWidth;
}


  