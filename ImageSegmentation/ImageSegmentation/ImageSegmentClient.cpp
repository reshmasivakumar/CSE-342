/*
Program 4: ImageSegmentClient.cpp
Author: Reshma Maduri Sivakumar
Design Due Date: 03/08/2017

Purpose:  This program reads a GIF image file and uses recursion to perform image segmentation
and writes it into an output GIF image file. The image is segmented into connected groups
of pixels based on its color attribute. The linked list data structure is used to create
the connected groups. Image is segmented by iterating through the image rows and columns ,
selecting a seed pixel and recursively examining the neighboring 4 pixels (2 pixels in case
of boundary pixels) that has close enough color to the seed pixel. These connected pixels then
form a connected group. The output image consists of a new image similar to the input image,
except that the color of each pixel in the output is the average of the colors of each pixel
in the group of the corresponding pixel in the input image.

*/

#include "PixelContainer.h"
 #include "Image.h"
#include <iostream>

void segmentImage( Image& inputImage, Image& outputImage);
void setOutputImagePixelColors( PixelContainer& current, Image &outputImage);
bool isConnectedPixel(const pixel& seed, const Image &inputImage, int row, int col);
bool isPixelAlreadyUsed(Image& inputImage, int row, int col);
void checkAndAddPixelToGroup
(PixelContainer &current,  Image& inputImage,
	Image& outputImage, int row, int col);


/*
segmentImage(): This method segments the image that is passed as input based on the method of identifying
set of pixels called seeds. The input image is iterated in raster order (i.e every row in
the image is iterated from left to right) to identify the seed pixel and creates connected
groups of pixels based on the color attribute of the seed pixels. A pixel is identified as
seed pixel if it doesnot belong to any other group. The 4 neighboring pixels (or 2 pixels
in case of boundary pixels) of each seed pixel are examined recursively on the basis of
color similarity to form a connected group. Only the neighboring pixels that matched the
color of the seed pixel will be considered as connected pixel and grouped together with the
seed. Once a pixel is processed, it will be marked as processed by setting its RGB value to
{0,0,0}. Then another seed is computed and processing continues until the whole image is
divided
into number of pixel groups. The groups are then merged into a final group. When processing
the groups the average of the RGB color values of the pixels in each group is calculated.
The output image is then created similar to input image except that the color of each pixel
in the output is the average of the colors of each pixel in the group of the corresponding
pixel in the input image.
Once each group is processed, they are merged into a final group. At the end of processing
the final group will represent a linkedlist of all pixels in the input image.
The method then outputs the total number of segments(connected groups), number of pixels in the
merged group and the average color of the merged group.


Precondition:  A valid image object is passed as input. It is assumed that none of the pixels in the
input image is completely black. A output image object created using the input image
needs to be passed as input.

Postcondition: The output image is the segmented and merged version of the input image i.e, each pixel in the
output image is computed as the average of the RGB values of the pixels in the corresponding
connected group it belongs to. The output image can be written to a output gif file in the
calling method.

*/
 
void segmentImage( Image& inputImage, Image& outputImage) {
 	PixelContainer final;
	PixelContainer current;
	pixel seedPixel;
	int numberOfSegments=0;
 	 
	int rows = inputImage.getImageRows();
	int cols = inputImage.getImageCols();
 		
	//loop over pixels in source image
	for (int row = 0; row < rows; row++)
	{
 	 	for (int col = 0; col < cols; col++)
		{
 			seedPixel = inputImage.getImagePixel(row, col);
			if (!isPixelAlreadyUsed(inputImage, row, col)) {
				// counting the number of segments
				numberOfSegments++;
				current.setSeed(seedPixel);
				// Recursively determine if a pixel is already assigned to a group
				// If not add to group
				checkAndAddPixelToGroup(current, inputImage, outputImage, row, col);
				//merge current group into final
				final.merge(current);
  				// Set the outputImage pixel colors to average values of related 
				// pixel colors
				setOutputImagePixelColors(current, outputImage );
 				
				//delete contents of current container group
  				current.deleteContainer();
 			}

		}
		
	}
	cout << " Total Number of segments " << numberOfSegments << endl;
	cout << " Printing details of Merged group" << endl;
	cout << final  << endl;
  	cout << "*********************************************" << endl;
	cout << "Test Copy Constructor of PixelContainer " << endl;
	PixelContainer copyTest(final);
	cout << copyTest <<endl;
 	cout << "*********************************************" << endl;
	cout << "Test assignment operator = of PixelContainer " << endl;
	PixelContainer newCopy = final;
	cout <<  newCopy << endl;
 	/*
	final.deleteContainer();
	cout << "final.getsize after delete" << final.getSize() << endl;
	cout << "copyTest.getsize after deleting final" << copyTest.getSize() << endl;;
	cout << "newCopy.getsize after deleting final" << newCopy.getSize() << endl;;
	*/

 }

/*
setOutputImagePixelColors(): This method is to set the pixels in the output image to the 
average of the color pixels in the input connected group. The input container is looped
over its size and each node in the container is accessed to pixel data and
row and col of the pixelnode. The average color pixels computed for all the
pixel colors in the input container is got using the getAverageColor() methods
of the inputContainer. The corresponding pixel in the same location(row,col) of the output
image is set to this computed average color pixel.  The getNextData() of the input
container class is called to get each  row, col  and pixel data

Precondition:  A valid output image reference and a valid PixelContainer object reference that contains a
set of connected pixels is passed as input along with the input image rows and columns.

Postcondition: The pixels in the output image at each input Group PixelContainer's Node location (row, col) will
be set to the average RGB color values of the PixelContainer.

*/


 void setOutputImagePixelColors( PixelContainer& current , Image &outputImage) {
 
	if (current.getSize() > 0)
	{
		//get average colors of current container group
		int avgRedColor = current.getRedAverageColor();
		int avgBlueColor = current.getBlueAverageColor();
		int avgGreenColor = current.getGreenAverageColor();
		pixel nextPixel;
		int row, col;
		//loop through all pixels in current group
		for (int i = 0; i < current.getSize() ; i++)
		{
			//get pixel, row and col in next node in current
			current.getNextData(nextPixel, row, col);
			//create pixel with average colors
			pixel  avgPixel = { avgRedColor, avgGreenColor, avgBlueColor };
			//set output image pixel at row, col to average pixel
			outputImage.setImagePixel(avgPixel, row, col);
		}
 	}
}

/*
 isConnectedPixel(): This method checks if the seed pixel and the current pixel in the inputimage
					  being processed are connected. The current pixel is considered to be connected
					  to seed if the color of the current pixel is close enough to the seed.
					  This is determined by the formula
					  Let seed be the seed pixel and p is the current pixel of inputimage at row,col
					  then we will say that the color is close enough if:
					  abs(seed.red – p.red) + abs(seed.green – p.green) + abs(seed.blue – p.blue) < 100

Precondition:  A valid seed pixel object reference, valid input image reference and current pixel location (row, col)
			   should be input.

Postcondition: Returns true if the seed pixel and the current pixel at location row,col satisfies the
               formula above
			   returns false otherwise

*/
  
bool isConnectedPixel(const pixel& seed, const Image &inputImage, int row, int col) {
	//difference between RGB pixel of seed and inputimage pixel at row,col
	int redPixelValue = abs(seed.red - inputImage.getImagePixel(row, col).red);
	int bluePixelValue = abs(seed.blue - inputImage.getImagePixel(row, col).blue);
	int greenPixelValue = abs(seed.green - inputImage.getImagePixel(row, col).green);
	//check if count of RGB pixelvalues connected to seed <100 
	//if yes, pixel is connected else no
	if ((redPixelValue + bluePixelValue + greenPixelValue) < 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 isPixelAlreadyUsed(): THis method checks if the pixel at location row, col in the output
						image is marked as already used( belongs to a group). Pixels already
						used are marked as {0,0,0}.

Precondition: A valid inputimage reference and valid location(row, col) of the current pixel being 
              processed

Postcondition: Returns true if current pixel at location row, col has red, blue and green values as 
				{0,0,0}
				returns false otherwise

*/

 
bool isPixelAlreadyUsed(Image& inputImage, int row, int col) {
	//check if pixel of ou
	if (inputImage.getImagePixel(row, col).red == 0 &&
		inputImage.getImagePixel(row, col).blue == 0 &&
		inputImage.getImagePixel(row, col).green == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
checkAndAddPixelToGroup(): This is a recursive method that checks if
							the seed pixel of the current connected 
							group passed and the current pixel of 
							the input image being processed is connected
							and doesnot belong to any other group.
							If so, the pixel is created as a node and added
							to the input connected group.
							The base conditions for this method are:
								- Check if Pixel is outside of Image. This happens when
									we are checking for pixels near boundaries. 
								 -Pixel already belongs to another group
								 - Pixel is not connected (color is not close enough to seed's)

							For the non-base recursive part, the current pixel at location(row,col)
							will be created as a new node and added to the current group.
							Once the seed is added the neigboring 4 pixels (or 2 pixels in case 
							of boundaries) are called recursively to check if they are connected
							to the seed by color. 

*/
 
void checkAndAddPixelToGroup
	(PixelContainer &current,  Image& inputImage, 
	Image& outputImage, int row, int col) {

	// Base Case 1: Check if Pixel is outside of Image. This happens when
	// we are checking for pixels near boundaries.
	if (row > inputImage.getImageRows()-1 || col > inputImage.getImageCols()-1
		|| row < 0 || col < 0)
		return;

	// Base Case 2: Check if pixel is already assigned to a group
	if (isPixelAlreadyUsed(inputImage, row, col))
 		return;

	// Base Case 3: Check if pixel has a color not close enough to seed.
	if (!isConnectedPixel(current.getSeed(), inputImage, row, col))
		return;

	// Recursive Part
	// Add inputImage pixel at row, col to current
	current.createPixelNode(inputImage.getImagePixel(row, col), row, col);
	// Mark the input image pixel to used.
	pixel blackPixel = { 0,0,0 };
	inputImage.setImagePixel(blackPixel, row, col);
	 //recursive calls with neighboring pixels of current pixel
	checkAndAddPixelToGroup(current, inputImage, outputImage, row-1, col);
	checkAndAddPixelToGroup(current, inputImage, outputImage, row, col + 1);
	checkAndAddPixelToGroup(current, inputImage, outputImage, row+1, col);
	checkAndAddPixelToGroup(current, inputImage, outputImage, row, col-1);
	 
	}  


/*
main(): Main method that reads the test.gif as input image. Creates an output image
	    using inputimage. Calls the segmentImage() method to create image segmentation.
		The output image modified after segmentation is written to output.gif file.
		
Precondition: A valid test.Gif file should exist
Postcondition: An output image file output.gif is written to disk.

*/

 int main() {
	// Reading image test.gif from file.
	Image sourceImage("test.gif");
	// Output the number of rows and cols of the source image
	cout << "Printing the input Images Rows and Columns" << endl;
	cout << sourceImage << endl;
	Image outputImage(sourceImage);
	segmentImage(sourceImage, outputImage);
	cout << "Writing output " << endl;
	cout << "Printing the output Images Rows and Columns" << endl;
	cout << outputImage << endl; 
	outputImage.outputToFile("output.gif");
	system("pause");

	 
}


 