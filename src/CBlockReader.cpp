/*
 * CBlockReader.cpp
 *
 *  Created on: 24 Jan 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CBlockReader.h"
#include <cmath>

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
 */
bool CBlockReader::VerifySpotArrangement()
{
	// Define tolerance to use in this function
	double tol = 5; // pixels

	// Compute mean spot location
	double meanLoc_x {0};
	double meanLoc_y {0};
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		meanLoc_x += m_Spots[i].pt.x;
		meanLoc_y += m_Spots[i].pt.y;
	}

	if (m_Spots.size() == 0)
		return false;
	else
	{
		meanLoc_x /= m_Spots.size();
		meanLoc_y /= m_Spots.size();
	}

	// Extract mean corrected x and y values
	vector<double> xValues (m_Spots.size());
	vector<double> yValues (m_Spots.size());

	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		xValues[i] = m_Spots[i].pt.x - meanLoc_x;
		yValues[i] = m_Spots[i].pt.y - meanLoc_y;
	}

	// Remove centre spot if it exists
	int centreSpot = -1;
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		if (abs(xValues[i]) < tol && abs(yValues[i]) < tol)
		{
			if (centreSpot > -1)
			{
				// TODO: Throw exception
			}
			else
			{
				centreSpot = i;
			}
		}
	}

	// Sort remaining spots by angle, then radial position
	vector<double> angles (m_Spots.size());
	vector<double> radii_sq (m_Spots.size());
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		if (i != centreSpot)
		{
			angles[i] = atan2(yValues[i], xValues[i]);
			radii_sq[i] = pow(xValues[i], 2) + pow(yValues[i], 2);
		}
	}

	// TODO: The actual sorting...

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


