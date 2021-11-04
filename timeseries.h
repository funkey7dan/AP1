#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <string>
#include "SimpleAnomalyDetector.h"

using namespace std;

class TimeSeries {

private:
    const char *filename;
    // we are going to store the data in vector of vectors while each
    // vector is column in the file
    std::vector<std::pair<std::string, std::vector<float>>> data;

    // read from file to the vector
    // it is private because we will call it from the constructor only
    void constructDataBase();
    // vector of the correlation pairs indecises and their pearson correlation
    mutable std::vector<correlatedFeatures> correlation_vector;
    mutable float thershold;

public:
    explicit TimeSeries(const char *CSVfileName);

    const char *getFileName() const;

    vector<pair<std::string, std::vector<float>>> getDataBase() const;

    // get specific value from data
    float getValueFromVector(int i, int j) const; //row i column j
    void set_thershold(float new_thr)const;

    void set_correlation_vector (std::vector<correlatedFeatures> to_set) const;

};

#endif /* TIMESERIES_H_ */