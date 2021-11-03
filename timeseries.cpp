#include <fstream>
#include <sstream>
#include "timeseries.h"

// constructor
TimeSeries::TimeSeries(const char *CSVfileName) {
    this->filename = CSVfileName;
    constructDataBase();
}

// getter
const char *TimeSeries::getFileName() const{
    return filename;
}

// getter
std::vector<std::pair<std::string, std::vector<float>>> TimeSeries::getDataBase() const{
    return data;
}

// get specific value from data
float TimeSeries::getValueFromVector(int i, int j) const{
    return data.at(j).second.at(i);
}

// private method that is called from constructor only
void TimeSeries::constructDataBase() {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    float val;

    // Read the column names
    if (myFile.good()) {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {

            // Initialize and add <colname, int vector> pairs to data
            this->data.push_back({colname, std::vector<float>{}});
        }
    }

    // Read data, line by line
    while (std::getline(myFile, line)) {
        // Create a stringstream of the current line
        std::istringstream ss(line);
        std::string token;

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each float
        while (std::getline(ss, token, ',')) {
            // Add the current float-type to the 'colIdx' column's values vector
            this->data.at(colIdx).second.push_back(std::stof(token));
            // Increment the column index
            colIdx++;
        }
    }
    // Close file
    myFile.close();
}