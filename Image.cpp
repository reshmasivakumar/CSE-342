/*
Program 4: Image.cpp
Author: Reshma Maduri Sivakumar
Due Date: 03/08/2017

Purpose: Image class that implements Image.h and creates an Image object with
		 an image as its instance variable. The class has overoaded ==, !=, = and
		 << operators.
*/

#include "ImageLib.h"
#include "Image.h"
#include <iostream>
//using namespace std;

// Input gif image 
const string imageFileName = "test.gif";

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

Image::Image(string inputFileName) {

	myImage = ReadGIF(inputFileName);
}

/*
ImageClass:        Constructor that takes as input values for rows and cols
				   and creates a new Image object by calling the CreateImage
				   function from ImageLib.h.

Preconditions:	   Values for rows and cols must be valid (greater than 0).

Postconditions:    Image object has been created with dimensions set to the
				   input rows and cols and red, blue and green component of
				   the pixels are set to black (initialized to 0).
*/

Image::Image(int rows, int cols) {

	// create a new image with dimensions as rows by cols
	myImage = CreateImage(rows, cols);

	// initialize the image to black
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			myImage.pixels[row][col].red = 0;
			myImage.pixels[row][col].blue = 0;
			myImage.pixels[row][col].green = 0;
		}
	}
}

/*
ImageClass:      Copy Constructor that takes as input another Image object
				 and creates a new Image object by calling the CopyImage
				 function from ImageLib.h. This creates a copy of the passed
				 Image object.

Preconditions:	 The input file must be a .GIF image..

Postconditions:  Image Object has been created by copying the input
                 Image object.
*/

Image::Image(const Image& otherImage) {

	// copy the image passed into myImage
	myImage = CopyImage(otherImage.myImage);
}

/*
Destructor:		Calls DeallocateImage method from ImageLib 
				and deallocates the image

Preconditions:  None.

Postconditions: Image object of the calling instance is deallocated.

*/

Image :: ~Image() {

	DeallocateImage(myImage);
}

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

Image &Image::operator=(const Image &otherImage) {

	// check if the image passed is self to avoid deallocating self
	if (this != &otherImage) {
		// deallocate this image to free the memory (prevent memory leaks)
		DeallocateImage(myImage);
		// set self to image passed.
		myImage = CopyImage(otherImage.myImage);
	}
	return *this;
}

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

bool Image :: operator == (const Image &otherImage) const {

	image temp = otherImage.myImage;

	if (myImage.rows != temp.rows && myImage.cols != temp.cols)
		return false;

	for (int row = 0; row < temp.rows; row++) {
		for (int col = 0; col < temp.cols; col++) {
			if (myImage.pixels[row][col].red != temp.pixels[row][col].red
				|| myImage.pixels[row][col].blue != temp.pixels[row][col].blue
				|| myImage.pixels[row][col].green != temp.pixels[row][col].green)
				return false;
		}
	}

	return true;
}

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

bool Image :: operator != (const Image &otherImage) const {

	return !(*this == otherImage);

}


/*
getImagePixel :       Accessor method that returns the Image object's
pixel at the input row and col (myImage.pixels[row][col]).

Preconditions:	      Pixels of the instance image cannot be NULL and the input
row and col must be greater than 0 and less than the Image's
rows and cols.

Postconditions:       Returns a const refrence to the instance images pixel at
myImage.pixels[row][col].
*/

const pixel& Image::getImagePixel(int row, int col) const {
	// if (myImage.pixels == NULL || row > myImage.rows || col > myImage.cols)
	//	return 
	return myImage.pixels[row][col];
}

/*
getImageRow :       Accessor method that returns how many rows are in the instance
image object: myImage.

Preconditions:	    The image object must conatain valid number of rows.

Postconditions:     Returns the number of rows in myImage.
*/

int Image::getImageRows() const {

	return myImage.rows;
}

/*
getImageCol :       Accessor method that returns how many cols are in the instance
image object: myImage.

Preconditions:	    The image object must conatain valid number of cols.

Postconditions:     Returns the number of cols in myImage.
*/

int Image::getImageCols() const {

	return myImage.cols;
}


  
/*
setImagePixel :     Mutator method that sets the input pixel to the
instance image object at the specified row and col.

Preconditions:	    Input row and col must be positive numbers and lesser than
the myImage's rows and cols.

Postconditions:     Sets the instance image object's pixels to otherPixel at the
specified row and col.
*/

void Image::setImagePixel(const pixel otherPixel, int row, int col) {
	//check if row, col are witin image boundaries
	if (row < 0 || row > getImageRows())
		throw exception("Trying to set pixel out of bounds");
	if (row < 0 || row > getImageCols())
		throw exception("Trying to set pixel out of bounds");
	myImage.pixels[row][col] = otherPixel;
}


/*
setImageRed :       Mutator method that sets the red value of myImage at the specified row and col

Preconditions:	    Input row must be greater than 0, myImage.pixels should not be NULL and the input
red value must be greater than 0 and less than 255.

Postconditions:     Sets the input red value at myImage.pixels[row][col].red.
*/

void Image::setImageRed(const int red, int row, int col) {
	if (red < 0 || red > 255)
		throw exception("Red component in an image can only be between 0 and 255");
	if (myImage.pixels != NULL)
		myImage.pixels[row][col].red = red;
}

/*
setImageBlue :       Mutator method that sets the blue value of myImage at the specified row and col

Preconditions:	     Input row must be greater than 0, myImage.pixels should not be NULL and the input
blue value must be greater than 0 and less than 255.

Postconditions:      Sets the input blue value at myImage.pixels[row][col].red.
*/

void Image::setImageBlue(const int blue, int row, int col) {

	if (blue < 0 || blue > 255)
		throw exception("Blue component in an image can only be between 0 and 255");
	if (myImage.pixels != NULL)
		myImage.pixels[row][col].blue = blue;
}

/*
setImageGreen :     Mutator method that sets the green value of myImage at the specified row and col

Preconditions:	    Input row must be greater than 0, myImage.pixels should not be NULL and the input
green value must be greater than 0 and less than 255.

Postconditions:     Sets the input green value at myImage.pixels[row][col].red.
*/

void Image::setImageGreen(const int green, int row, int col) {
	if (green < 0 || green > 255)
		throw exception("Green component in an image can only be between 0 and 255");
	if (myImage.pixels != NULL)
		myImage.pixels[row][col].green = green;
}

/*
outputToFile :     Method calls writeGIF function from ImageLib.h to write the image
				   object to file under the outputFileName.

Preconditions:	   outputFileName is a valid name to output an image to file.

Postconditions:    Image with the name "outputfilename" is written to the file.
*/

void Image::outputToFile(string outputfileName) const{

	WriteGIF(outputfileName, myImage);
}

 /*
operator<< :		cout has been overloaded to output the instance image's
					rows and cols value. 

Precondition:		None.

Postcondition:		Outputs to console the values of myImage.rows and myImage.cols.

*/

ostream& operator<<(ostream& out, const Image& otherImage) {

	out << "Rows: " << otherImage.myImage.rows << " " << "Columns: " << otherImage.myImage.cols << endl;
	return out;

}
