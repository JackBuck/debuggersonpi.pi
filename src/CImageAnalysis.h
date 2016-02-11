/*
 * CImageAnalysis.h
 *
 *  Created on: 20 Jan 2016
 *      Author: Jack Buckingham
 */

#ifndef SRC_CIMAGEANALYSIS_H_
#define SRC_CIMAGEANALYSIS_H_

#include <opencv2/opencv.hpp>
#include <string>

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *	This is a class which I will use when playing about with image analysis.
 */
class CImageAnalysis
{
public:
	// === Constructors and Destructors =============================================================
	CImageAnalysis(std::string imagePath);
	//virtual ~CImageAnalysis();

	// === Public Functions =========================================================================
	int PlayingAbout_CornerHarris();
	int PlayingAbout_BlobDetect();

private:
	// === Private Functions ========================================================================
	static void CornerHarris_trackbarCallback(int, void*);

	// === Member Variables =========================================================================
	cv::Mat image, image_gray;
	const int maxThresh { 255 };
	const char* sourceWindow = "Source image";
	const char* cornersWindow = "Corners detected";

};

#endif /* SRC_CIMAGEANALYSIS_H_ */
