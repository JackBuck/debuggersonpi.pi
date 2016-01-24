/*
 * CBlockReader.cpp
 *
 *  Created on: 24 Jan 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CBlockReader.h"

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;
using namespace cv;


// -/-/-/-/-/-/-/ CONSTRUCTORS AND DESTRUCTORS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
/* ~~~ FUNCTION (default constructor) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialises m_Image and m_Spots as empty by implicit calls to their default constructors.
 */
CBlockReader::CBlockReader()
{
}

/* ~~~ FUNCTION (constructor) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialises m_Image from a specified file.
 *
 * The image is resized immediately after loading.
 * The constructor throws an exception if the image could not be loaded.
 *
 * INPUTS:
 * 	imagePath - A string containing the path to an image to use to initialise the class instance.
 */
CBlockReader::CBlockReader(string imagePath)
{
	Mat image_fullsize = imread(imagePath, IMREAD_GRAYSCALE);
	if ( image_fullsize.empty() )
	{
		throw InputImagePath_BadFilePath {imagePath};
	}
	else
	{
		resize(image_fullsize, m_Image, Size(), 0.2, 0.2, INTER_AREA);
	}
}


/* ~~~ FUNCTION (destructor) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */
CBlockReader::~CBlockReader()
{
	// TODO Auto-generated destructor stub
}


// -/-/-/-/-/-/-/ INITIALISER FUNCTIONS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *	This function uses the Pi's camera to take a photo. It will save the photo, update m_Image to use
 *	this photo and reset all member variables calculated using any previous image.
 *
 *	INPUTS:
 *	saveLocation - This should contain the path at which to save the photo.
 */
bool CBlockReader::TakePhoto(const std::string saveLocation)
{
	// TODO: Find out how to take a photo with the PI camera and the implement CBlockReader::TakePhoto
}


// -/-/-/-/-/-/-/ SPOT COUNTING FUNCTIONS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function uses the opencv SimpleBlobDetector to count and return the number of spots in the
 * picture. It calls VerifySpotNbhdVisible() and VerifySpotArrangement() to check that the number
 * counted can be trusted. A value of -1 is returned instead if not.
 */
int CBlockReader::CountSpots()
{

}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function uses the opencv SimpleBlobDetector to identify the spots in the picture. The spots
 * are filtered based on their area, circularity, convexity and inertia.
 */
void CBlockReader::DetectSpots()
{
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function computes the distances between the spots and compares the results with the
 * distances expected for that number of spots. (If the distances match up to within a given
 * tolerance then the two arrangements are regarded as the same up to an isometry, and so are deemed
 * acceptable). A value of true is returned if the test passes and false if the spot arrangement is
 * unexpected.
 */
bool CBlockReader::VerifySpotArrangement()
{
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function verifies that the spots are not too close to the edge of the image such that we
 * are at risk of cropping out extra spots.
 */
bool CBlockReader::VerifySpotNbhdVisible()
{
}


// -/-/-/-/-/-/-/ BLOCK LOCATION FUNCTIONS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function analyses the image to determine the position and orientation of the block relative
 * to the robot. This is useful for providing feedback to the caller when the picture supplied to
 * the CBlockReader is rejected when counting the spots.
 *
 * OUTPUTS:
 * blockRelPosn_x - The x-coordinate of the approximate centre of the block in the image frame.
 * blockRelPosn_y - The y-coordinate of the approximate centre of the block in the image frame.
 * blockRelRotation - The (anticlockwise) angle (in RADIANS) through which the block has been
 * 	rotated in the image frame. Note that this can only be defined up to pi/2 since a square has
 * 	rotational symmetry of order four.
 * return value - This returns true if the above quantities could be computed from the picture, and
 * 	false otherwise. For example, false is returned if the block could not be found within the
 * 	image.
 */
bool CBlockReader::ComputeBlockLocation(double& blockRelPosn_x, double& blockRelPosn_y, double& blockRelRotation)
{
	// TODO: Come up with a good algorithm for the CBlockReader::ComputeBlockLocation(...) function.
}

