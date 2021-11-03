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
    // read from file to the vector
    // it is private because we will call it from the constructor only
    void constructDataBase();

public:
    explicit TimeSeries(const char* CSVfileName);
    const char* getFileName() const;
    vector<pair<std::string, std::vector<float>>> getDataBase() const;
    //row i column j
    float getValueFromVector(int i, int j) const;
};

#endif /* TIMESERIES_H_ */