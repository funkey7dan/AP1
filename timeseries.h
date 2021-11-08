#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <string>
#include <map>
//#include "SimpleAnomalyDetector.h"

using namespace std;

class TimeSeries {

private:
    const char *filename;
    // we are going to store the data in vector of vectors while each
    // vector is column in the file
    std::vector<std::pair<std::string, std::vector<float>>> data;
    std::map<string, int> col_name_to_index;

    // read from file to the vector
    // it is private because we will call it from the constructor only
    void constructDataBase();
    // vector of the correlation pairs indecises and their pearson correlation

public:
    explicit TimeSeries(const char *CSVfileName);

    const char *getFileName() const;

    vector<pair<std::string, std::vector<float>>> getDataBase() const;

    // get specific value from data
    float getValueFromVector(int i, int j) const; //row i column j
    void set_thershold(float new_thr)const;


    int getRowSize() const;
    int getColSize() const;
    string getColName(int i) const;
};

#endif /* TIMESERIES_H_ */