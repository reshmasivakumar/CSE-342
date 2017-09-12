#pragma once

/*
Program 3: Rectangle.h
Author: Reshma Maduri Sivakumar
Due Date: 02/10/2017

Purpose: Creates an Rectangle  class that represents
         a rectanlge which stores the boundary locations i.e.
		 top right indexes (x,y) and the bottom left indexes are
		 stored. The class also stores the height and width of the
	     Rectangle.
         There is no dynamic memory allocated in this class, hence default
		 copy constructor, destructor and assignment operator = is used.
		 The class has constructors, accessors, mutator(s), operator<<, 
		 operator==, operator!=
 
*/
 
#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

#include <iostream>
using namespace std;

class Rectangle
{
	friend ostream& operator<<(ostream&, const Rectangle&);
 
	private:
		struct point {
			int x;
			int y;
		};
	 
	point topIndexes; //top right (x,y)
	point bottomIndexes;  //bottom left (x,y)
	 
	int height; //height of the area
	int width;  //width of the area

	public:

		/*
		Rectangle:	Constructor that creates a Rectangle object with default
					dimensions.

		Preconditions: None

		Postconditions:	A Rectangle object is created with top right and bottom 
		               left dimensions as (0,1) and (1,0) and height =2 and width=2
		*/

 		Rectangle();

		/*
			Rectangle:	Constructor that takes as input the top right, bottom left, height
						and width dimensions to create a Rectangle object.
		            
			Preconditions: Input values must be greater than 0.

			Postconditions:	A Rectangle object is created with top right and bottom
							left dimensions as (0,1) and (1,0) and height =2 and width=2
		*/

		Rectangle(int topRowIndex, int topColIndex, int height, int width);

		/*
			setbottomRowIndex : Mutator method that sets the bottom left row index based on
		                    top right row index and the height of the instance object
						 
			Preconditions:	   The top right row index and the height should exist for this
		                    value to be calculated.

			Postconditions:     Sets the bottom left row index for this object.
		*/

		void setbottomRowIndex();

		/*
			setbottomColIndex : Mutator method that sets the bottom left col index based on
								top right col index and the width of the instance object
		 
			Preconditions:	   The top right col index and the width should exist for this
								value to be calculated.

			Postconditions:     Sets the bottom left col index for this object.
		*/

		void setbottomColIndex();

		/*
		Operator== :      The equal to operator is overloaded to check if the 
						  Rectangle object passed is equal to this object. The
						  objects are compared based on the top right and bottom 
						   left indexes and the height and width.

		Preconditions:	  otherRectangle and the instance object must have the
						   same dimensions.

		Postconditions:   Returns false if the dimensions are not the same between
						  otherRectangle and the instance object.
						   Returns true if the dimensions match.
		*/

		bool operator == (const Rectangle& otherRectangle) const;


		/*
		operator!= :     The not equal to operator is over loaded to check the 
						 inequality of the call theRectangle object passed is equal
						 to this object.
		
		Preconditions:	 otherRectangle and the instance object must not have the
						  same dimensions.

		Postconditions:  Returns true if the dimensions are not the same between
						 otherRectangle and the instance object.
						 Returns false if the dimensions are the same.
		*/

		bool operator != (const Rectangle& otheRectangle) const;

 		/*
		  getHeight: Accessor method that returns the height of this Rectangle object.
		 
		  Preconditions:	Rectangle object must be created and height set 
		 
		  Postconditions:	Returns height as const integer.
		*/

		const int  getHeight() const;

		/*
		  getWidth: Accessor method that returns the width of this Rectangle object.
		
		  Preconditions:	Rectangle object must be created and width set to 
							positive value

		  Postconditions:	Returns width as const integer.
		*/

		const int  getWidth() const;

		/*
		getStartRowIndex: Accessor method that returns the top right row
		                  index of this Rectangle object.

		Preconditions:	Rectangle object must be created and top right row 
						index set to a positive value

		Postconditions:	Returns top right row index as const integer.
		*/

		const int getStartRowIndex() const;

		/*
		getStartColIndex: Accessor method that returns the top right col
						  index of this Rectangle object.

		Preconditions:	Rectangle object must be created and top right col
						index set to a positive value

		Postconditions:	Returns top right col index as const integer.
		*/

		const int getStartColIndex() const;

		/*
		getbottomRowIndex: Accessor method that returns the bottom left row
							index of this Rectangle object.

		Preconditions:	Rectangle object must be created and bottom left row
						index set to a positive value

		Postconditions:	Returns bottom left col index as const integer.
		*/

		const int getbottomRowIndex() const;

		/*
			getbottomColIndex: Accessor method that returns the bottom left col
								index of this Rectangle object.

			Preconditions:	Rectangle object must be created and bottom left col
							index set to a positive value

			Postconditions:	Returns bottom col index as const integer.
		*/

		const int getbottomColIndex() const;

		/*
			setStartRowIndex: Mutator method that takes an int and sets the 
		                  top right row index of this object.

			Preconditions:	 int passed should be positive integer.

			Postconditions:	Sets the top right row index of this object.
		*/

	  	void setStartRowIndex(int);

		/*
			setStartColIndex: Mutator method that takes an int and sets the 
		                  top right col index of this object.

			Preconditions:	 int passed should be positive integer.

			Postconditions:	Sets the top right col index of this object.
		*/

		void setStartColIndex(int);

		 /*
		  setHeight:		Mutator that takes an integer and sets the height of
							this object.
		 
		  Preconditions:	int passed should be positive integer.
		 
		  Postconditions:	Sets value of height for this object.
		 */

		 void setHeight(int someHeight);

		 /*
			 setWidth:		Mutator that takes an integer and sets the width of
							 this object.

			 Preconditions:	int passed should be positive integer.

			 Postconditions:	Sets value of width for this object.
		 */

		 void setWidth(int someWidth);
		 	 
};

#endif
