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

	static void WriteCSV(const std::vector<std::vector<int> >& lines, const std::string& filePath);
	static void WriteCSV(const std::vector<std::vector<double> >& lines, const std::string& filePath);

	static void AppendCSV(const std::vector<int>& line, const std::string& filePath);
	static void AppendCSV(const std::vector<double>& line, const std::string& filePath);
	static void AppendCSV(const std::vector<std::vector<int> >& lines, const std::string& filePath);
	static void AppendCSV(const std::vector<std::vector<double> >& lines, const std::string& filePath);

	// === Exceptions ======================================================================================
	struct Exception_CantOpenFile
	{
		std::string m_filePath;
		Exception_CantOpenFile(std::string filePath)
				: m_filePath {filePath}
		{
		}
	};

private:
	// === Constructors and Destructors ====================================================================
	CParseCSV() {}
};


#endif /* SRC_CPARSECSV_H_ */
