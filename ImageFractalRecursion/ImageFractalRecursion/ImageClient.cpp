/*
Program 3
Author: Reshma Maduri Sivakumar
Due Date: 02/10/2017

Purpose:  Image Client program that uses an Image class and a Rectangle class to 
		  create an image fractal using recursion. 
		  This client program reads an image(source image) from the image file "test.gif"
		  and outputs the source image in a particular format as "output.gif".
		  The program contains methods to shrink, invert and create fractal image of the 
		  shrunk and inverted sub-images of the source image. The source image area is divided
		  into 4 partitions as:
		  - Top Left partition contains the reduced version of source image
		  - Top Right partition contains the fractal reduced/inverted images of source image.
		  - Bottom left partition contains the fractal reduced/inverted images of source image
		  - Bottom right partition contains the inverted reduced image of source image
          The Rectangle class is used to hold the dimensions of the partitions. 

		  The color of each pixel in the smaller images is calculated by averaging the 
		  appropriate 2 x 2 block of four pixels in the source image.If the input and output 
		  both have their upper-left corner at (0, 0), then the relationship between the 
		  images is usually:
		  output(r, c) = (input(2r, 2c) + input(2r+1, 2c) + input(2r, 2c+1) + input(2r+1, 2c+1) ) / 4
		  The formula will be applied for each of the RGB color bytes.

		  For the inverted image,  the formula will be
		  output(r, c) = (input(maxR – 2r, maxC – 2c) + input(maxR – 2r – 1, maxC – 2c) +
		  input(maxR – 2r, maxC – 2c – 1) + input(maxR – 2r – 1, maxC – 2c – 1) ) / 4

		  assume the images have their upper-left corner at (0, 0), maxR be one less
		  than the number of rows in the input image and maxC be one less than the
		  number of cols in the input image:
		  output(r, c) = (input(maxR – 2r, maxC – 2c) + input(maxR – 2r – 1, maxC – 2c) +
		  input(maxR – 2r, maxC – 2c – 1) + input(maxR – 2r – 1, maxC – 2c – 1) ) / 4

		  If the image has an odd number of columns, then the subimages on the  left partition 
		  will have one more column than the subimages on the  right, so that the overall image 
		  size stays the same. Similarly, if the image has an odd number of rows, then
		  the reduced images on the top will have one more row than the subimages on the bottom.

*/

#include "ImageLib.h"
#include "Image.h"
#include "Rectangle.h"
#include <iostream>

// constants for the max and min RGB color values.
const int MAX_RGB = 255;
const int MIN_RGB = 0;

// Method Prototypes
 
void createFractalImage(const Image&);
void  createTopLeftPartition(Rectangle& newRect, Rectangle source);
void createTopRightPartition(Rectangle& newRect, Rectangle source);
void createBottomLeftPartition(Rectangle& newRect, Rectangle source);
void createBottomRightPartition(Rectangle& newRect, Rectangle source);
void shrinkImage(Image& targetImage, const Rectangle& sourceArea, const Rectangle& targetArea);
void invertOriginalImage(const Image& sourceImage, Image& targetImage, const Rectangle& targetArea);
void invertSubImage(Image& targetImage, const Rectangle& sourceArea, const Rectangle& targetArea);
void fractalRecurse(Image& targetImage, const Rectangle& sourceArea, const Rectangle& targetArea);

/*
main() :			Reads "test.gif" from file to create a source Image object with.
					A function is called to create an "output.gif" file. The source image will
					be partitioned into 4 areas and fills each partition with reduced/inverted 
					and fractal versions of source image  

Precondition:		test.gif exists and is a valid GIF image
Postcondition:		output.gif will be written which will have the source image partitioned into
                    4 areas as follows:
					- Top Left partition contains the reduced version of source image
					- Top Right partition contains the fractal reduced/inverted images of source image.
					- Bottom left partition contains the fractal reduced/inverted images of source image
					- Bottom right partition contains the inverted reduced image of source image
*/

int main() {

	// Reading image test.gif from file.
	Image sourceImage("test.gif");

	// Output the number of rows and cols of the source image
	cout << "Printing the input Images Rows and Columns" << endl;
	cout << sourceImage << endl;
	cout << "Output image" << endl;
	//Call method to create and output the image to output.gif
	createFractalImage(sourceImage);
	//system("PAUSE");
}


void createFractalImage(const Image& sourceImage) {

	//create destination image with source image dimensions. The target image
	//will be partitioned into 4
	Image targetImage(sourceImage.getImageRows(), sourceImage.getImageCols());

	//create the sourceArea using source image boundaries-  area occupied by the source image 
	// the dimensions of the larger source area will be top right (x,y) (0,noofcols) 
	// bottom right (x,y) will be (noofrows, 0)
	Rectangle sourceArea = Rectangle(0, (sourceImage.getImageCols() - 1), sourceImage.getImageRows(), sourceImage.getImageCols());
	cout << "Source Area" << sourceArea << endl;
	//create the first top-left area - shrinked original image
	Rectangle topLeftRect;
	createTopLeftPartition(topLeftRect, sourceArea);
	cout << "top left partition dimensions " << topLeftRect << endl;
	//create first bottom right area - for inverted image
	Rectangle bottomRightRect;
	createBottomRightPartition(bottomRightRect, sourceArea);
	// create the top right area for recursively defined fractal of top left image
	Rectangle topRightRect;
	createTopRightPartition(topRightRect, sourceArea);
	//create bottom left rectangle - recursively defined fractal of bottom right image
	Rectangle bottomLeftRect;
	createBottomLeftPartition(bottomLeftRect, sourceArea);

	//shrink original image and place in topLeftRect
	targetImage = sourceImage;
	shrinkImage(targetImage, sourceArea, topLeftRect);

	//invert the shrunk image and place in bottom right rectangle
	invertOriginalImage(sourceImage, targetImage, bottomRightRect);
	 
	// Call fractal recursion to recurse to shrink and invert image in the
	// topLeftRect into the topRigtRect
	fractalRecurse(targetImage, topLeftRect, topRightRect);

	//Call fractal recursion to recurse to shrink and invert image in the
	// topLeftRect into the bottom left Rect
	fractalRecurse(targetImage, topLeftRect, bottomLeftRect);
	//write targetimage to output.gif
	targetImage.outputToFile("output.gif");
	
}


/*
createTopLeftPartition: Partitions this Rectangle object and returns the
						top-left portion(smaller rectangle). If height of
						this object is odd, the top left partition should
						have one more row than the partitions in the bottom.
						eg. If the source image area dimensions are
						{0, 575} {431,0} then top left dimensions will be
						{0,287} {215,0}

Preconditions:	 Called on a valid Rectangle object big enough to be partitioned

Postconditions: Returns the top left partition of this Rectangle object
				which will be 1/4th the size of this entire Rectangle object.
*/

void  createTopLeftPartition(Rectangle& topLeftRect, Rectangle source)
{

	//set top right dimensions for the top left partition as source image's
	// starting dimension 0 , source image's half of the width 
	topLeftRect.setStartRowIndex(source.getStartRowIndex());
	topLeftRect.setStartColIndex(source.getStartColIndex() - (source.getWidth() / 2));
	//set width of topleft 
	topLeftRect.setWidth(source.getWidth() / 2);
	//If the Rectangle has an odd number of rows(width),
	//then the width should have one more row
	if (source.getHeight() % 2 != 0)
	{
		topLeftRect.setHeight((source.getHeight() / 2) + 1);
	}
	else
		topLeftRect.setHeight(source.getHeight() / 2);

	//calculate the bottom left dimensions  
	topLeftRect.setbottomRowIndex();
	topLeftRect.setbottomColIndex();
 	 
}

/*
	createTopRightPartition: Partitions this Rectangle object and returns the
							top-right portion(smaller rectangle). If height of
							this object is odd, the top right partition should
							have one more row than the partitions in the bottom.
							eg. If the source image area dimensions are
							{0, 575} {431,0} then top right dimensions will be
							{0,575} {215,288}

Preconditions: Called on a valid Rectangle object big enough to be
				partitioned

Postconditions: Returns the top right partition of this Rectangle object
				which will be 1/4th the size of this entire Rectangle object.
*/


void createTopRightPartition(Rectangle &topRightRect, Rectangle source)
{
	// set top right dimensions for the top right partition as source image's
	// starting dimensions ( 0 , noofcols of source)
	topRightRect.setStartRowIndex(source.getStartRowIndex());
	topRightRect.setStartColIndex(source.getStartColIndex());

	//set width is source image width by 2
	topRightRect.setWidth(source.getWidth() / 2);

	//if height odd, add extra row to height
	if (source.getHeight() % 2 != 0)
	{
		topRightRect.setHeight((source.getHeight() / 2) + 1);
	}
	else
		topRightRect.setHeight(source.getHeight() / 2);
	
	//calculate the bottom left dimensions 
	topRightRect.setbottomRowIndex();
	topRightRect.setbottomColIndex();

}


/*
createBottomLeftPartition: Partitions this Rectangle object and returns the
							bottom left portion(smaller rectangle). If width of
							this object is odd, the bottom left partition should
							have one more col is added to maintain
							the overall image size.
							eg. If the source image area dimensions are
							{0, 575} {431,0} then top right dimensions will be
							{216, 287} {431,0}


Preconditions: Called on a valid Rectangle object big enough to be
							partitioned

Postconditions: Returns the bottom left partition of this Rectangle object
				which will be 1/4th the size of this entire Rectangle object.
*/

void createBottomLeftPartition(Rectangle& bottomLeftRect, Rectangle source)
{
	//set top right dimension of bottom left partition as half of source rows, half of
	//source columns -1
	bottomLeftRect.setStartRowIndex(source.getStartRowIndex() + (source.getHeight() / 2));
	bottomLeftRect.setStartColIndex(source.getStartColIndex() - (source.getWidth() / 2));
	
	bottomLeftRect.setHeight(source.getHeight() / 2);

	//if width odd , the left partition has one more column than right
	if (source.getWidth() % 2 != 0)
	{
		bottomLeftRect.setWidth((source.getWidth() / 2) + 1);
	}
	else
		bottomLeftRect.setWidth(source.getWidth() / 2);

	bottomLeftRect.setbottomRowIndex();
	bottomLeftRect.setbottomColIndex();
}

/*
	createBottomRightPartition: Partitions this Rectangle object and returns the
								bottom right portion(smaller rectangle). If height of
								this object is odd, the top  partition should
								have one more row than the partitions in the bottom.
								If width is odd, the left partition should have one
								more column than the partion on the right  to maintain
								the overall image size.
								eg. If the source image area dimensions are
								{0, 575} {431,0} then top right dimensions will be
								{216,575 } {431,288 }	

Preconditions: Called on a valid Rectangle object big enough to be
			partitioned

Postconditions: Returns the bottom right partition of this Rectangle object
					which will be 1/4th the size of this entire Rectangle object.
*/
void createBottomRightPartition(Rectangle& bottomRightRect, Rectangle source)
{
	//set top left dimensions of bottom right partition to be source image start index 
	//(noofrows/2, noofcols )
	bottomRightRect.setStartRowIndex(source.getStartRowIndex() + (source.getHeight() / 2));
	bottomRightRect.setStartColIndex(source.getStartColIndex());
	//set height and width half of source
	bottomRightRect.setHeight(source.getHeight() / 2);
	bottomRightRect.setWidth(source.getWidth() / 2);
	//calculate the bottom left dimensions 

	bottomRightRect.setbottomRowIndex();
	bottomRightRect.setbottomColIndex();
}

/*
	shrinkImage:  Reduce the size of the source image by reducing the RGB Color pixels as average
					of 2X2 block of source pixels into target.

	Preconditions:  A valid source Image area and target area whose dimensions lie within
					source area

	Postconditions: Returns the reduced size of the source image to 1/4th of the source image size

*/
void shrinkImage(Image& targetImage, const Rectangle& sourceArea, const Rectangle& targetArea)
{
	
	//Get the source top right image dimensions 
	//image reduced size to be calculated relative to the source image
	int minRow = sourceArea.getStartRowIndex();
	int minCol = (sourceArea.getStartColIndex() - sourceArea.getWidth()) + 1;

	int maxRow = (sourceArea.getStartRowIndex() + sourceArea.getHeight()) - 1;
	int maxCol = sourceArea.getStartColIndex();

	//RGB pixel average counts 
	int targetRedPixelCount = 0, targetGreenPixelCount = 0, targetBluePixelCount = 0;

	int inputRow1 = 0, inputCol1 = 0, inputRow2 = 0, inputCol2 = 0,
		inputRow3 = 0, inputCol3 = 0, inputRow4 = 0, inputCol4 = 0;

	//get the dimensions of the area of the target partition
	// to iterate over
	int startRow = targetArea.getStartRowIndex();
	int startCol = targetArea.getbottomColIndex();
	int bottomRow = targetArea.getbottomRowIndex();
	int endCol = targetArea.getStartColIndex();

	//Iterate the target area relative to source
	for (int row = startRow; row <= bottomRow; row++)
	{
		for (int col = startCol; col <= endCol; col++)
		{
			//target(r, c) = (input(2r, 2c) + input(2r+1, 2c) + input(2r, 2c+1) + input(2r+1, 2c+1) ) / 4

			inputRow1 = minRow + (2 * (row - startRow));
			inputCol1 = minCol + (2 * (col - startCol));
			inputRow2 = minRow + (2 * (row - startRow) + 1);
			inputCol2 = minCol + (2 * (col - startCol));
			inputRow3 = minRow + (2 * (row - startRow));
			inputCol3 = minCol + ((2 * (col - startCol)) + 1);
			inputRow4 = minRow + (2 * (row - startRow) + 1);
			inputCol4 = minCol + ((2 * (col - startCol)) + 1);

			//check average never crosses the boundary between partitions
			if ((inputRow1 <= maxRow && inputCol1 <= maxCol) &&
				(inputRow2 <= maxRow && inputCol2 <= maxCol) &&
			 	(inputRow3 <= maxRow && inputCol3 <= maxCol) &&
				(inputRow4 <= maxRow && inputCol4 <= maxCol))
			{
				//average redpixel count
				targetRedPixelCount = (targetImage.getImagePixel(inputRow1, inputCol1).red + targetImage.getImagePixel(inputRow2, inputCol2).red
					+ targetImage.getImagePixel(inputRow3, inputCol3).red +
						targetImage.getImagePixel(inputRow4, inputCol4).red) / 4;

				//average greenpixel count
				targetGreenPixelCount = (targetImage.getImagePixel(inputRow1, inputCol1).green + targetImage.getImagePixel(inputRow2, inputCol2).green
					+ targetImage.getImagePixel(inputRow3, inputCol3).green +
					targetImage.getImagePixel(inputRow4, inputCol4).green) / 4;

				//average bluepixel count
				targetBluePixelCount = (targetImage.getImagePixel(inputRow1, inputCol1).blue + targetImage.getImagePixel(inputRow2, inputCol2).blue
					+ targetImage.getImagePixel(inputRow3, inputCol3).blue +
					targetImage.getImagePixel(inputRow4, inputCol4).blue) / 4;

				//set target image pixels as average of 2X2 block of source pixels
				targetImage.setImageRed(targetRedPixelCount, row, col);
				targetImage.setImageBlue(targetBluePixelCount, row, col);
				targetImage.setImageGreen(targetGreenPixelCount, row, col);
			}
		}
	}
 }
/*
	invertOriginalImage:   Shrinks and Inverts the  source image into the bottom rigt partition.
							The RGB Color pixels of the inverted target image are calculated as
							as average of 2X2 block of source pixels into target.
							target(r, c) = (input(maxR – 2r, maxC – 2c) +
							input(maxR – 2r – 1, maxC – 2c) +
							input(maxR – 2r, maxC – 2c – 1) +
							input(maxR – 2r – 1, maxC – 2c – 1) ) / 4

	Preconditions: A valid sourceimage, target image and target area where inverted reduced 
					image will be output

	Postconditions: Returns the bottom right partition of this Rectangle object
					which will be 1/4th the size of this entire Rectangle object which
					will contain the reduced shrunk image of the source image
*/			

void invertOriginalImage(const Image& sourceImage, Image& targetImage, const Rectangle& targetArea)
{
	//set top right dimensions of the target area - which is same as source 
 	int startRow = targetArea.getStartRowIndex();
	int startCol = (targetArea.getStartColIndex() + 1) - targetArea.getWidth();

    //set the source height and width to iterate over
	int bottomRow = startRow + (targetArea.getHeight() - 1);
 	int endCol = startCol + (targetArea.getWidth() - 1);

	//define maxRow and maxCol
	int maxRow = sourceImage.getImageRows() - 1;
	int maxCol = sourceImage.getImageCols() - 1;

	//RGB average pixel counts
	int targetRedPixelCount = 0, targetGreenPixelCount = 0, targetBluePixelCount = 0;
	 
	int inputRow1 = 0, inputCol1 = 0, inputRow2 = 0, inputCol2 = 0,
		inputRow3 = 0, inputCol3 = 0, inputRow4 = 0, inputCol4 = 0;

	//Iterate over destination, but calculate based on source
	for (int row = startRow; row <= bottomRow; row++)
	{
		for (int col = startCol; col <= endCol; col++)
		{
			//target(r, c) = (input(maxR – 2r, maxC – 2c) + input(maxR – 2r – 1, maxC – 2c) +
				//input(maxR – 2r, maxC – 2c – 1) + input(maxR – 2r – 1, maxC – 2c – 1)) / 4

			inputRow1 = maxRow - (2 * (row - startRow));
			inputCol1 = maxCol - (2 * (col - startCol));
			inputRow2 = maxRow - (2 * (row - startRow)) - 1;
			inputCol2 = maxCol - (2 * (col - startCol));
			inputRow3 = maxRow - (2 * (row - startRow));
			inputCol3 = maxCol - (2 * (col - startCol)) - 1;
			inputRow4 = maxRow - (2 * (row - startRow)) - 1;
			inputCol4 = maxCol - (2 * (col - startCol)) - 1;

			//calculate the red pixel count for target as average of source red pixel count 
			targetRedPixelCount = (sourceImage.getImagePixel(inputRow1, inputCol1).red + sourceImage.getImagePixel(inputRow2, inputCol2).red
				+ sourceImage.getImagePixel(inputRow3, inputCol3).red +
				sourceImage.getImagePixel(inputRow4, inputCol4).red) / 4;

			//calculate the green pixel count for target as average of source green pixel count 
			targetGreenPixelCount = (sourceImage.getImagePixel(inputRow1, inputCol1).green + sourceImage.getImagePixel(inputRow2, inputCol2).green
				+ sourceImage.getImagePixel(inputRow3, inputCol3).green +
				sourceImage.getImagePixel(inputRow4, inputCol4).green) / 4;

			//calculate the blue pixel count for target as average of source blue pixel count 
			targetBluePixelCount = (sourceImage.getImagePixel(inputRow1, inputCol1).blue + sourceImage.getImagePixel(inputRow2, inputCol2).blue
				+ sourceImage.getImagePixel(inputRow3, inputCol3).blue +
				sourceImage.getImagePixel(inputRow4, inputCol4).blue) / 4;

			//set the target image RGB pixels 
			targetImage.setImageRed(targetRedPixelCount, row, col);
			targetImage.setImageBlue(targetBluePixelCount, row, col);
			targetImage.setImageGreen(targetGreenPixelCount, row, col);

		}
	}
}


/*
	invertOriginalImage:   Called in create Fractal recursive function to create fractal images
						  of reduced and Inverted  source image into the bottom rigt partition.
							The RGB Color pixels of the inverted target image are calculated as
							as average of 2X2 block of source pixels into target.
							target(r, c) = (input(maxR – 2r, maxC – 2c) +
							input(maxR – 2r – 1, maxC – 2c) +
							input(maxR – 2r, maxC – 2c – 1) +
							input(maxR – 2r – 1, maxC – 2c – 1) ) / 4

	Preconditions: A valid target image, source area and target area where inverted reduced
				image will be output

	Postconditions: Returns the bottom right partition of this Rectangle object
					which will be 1/4th the size of this entire Rectangle object which
					will contain the  reduced shrunk image of the source image
*/


void invertSubImage(Image& targetImage, const Rectangle& sourceArea, const Rectangle& targetArea)
{
	//set dimensions of target area 
 	int startRow = targetArea.getStartRowIndex();
	int startCol = (targetArea.getStartColIndex()) - targetArea.getWidth();
	//get the area to iterate over	 
	int bottomRow = startRow + (targetArea.getHeight() - 1);
	int endCol = startCol + (targetArea.getWidth() - 1);

	//define maxRow and maxCol
	int maxRow = sourceArea.getbottomRowIndex();
	int maxCol = sourceArea.getStartColIndex();

	//RGB pixel counts pixel counts
	int redPixelCount = 0, greenPixelCount = 0, bluePixelCount = 0;

	//Iterate over destination, but calculate based on source
	for (int row = startRow; row <= bottomRow; row++)
	{
		for (int col = startCol; col <= endCol; col++)
		{
			//output(r, c) = (input(maxR – 2r, maxC – 2c) + input(maxR – 2r – 1, maxC – 2c) +
			//	input(maxR – 2r, maxC – 2c – 1) + input(maxR – 2r – 1, maxC – 2c – 1)) / 4

			redPixelCount = targetImage.getImagePixel(maxRow - (2 * (row - startRow)), maxCol - (2 * (col - startCol))).red;
			greenPixelCount = targetImage.getImagePixel(maxRow - (2 * (row - startRow)), maxCol - (2 * (col - startCol))).green;
			bluePixelCount = targetImage.getImagePixel(maxRow - (2 * (row - startRow)), maxCol - (2 * (col - startCol))).blue;
			 
			redPixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)) - 1, maxCol - (2 * (col - startCol)) - 1).red;
			greenPixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)) - 1, maxCol - (2 * (col - startCol)) - 1).green;
			bluePixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)) - 1, maxCol - (2 * (col - startCol)) - 1).blue;
			 
			redPixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)), maxCol - (2 * (col - startCol)) - 1).red;
			greenPixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)), maxCol - (2 * (col - startCol)) - 1).green;
			bluePixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)), maxCol - (2 * (col - startCol)) - 1).blue;
			 
			redPixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)) - 1, maxCol - (2 * (col - startCol)) - 1).red;
			greenPixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)) - 1, maxCol - (2 * (col - startCol)) - 1).green;
			bluePixelCount += targetImage.getImagePixel(maxRow - (2 * (row - startRow)) - 1, maxCol - (2 * (col - startCol)) - 1).blue;

			//calc average

			 	redPixelCount = redPixelCount / 4;
				greenPixelCount = greenPixelCount / 4;
				bluePixelCount = bluePixelCount / 4;
			

			targetImage.setImageRed(redPixelCount, row, col);
			targetImage.setImageBlue(bluePixelCount, row, col);
			targetImage.setImageGreen(greenPixelCount, row, col);

		}
	}
}


/*
  fractalRecurse:       Recursive function that  creates fractal images by reducing and 
						inverting images defined in sourceArea into targetArea on targetImage.
						The fractals are created by shrink the image into top-left area and 
						inverting into bottom-right area recursively.

  Preconditions:		 Valid targetImage, source area and target area to output
 
  Postconditions:		The targetArea of the target image is filled with fractal
                        images based on sourceArea.
*/
void fractalRecurse(Image& targetImage, const Rectangle& sourceArea, const Rectangle& targetArea)
{

	//base case - recurse till no rows and cols in target Area
	if (targetArea.getHeight() <= 0 || targetArea.getWidth() <= 0)
	{
		return;
	}
	else
	{
		//create topLeft partition of the targetArea 
		Rectangle topLeftRect;
		 createTopLeftPartition(topLeftRect, targetArea);
		//shrink image relative to sourcearea
		shrinkImage(targetImage, sourceArea, topLeftRect);
		//create bottomRight partition of targetArea
		Rectangle bottomRightRect;
		createBottomRightPartition(bottomRightRect, targetArea);
		//invert and shrink source image into bottomRightRect
		invertSubImage(targetImage, sourceArea, bottomRightRect);
		//create topRight partition of targetArea
		Rectangle topRightRect;
		createTopRightPartition(topRightRect, targetArea);
		//Call fractal recurse into topRight partition
		fractalRecurse(targetImage, topLeftRect, topRightRect);
		// create bottomleft partition of targetArea
		Rectangle bottomLeftRect;
		createBottomLeftPartition(bottomLeftRect, targetArea);
		//Call fractal recurse into bottomLeft partition
		fractalRecurse(targetImage, topLeftRect, bottomLeftRect);
	}
}


