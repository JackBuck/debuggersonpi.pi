/*
 * CBlockReader.cpp
 *
 *  Created on: 24 Jan 2016
 *      Author: Jack Buckingham
 */

// ~~~ INCLUDES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CBlockReader.h"
#include "CParseCSV.h"
#include <cmath>

// ~~~ NAMESPACES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;
using namespace cv;

// -/-/-/-/-/-/-/ STATIC DATA INITIALISATION /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
/* ~~~ FILE / FOLDER PATHS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
// TODO: Learn how to do filenames portably so that it will run on Windows machines...
const std::string CBlockReader::imgExampleFolder {"Data/SpotImageExamples/"}; // In unix it is safe to concatenate filenames with two slashes :D
const std::string CBlockReader::expectedSpotDistancesFile {"Data/Calibration/ExpectedSpotDistances.csv"};


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
	LoadImgFromFile(imagePath);
}


// -/-/-/-/-/-/-/ INITIALISER FUNCTIONS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-
/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialises m_Image from a specified file.
 *
 * The image is resized immediately after loading.
 * The constructor throws an exception if the image could not be loaded.
 *
 * INPUTS:
 * 	imagePath - A string containing the path to an image to use to initialise the class instance.
 */
void CBlockReader::LoadImgFromFile(string imagePath)
{
	Mat image_fullsize = imread(imagePath, IMREAD_GRAYSCALE);
	if (image_fullsize.empty())
	{
		throw Exception_InputImagePath_BadFilePath { imagePath };
	}
	else
	{
		resize(image_fullsize, m_Image, Size(), 0.2, 0.2, INTER_AREA);
	}
}

/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *	This function uses the Pi's camera to take a photo. It will save the photo, update m_Image to use
 *	this photo and reset all member variables calculated using any previous image.
 *
 *	INPUTS:
 *	saveLocation - This should contain the path at which to save the photo.
 */
bool CBlockReader::TakePhoto(std::string saveLocation)
{
	// TODO: Find out how to take a photo with the PI camera and then implement CBlockReader::TakePhoto
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

	bool spotNbhdTest = VerifySpotNbhdVisible();
	bool spotArrangementTest = VerifySpotArrangement();

	// Temporary logging to console
	if (!spotNbhdTest)
		cout << "--Failed nbhd test--";
	if (!spotArrangementTest)
		cout << "--Failed arrangement test--";

	if ( spotNbhdTest & spotArrangementTest)
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
 * It does this by
 *  - computing the mean of the spot locations and subtracting it from the spots
 *  - sorting the spots by angle and radius (anticlockwise angle from pos x-axis)
 *  - computing the distances between all pairs of spots
 *  - comparing these distances with the expected distances, for each 'circular permutation' of the
 *    spots (i.e. a permutation which is a power of (1,...,n) ).
 *
 * This is an O(n^2) algorithm where n is the number of spots.
 *
 * By allowing a circular permutation of the spots, we are allowing for mismatching of measured and
 * expected spots due to rotation about the mean of the spots.
 * Ideally we would just look at the circular permutations which matched up groups of measured spots
 * with the same angle with groups of expected spots with the same angle (i.e. not split up groups).
 * However, it is easier to simply include all permutations round the circle, and rely on the ones
 * with split groups to fail the test (which they should!).
 *
 */
bool CBlockReader::VerifySpotArrangement()
{
	// Load expected spot distances
	vector<vector<double>> allExpectedSpotDistances =	CParseCSV::ReadCSV_double(expectedSpotDistancesFile);
	int startInd = m_Spots.size() * (m_Spots.size() - 1) / 2;
	int endInd = m_Spots.size() * (m_Spots.size() + 1) / 2; // Actually one more than the end ind...
	vector<vector<double>> expectedSpotDistances(allExpectedSpotDistances.begin() + startInd, allExpectedSpotDistances.begin() + endInd);

	// Compute distances between spots - return false if no spots
	if (!SortAndComputeSpotDists())
		return false;

	// Compare with expected spot distances
	for (unsigned int n = 0; n < m_Spots.size(); ++n) // Permute round circle by n points
	{
		bool match = true;
		for (unsigned int i = 0; i < m_Spots.size(); ++i)
		{
			for (unsigned int j = 0; j < m_Spots.size(); ++j)
			{
				match &= abs(expectedSpotDistances[(i+n) % m_SpotDists.size()][(j+n) % m_SpotDists.size()] - m_SpotDists[i][j]) < SPOTDISTTOL;
			}
		}

		if (match)
			return true;
	}

	return false;
}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function verifies that the spots are not too close to the edge of the image such that we
 * are at risk of cropping out extra spots.
 */
bool CBlockReader::VerifySpotNbhdVisible() const
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
bool CBlockReader::ComputeBlockLocation(double& blockRelPosn_x, double& blockRelPosn_y) const
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


// -/-/-/-/-/-/-/ CALIBRATION FUNCTIONS -/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
/* ~~~ FUNCTION (public) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function (re)writes the file containing the expected distances between spots.
 *
 * INPUTS:
 * fileNames - This should be a 5-element vector of strings. The ith element should contain the
 *    filename of the ith block. The folder containing these files is specified as a static
 *    constexpr in the class.
 *
 * WRITES FILES:
 * The program writes the file containing the expected distances between spots. The location of this
 * 	file is a static constexpr of the class.
 *
 */
void CBlockReader::SetExpectedSpotDistances(const vector<string>& fileNames)
{
	if (fileNames.size() != 5)
		throw Exception_InputImagePath_BadFilePath { fileNames };

	CParseCSV::WriteCSV(vector<double>(), expectedSpotDistancesFile, ios::out);
	vector<vector<double>> expectedSpotDistances;
	for (unsigned int i = 0; i < 5; ++i)
	{
		LoadImgFromFile(imgExampleFolder+fileNames[i]);
		DetectSpots();
		SortAndComputeSpotDists();

		CParseCSV::WriteCSV(m_SpotDists, expectedSpotDistancesFile, ios::app);
	}
}


// -/-/-/-/-/-/-/ HELPER FUNCTIONS /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
/* ~~~ STRUCT (emulating private function) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function will compare two vectors of cv::Point2f. If one point is further round the circle
 * than the other, then it will be deemed larger. If two points are the same angle round the circle,
 * up to tolerence, then the radius will be used to sort them.
 * Angles are measured anticlockwise from the positive x-axis.
 * The angle given to (0,0) (and points within angTol of this) is zero. Hence any such point will be
 * smaller than any non (0,0) point.
 *
 * MEMBER VARIABLES:
 * angTol - If the angle computed (in RADIANS) for the two points is less than angTol then the
 * 	points will be deemed to have the same angle.
 * radTol - If a point has norm less than radTol then it will be deemed to be zero.
 *
 * OPERATOR():
 * 	If point1 < point2 by the algorithm defined above, then the function returns true. Else it
 * 	returns false.
 *
 */
CBlockReader::CompareByAngleThenRadius::CompareByAngleThenRadius()
		: m_AngTol {ANGTOL}, m_RadTol {RADTOL}
{
}

bool CBlockReader::CompareByAngleThenRadius::operator ()(const Point2f point1, const Point2f point2) const
{
	// Compute radii squared
	double point1_rad2 = point1.x * point1.x + point1.y * point1.y;
	double point2_rad2 = point2.x * point2.x + point2.y * point2.y;

	// Check neither point is the centre point
	if (point2_rad2 < m_RadTol * m_RadTol)
		return false; // point2 <= point1

	if (point1_rad2 < m_RadTol * m_RadTol)
		return true; // point1 == (0,0) < point2 (would have returned false in previous statement if point2 == (0,0) as well)

	// Compute angles
	double point1_ang = atan2(point1.y, point1.x);
	double point2_ang = atan2(point2.y, point2.x);
	// TODO: Declare and check errorno - see page 918 of C++ book

	// Compare angles
	if (abs(point1_ang - point2_ang) < m_AngTol
			|| abs(point1_ang - point2_ang) > 2 * M_PI - m_AngTol)
	{
		// If the points have the same angle
		if (point1_rad2 < point2_rad2)
			return true;
		else
			return false;
	}
	else if (point1_ang < point2_ang)
		return true;
	else // If point 2 has the smaller angle
		return false;

}

/* ~~~ FUNCTION (private) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This function sorts a copy of m_spots (with the mean spot location subtracted), then computes the
 * distances between them. The sorting is done using CompareByAngleThenRadius.
 *
 * MEMBER VARIABLES READ:
 * m_Spots
 *
 *	MEMBER VARIABLES SET:
 * m_SpotDists - This is updated to include the distances between the spots. Note that since m_Spots
 * 	isn't itself sorted by this function, the indices in m_SpotDists do not correspond to those in
 * 	m_Spots.
 *
 */
bool CBlockReader::SortAndComputeSpotDists()
{
	// Compute mean spot location
	double meanLoc_x {0};
	double meanLoc_y {0};
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		meanLoc_x += m_Spots[i].pt.x;
		meanLoc_y += m_Spots[i].pt.y;
	}

	if (m_Spots.size() == 0)
	{
		m_SpotDists.clear();
		return false;
	}
	else
	{
		meanLoc_x /= m_Spots.size();
		meanLoc_y /= m_Spots.size();
	}

	// Centre points by subtracting mean
	vector<Point2f> centredSpots {};
	centredSpots.reserve(m_Spots.size());
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
	{
		Point2f aSpot = m_Spots[i].pt;
		aSpot.x -= meanLoc_x;
		aSpot.y -= meanLoc_y;
		centredSpots.push_back(aSpot);
	}

	// Sort centredSpots
	// TODO: Debug sorting with testfourh15cm4.jpg
	sort(centredSpots.begin(), centredSpots.end(), CompareByAngleThenRadius {});

	// Find average spot size
	double avSpotSize {0};
	for (unsigned int i = 0; i < m_Spots.size(); ++i)
		avSpotSize += m_Spots[i].size;
	avSpotSize /= m_Spots.size();

	// Compute distances between spots
	m_SpotDists = vector<vector<double> > (centredSpots.size(), vector<double>(centredSpots.size(), -1));
	for (unsigned int i = 0; i < m_SpotDists.size(); ++i)
	{
		for (unsigned int j = 0; j < m_SpotDists.size(); ++j)
		{
			double xDiff = centredSpots[i].x - centredSpots[j].x;
			double yDiff = centredSpots[i].y - centredSpots[j].y;

			m_SpotDists[i][j] = sqrt(xDiff * xDiff + yDiff * yDiff) / avSpotSize;
		}
	}

	// Return success
	return true;
}



