#include "timeseries.h"
#include <fstream>
#include <sstream>
#include <iostream>

// constructor
TimeSeries::TimeSeries(const char *CSVfileName)
{

    this->filename = CSVfileName;
    constructDataBase();
}

// getter
std::vector<std::pair<std::string, std::vector<float>>> TimeSeries::getDataBase() const
{

    return this->data;
}

/**
 * private method that is called from constructor only
 * Reads a CSV file into a vector of <string, vector<int>> pairs where
 * each pair represents <column name, column values>
 */
void TimeSeries::constructDataBase()
{


    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open())
    { throw std::runtime_error("Could not open file"); }

    // Helper vars
    std::string line, colname;

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);
        int i = 0;
        // Extract each column name
        while (std::getline(ss, colname, ','))
        {
            // Initialize and add <colname, int vector> pairs to data
            this->data.push_back({colname, std::vector<float>{}});
            this->col_name_to_index.insert(pair<string, int>(colname, i));
            i++;
        }
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::istringstream ss(line);
        std::string token;

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each float
        while (std::getline(ss, token, ','))
        {
            // Add the current float-type to the 'colIdx' column's values vector
            this->data.at(colIdx).second.push_back(std::stof(token));
            // Increment the column index
            colIdx++;
        }
    }
    // Close file
    myFile.close();
}

/**
 *
 * @return the row size
 */
int TimeSeries::getRowSize() const
{

    return data.size();
}

/**
 *
 * @return the column length
 */
int TimeSeries::getColSize() const
{

    return data[ 0 ].second.size();
}

/**
 * Getter for column name by index
 * @param i index
 * @return the column name
 */
string TimeSeries::getColName(int i) const
{

    try
    {
        return this->data[ i ].first;
    }
    catch (exception& exception)
    {
        std::cout << "Can't access index" << endl;
    }
}

/**
 *
 * @param name the name of the column we want to get
 * @return a vector representation of the requested column.
 */
vector<float> TimeSeries::get_col_by_name(const std::string& name) const
{

    int index = this->col_name_to_index.at(name);
    return this->data[ index ].second;
}


