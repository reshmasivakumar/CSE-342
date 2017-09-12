/*
Program 3: Image.h
Author: Reshma Maduri Sivakumar
Due Date: 02/10/2017

Purpose: Interface for the Image class.

*/

#include "ImageLib.h"

#ifndef Image_h
#define Image_h

#include <iostream>
using namespace std;

class Image
{
	/*
	operator<< :		cout has been overloaded to output the instance image's
	rows and cols value.

	Precondition:		None.

	Postcondition:		Outputs to console the values of myImage.rows and myImage.cols.

	*/

	friend ostream& operator<<(ostream&, const Image&);

private:

	// instance variable for the image class.
	image myImage;

public:
	/*
	ImageClass:			Constructor that takes as input a string file and
	creates a new Image object by calling the ReadGIF
	function from ImageLib.h.

	Preconditions:		The input file must have an extension .GIF as the
	Image class can only process GIF Image files.

	Postconditions:		Image object has been created with the name inputFileName
	and the image is associated to the image with the name
	inputFileName on the file. Image creates a black blank
	image with rows, cols and pixels set to 0 if no image was
	read.
	*/

	Image(string);

	/*
	ImageClass:        Constructor that takes as input values for rows and cols
	and creates a new Image object by calling the CreateImage
	function from ImageLib.h.

	Preconditions:	   Values for rows and cols must be valid (greater than 0).

	Postconditions:    Image object has been created with dimensions set to the
	input rows and cols and red, blue and green component of
	the pixels are set to black (initialized to 0).
	*/

	Image(int, int);

	/*
	ImageClass:      Copy Constructor that takes as input another Image object
	and creates a new Image object by calling the CopyImage
	function from ImageLib.h. This creates a copy of the passed
	Image object.

	Preconditions:	 The input file must be a .GIF image..

	Postconditions:  Image Object has been created by copying the input
	Image object.
	*/

	Image(const Image&);

	/*
	Destructor:		Calls DeallocateImage method from ImageLib
	and deallocates the image

	Preconditions:  None.

	Postconditions: Image object of the calling instance is deallocated.

	*/

	~Image();

	/*
	Operator= :     The assignment operator has been overloaded to call
	CopyImage function of ImageLib.h to create a copy of
	the Image object passed in the parameter only if the
	image passed isnt the same as the image existing in
	this class.

	Preconditions:	The passed Image object who's Pixels = NULL.

	Postconditions: Image object passed has been assigned to this image
	with the same rows, cols and pixels and returns the
	reference of this newly assigned image object.
	*/

	Image& operator = (const Image&);

	/*
	Operator== :      The equal to operator is overloaded to loop through
	each pixels of the image and compares if the RGB
	components are equal between myImage and otherImage.

	Preconditions:	  otherImage and the instance image object must have the
	same dimensions.

	Postconditions:   Returns false if the dimensions are not the same between
	myImage and otherImage.
	Returns true if the dimensions and each pixels are the
	same.
	*/

	bool operator == (const Image&) const;

	/*
	operator!= :     The not equal to operator is over loaded to call the
	equal to function and returns the ! of it.

	Preconditions:	 otherImage and the instance image object must have the
	same dimensions.

	Postconditions:  Returns true if the dimensions are not the same between
	myImage and otherImage.
	Returns false if the dimensions and each pixels are the
	same.
	*/

	bool operator != (const Image&) const;

	/*
	getImage     :       Accessor method that returns the image instance variable.

	Preconditions:	      myImage must be created

	Postconditions:       Returns a const refrence to the instance image.
	*/

	//const image& getImage() const;

	/*
	getImagePixel :       Accessor method that returns the Image object's
	pixel at the input row and col (myImage.pixels[row][col]).

	Preconditions:	      Pixels of the instance image cannot be NULL and the input
	row and col must be greater than 0 and less than the Image's
	rows and cols.

	Postconditions:       Returns a const refrence to the instance images pixel at
	myImage.pixels[row][col].
	*/

	const pixel& getImagePixel(int, int) const;

	/*
	getImageRow :       Accessor method that returns how many rows are in the instance
	image object: myImage.

	Preconditions:	    The image object must conatain valid number of rows.

	Postconditions:     Returns the number of rows in myImage.
	*/
	int getImageRows() const;

	/*
	getImageCol :       Accessor method that returns how many cols are in the instance
	image object: myImage.

	Preconditions:	    The image object must conatain valid number of cols.

	Postconditions:     Returns the number of cols in myImage.
	*/

	int getImageCols() const;

	  
	/*
	setImagePixel :     Mutator method that sets the input pixel to the
	instance image object at the specified row and col.

	Preconditions:	    Input row and col must be positive numbers and lesser than
	the myImage's rows and cols.

	Postconditions:     Sets the instance image object's pixels to otherPixel at the
	specified row and col.
	*/
	void setImagePixel(pixel, int, int);

  
	/*
	setImageRed :       Mutator method that sets the red value of myImage at the specified row and col

	Preconditions:	    Input row must be greater than 0, myImage.pixels should not be NULL and the input
	red value must be greater than 0 and less than 255.

	Postconditions:     Sets the input red value at myImage.pixels[row][col].red.
	*/

	void setImageRed(int, int, int);

	/*
	setImageBlue :       Mutator method that sets the blue value of myImage at the specified row and col

	Preconditions:	     Input row must be greater than 0, myImage.pixels should not be NULL and the input
	blue value must be greater than 0 and less than 255.

	Postconditions:      Sets the input blue value at myImage.pixels[row][col].red.
	*/

	void setImageBlue(int, int, int);

	/*
	setImageGreen :     Mutator method that sets the green value of myImage at the specified row and col

	Preconditions:	    Input row must be greater than 0, myImage.pixels should not be NULL and the input
	green value must be greater than 0 and less than 255.

	Postconditions:     Sets the input green value at myImage.pixels[row][col].red.
	*/
	void setImageGreen(int, int, int);

	/*
	outputToFile :     Method calls writeGIF function from ImageLib.h to write the image
	object to file under the outputFileName.

	Preconditions:	   outputFileName is a valid name to output an image to file.

	Postconditions:    Image with the name "outputfilename" is written to the file.
	*/

	void outputToFile(string)const;

	/*
	MirrorImage:		Method creates a new Image object which is a copy of the instance image
	returns the flipped Image object. myImage is not changed.

	Preconditions:		Instance image (myImage) has myImage.rows * myImage.cols pixels allocated.

	Postconditions:		The temp Image has been flipped horizontally to create a mirrored effect
	and has been returned.
	*/
	Image mirrorImage() const;

	/*
	photoNegative:		Method creates a new Image object which is a copy of the instance image
	and returns the photonegative Image object. instance object
	myImage is not changed.

	Preconditions:	    Instance image (myImage) has myImage.rows * myImage.cols pixels allocated.

	Postconditions:    The temp Image has been modified with all pixel colors inverted
	and has been returned.
	*/
	Image photoNegative() const;

	/*
	invertPixels:		Inverts the color of a single pixel

	Preconditions:	    None

	Postconditions:    Each color in a pixel (Red, Blue and Green have been inverted (255-color);

	*/
	void invertPixels(pixel&) const;


};

#endif /* Image_h */
