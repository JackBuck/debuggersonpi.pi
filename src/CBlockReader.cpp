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
	if (image_fullsize.empty())
	{
		throw InputImagePath_BadFilePath { imagePath };
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
	DetectSpots();

	if (VerifySpotNbhdVisible() & VerifySpotArrangement())
		return m_Spots.size();
	else
		return -1;
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function uses the opencv SimpleBlobDetector to identify the spots in the picture. The spots
 * are filtered based on their area, circularity, convexity and inertia.
 */
void CBlockReader::DetectSpots()
{
	////////////////////////////////////////////////////////////
	// Setup SimpleBlobDetector Parameters.

	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 10;
	params.maxThreshold = 200;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 500;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.7;

	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.8;

	////////////////////////////////////////////////////////////
	// Detect Spots

	SimpleBlobDetector detector(params);
	detector.detect(m_Image, m_Spots);
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function verifies that the spots are in the expected arrangement for that number of spots.
 * That is, it verifies that they are related to the expected arrangement by a non-reflecting
 * isometry. That is, by a rotation and a translation.
 *
 * Let X be an nx2 matrix containing the coordinates of the n spots, relative to the mean spot. That
 * is, compute the mean location of the spots, and subtract it from the coordinates of each spot to
 * obtain X. Do similarly with the expected arrangement for n spots to obtain a matrix Y. We wish to
 * verify that there exist an orthogonal matrix Q and a permutation matrix P such that X = PYQ.
 *
 * This is done by computing a singular value decomposition X = USV'. Here S is diagonal of the same
 * shape as X, with descending diagonal elements, and U and V are orthogonal (and hence square).
 * Matrix transpose is denoted '.
 *
 *	If the singular values (diagonal elements of S) are distinct, then V is determined uniquely, as
 *	are the first two columns of U. The remaining columns of U are unconstrained (so long as U
 *	remains orthogonal). Hence, computing a singular value decomposition of Y, say Y = WTZ' for T
 *	diagonal and W and Z orthogonal, it suffices to check that T = S and that the first two columns
 *	of U can be transformed into the first two columns of V by a permutation P of the rows.This is
 *	done by sorting the rows of U and comparing with the values in the first two columns of W
 *	(equality up to some tolerance that is).
 *
 *	If the singular values of X are the same, then we still require that they match the singular
 *	values of Y. However, everything commutes with scalar matrices, so we have the more general
 *	problem of determining whether the first two columns of U span the same space as the first two
 *	columns of W, possibly after a permutation of the rows. For each permutation of the rows, we can
 *	take the dot product between the first column of U and the first two columns of W. If the sum of
 *	the squares of these gives the square of the norm of the first column of U then it lies in the
 *	span of the first two columns of W (W is orthogonal). Similarly with the second column. If both
 *	the first two columns of U lie in the span of the first two columns of W, then their span is the
 *	same (since U is invertible). Since U and W are at most 5x5, there are only 120 permutations of
 *	the rows, so this is feasible.
 *
 */
bool CBlockReader::VerifySpotArrangement()
{
	// Compute SVD of X
	vector<double> X1(m_Spots.size());
	vector<double> X2(m_Spots.size());

	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		X1[i] = m_Spots[i].pt.x;
		X2[i] = m_Spots[i].pt.y;
	}

	// TODO: Finish this function!
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function verifies that the spots are not too close to the edge of the image such that we
 * are at risk of cropping out extra spots.
 */
bool CBlockReader::VerifySpotNbhdVisible()
{
	double minSpotPadding = 1; // A proportion of the diameter of the spot

	bool result = true;
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		double distFromLeftEdge = m_Spots[i].pt.x;
		double distFromRightEdge = m_Image.cols - m_Spots[i].pt.x;
		double distFromTopEdge = m_Spots[i].pt.y;
		double distFromBottomEdge = m_Image.rows - m_Spots[i].pt.y;

		if (distFromLeftEdge < minSpotPadding * m_Spots[i].size)
		{
			result = false;
		}
		else if (distFromRightEdge < minSpotPadding * m_Spots[i].size)
		{
			result = false;
		}
		else if (distFromTopEdge < minSpotPadding * m_Spots[i].size)
		{
			result = false;
		}
		else if (distFromBottomEdge < minSpotPadding * m_Spots[i].size)
		{
			result = false;
		}
	}

	return result;
}



// -/-/-/-/-/-/-/ BLOCK LOCATION FUNCTIONS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function analyses the image to determine the position of the block relative to the robot.
 * This is useful for providing feedback to the caller when the picture supplied to the CBlockReader
 * is rejected when counting the spots.
 *
 * OUTPUTS:
 * blockRelPosn_x - The x-coordinate of the approximate centre of the block in the image frame.
 * blockRelPosn_y - The y-coordinate of the approximate centre of the block in the image frame.
 * return value - This returns true if the above quantities could be computed from the picture, and
 * 	false otherwise. For example, false is returned if the block could not be found within the
 * 	image.
 */
bool CBlockReader::ComputeBlockLocation(double& blockRelPosn_x, double& blockRelPosn_y)
{
	blockRelPosn_x = 0;
	blockRelPosn_y = 0;

	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		blockRelPosn_x += m_Spots[i].pt.x;
		blockRelPosn_y += m_Spots[i].pt.y;
	}

	if (m_Spots.size() == 0)
		return false;
	else
	{
		blockRelPosn_x /= m_Spots.size();
		blockRelPosn_y /= m_Spots.size();
		return true;
	}

}


