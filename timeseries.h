#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <vector>
#include <string>
#include <map>

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
    vector<float> get_col_by_name(const std::string& name) const;
    vector<pair<std::string, std::vector<float>>> getDataBase() const;

    int getRowSize() const;
    int getColSize() const;
    string getColName(int i) const;
};

#endif /* TIMESERIES_H_ */