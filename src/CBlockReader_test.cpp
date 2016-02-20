/*
 * CBlockReader_test.cpp
 *
 *  Created on: 24 Jan 2016
 *      Author: Jack Buckingham
 */

#include "CBlockReader.h"
#include <iostream>

using namespace std;

// This test generates the spot distances calibration file
void CBlockReader_test()
{
	cout << "--CBlockReader_test--\n\n";

	vector<string> fileNames
	{
			"testoneh15cm2.jpg",
			"testtwoh15cm2.jpg",
			"testthreeh15cm2.jpg",
			"testfourh15cm3.jpg",
			"testfiveh15cm1.jpg"
	};

	cout << "Writing spot distances calibration file...";
	CBlockReader aBlockReader;
	aBlockReader.SetExpectedSpotDistances(fileNames);
	cout << " done!\n";

}

int CBlockReader_test2()
{
	cout << "--CBlockReader_test2--\n\n";
	string folderName {"TestData/CameraPhotos/Batch2/"};
	vector<string> fileNames
	{
			"testoneh15cm1.jpg",
			"testtwoh15cm1.jpg",
			"testthreeh15cm3.jpg",
			"testfourh15cm4.jpg",
			"testfiveh15cm4.jpg"
	};

	bool success = true;
	for (unsigned int i = 0; i < fileNames.size(); ++i)
	{
		cout << "i+1 = " << i+1 << ",   Num Spots Counted = ";
		CBlockReader aBlockReader {folderName + fileNames[i]};
		int numSpots = aBlockReader.CountSpots();
		cout << numSpots << endl;

		if (i+1 != numSpots)
			success = false;
	}

	if (success)
	{
		cout << "Success!\n";
		return 0;
	}
	else
	{
		cout << "Failure!\n";
		return 1;
	}
}
