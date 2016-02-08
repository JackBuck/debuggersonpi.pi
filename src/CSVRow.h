/*
 * CSVRow.h
 *
 *  Created on: 8 Feb 2016
 *      Author: Jack Buckingham
 *
 *  Credit goes to http://stackoverflow.com/users/14065/loki-astari
 *  The class has been lifted from
 *  http://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
 *
 */

#ifndef SRC_CSVROW_H_
#define SRC_CSVROW_H_

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVRow
{
public:
	std::string const& operator[](std::size_t index) const
			{
		return m_data[index];
	}

	std::size_t size() const
	{
		return m_data.size();
	}

	void readNextRow(std::istream& str);

private:
	std::vector<std::string> m_data;

};

std::istream& operator>>(std::istream& str,CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

#endif /* SRC_CSVROW_H_ */
