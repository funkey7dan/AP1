#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <string>

using namespace std;

class TimeSeries{
private:
    const char* filename;
    // we are going to store the data in vector of vectors while each
    // vector is column in the file
    std::vector<std::pair<std::string, std::vector<float>>> data;
    // pass vector of vectors by reference - there we will read from file to the vector
    // it is private because we will call it from the constructor only
    void constructDataBase(std::vector<std::pair<std::string, std::vector<float>>>& data);

public:
    explicit TimeSeries(const char* CSVfileName);
    const char* getFileName();
    vector<pair<std::string, std::vector<float>>> getDataBase();
    //row i column j
    float getValueFromVector(int i, int j);
};

#endif /* TIMESERIES_H_ */