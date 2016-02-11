/*
 * CImageAnalysis.cpp
 *
 *  Created on: 20 Jan 2016
 *      Author: jack
 */

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "CImageAnalysis.h"

using namespace cv;
using namespace std;

CImageAnalysis::CImageAnalysis(string imagePath)
{
	// TODO Auto-generated constructor stub

	// Load image
	Mat image_orig = imread(imagePath, IMREAD_GRAYSCALE);
	if ( image_orig.empty() )
	{
		cout << "Could not open or find the image" << endl;
		image = Mat();
	}
	else
	{
		resize(image_orig, image, Size(), 0.2, 0.2, INTER_AREA);
	}
}

int CImageAnalysis::PlayingAbout_CornerHarris()
{
	// Convert to Grayscale
	cvtColor( image, image_gray, COLOR_BGR2GRAY );

	// Set up window
	namedWindow( sourceWindow, WINDOW_AUTOSIZE );

	// -- Make it static, and pass the object instance?
	int thresh = maxThresh;
	createTrackbar( "Threshold: ", sourceWindow, &thresh, maxThresh, &CImageAnalysis::CornerHarris_trackbarCallback, this);
	imshow( sourceWindow, image_gray );

	CornerHarris_trackbarCallback(thresh,this);

	waitKey(0);
	destroyWindow(sourceWindow);
	destroyWindow(cornersWindow);

	return 0;
}

void CImageAnalysis::CornerHarris_trackbarCallback(int thresh, void* object)
{
	CImageAnalysis* myImageAnalysis = (CImageAnalysis*) object;

	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros( myImageAnalysis->image.size(), CV_32FC1 );

	int blockSize = 7;
	int apertureSize = 3;
	double k = 0.1;

	cornerHarris( myImageAnalysis->image_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
	normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( dst_norm, dst_norm_scaled );
	for( int j = 0; j < dst_norm.rows ; j++ )
	{ for( int i = 0; i < dst_norm.cols; i++ )
	{
		if( (int) dst_norm.at<float>(j,i) > thresh )
		{
			circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(255,255,255), 2, 8, 0 );
		}
	}
	}
	namedWindow( myImageAnalysis->cornersWindow, WINDOW_AUTOSIZE);
	imshow( myImageAnalysis->cornersWindow, dst_norm_scaled );
}

int CImageAnalysis::PlayingAbout_BlobDetect()
{
//	auto startTime = chrono::steady_clock::now();

	// Setup SimpleBlobDetector parameters.
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

	// Set up detector with params
	SimpleBlobDetector detector(params);

	// Detect blobs
	vector < KeyPoint > keyPoints;
	detector.detect(image, keyPoints);

//	auto endTime = chrono::steady_clock::now();
//	cout << chrono::duration <double, milli> (endTime - startTime).count() << " ms" << endl;

	// Draw detected blobs as red circles
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat imageWithKeypoints;
	drawKeypoints(image, keyPoints, imageWithKeypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Print number of spots and spot info
	cout << "Found " << keyPoints.size() << " points:\n";
	for (unsigned int i = 0; i < keyPoints.size(); ++i)
	{
		cout << "  Size " << keyPoints[i].size
				<< ",\tlocation " << keyPoints[i].pt
				<< '\n';
	}

	// Show blobs
	namedWindow( sourceWindow, WINDOW_AUTOSIZE);
	imshow(sourceWindow, imageWithKeypoints);
	waitKey(0);

	return 0;
}

