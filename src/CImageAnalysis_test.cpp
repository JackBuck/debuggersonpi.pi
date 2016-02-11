/*
 * CImageAnalysis_test.cpp
 *
 *  Created on: 20 Jan 2016
 *      Author: jack
 */

#include "CImageAnalysis.h"
#include <string>

int CImageAnalysis_test()
{

//	CImageAnalysis anImageAnalysis_1 {"TestData/CameraPhotos/Batch1/five.jpg"};
	CImageAnalysis anImageAnalysis_1 {"TestData/CameraPhotos/Batch2/testfiveh15cm1.jpg"};
	anImageAnalysis_1.PlayingAbout_BlobDetect();

	return 0;
}
