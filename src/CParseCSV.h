/*
 * CParseCSV.h
 *
 *  Created on: 8 Feb 2016
 *      Author: Jack Buckingham
 */

#ifndef SRC_CPARSECSV_H_
#define SRC_CPARSECSV_H_

#include <vector>
#include <string>

/* ~~~ CLASS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This is a class to read and write from a csv file.
 */
class CParseCSV
{
public:
	// === Public Static Functions =========================================================================
	static std::vector<std::vector<int> > ReadCSV_int(const std::string& filePath);
	static std::vector<std::vector<double> > ReadCSV_double(const std::string& filePath);

private:
	// === Constructors and Destructors ====================================================================
	CParseCSV() {}
};


#endif /* SRC_CPARSECSV_H_ */
