
#include <tuple>
#include <utility>
#include "SimpleAnomalyDetector.h"

// constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    threshold = 0.9;
}
// destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;

/**
 * function to learn the normal values for the provided timeseries object
 * @param ts the timeseries object we use to learn the normal state
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {

    int len = ts.getRowSize(), vector_size = ts.getColSize(); // get number of columns
    vector<pair<basic_string<char>, vector<float>>> dataBase = ts.getDataBase();
    /*
     *  we iterate through the columns we have in the database, using two loops
     *  the first loop dictates the first feature which we will compare via the second loop to all the other features.
     */
    for (int i = 0; i < len; i++) {
        // get a column represented by a column name and a vector of the values in the column
        std::pair<std::string, std::vector<float>> temp_pair1 = (dataBase)[i];
        float *vect1 = temp_pair1.second.data();
        // start the max correlation from 0
        float max_correlation = 0;
        int correlating_index = -1;
        // second, inner loop, for iterating over the second feature
        for (int j = i + 1; j < len; j++) {
            std::pair<std::string, std::vector<float>> temp_pair2 = (dataBase)[j];
            float *vect2 = temp_pair2.second.data();
            // get pearson absolute value
            float pearson_value = abs(pearson(vect1, vect2, vector_size));
            if (pearson_value > max_correlation) {
                max_correlation = pearson_value;
                correlating_index = j;
            }
            // if the max correlation we found is less than the threshold we defined, this index should be ignored
            if (max_correlation < this->threshold) {
                correlating_index = -1;
            }
        }
        // if the index is -1 it means no meaningful correlation was found
        if (correlating_index == -1) {
            continue;
        }
        correlatedFeatures cf_temp;
        // function to initialize the features
        init_feature(cf_temp, ts.getColName(i), ts.getColName(correlating_index),
                     dataBase[i].second, dataBase[correlating_index].second, max_correlation);
        // insert the correlation features we found into the correlation features vector
        this->cf.push_back(cf_temp);
    }
}
/**
 * a function to detect anomalies in a timeseries object.
 * We iterate through the features we found correkative and saved in cf, and for each pair of features we check the
 * provided timeseries line by line. If any of the features we found to be have a high deviation from the line
 * we found in the normal data, we create a new anomaly report object.
 * @param ts the time series we check for anomalies.
 * @return v_anom - a vector of all the anomalies we found.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> v_anom;
    /*
     * iterate through the correlative pairs we found
     */
    for(correlatedFeatures const& a : cf){
        vector<float> col1 = ts.get_col_by_name(a.feature1);
        vector<float> col2 = ts.get_col_by_name(a.feature2);
        int len = col1.size();
        /*
         * iterate through the row and create points from the values
         */
        for(int i = 0; i < len; i++){
            Point p = Point(col1[i], col2[i]);
            // calculate the deviation of the point from the normal line
            float devf = dev(p, a.lin_reg);
            float threshold_margin = a.threshold;
            // check if the deviation is withing accepted margins. If not, report anomaly.
            if (devf > threshold_margin){
                AnomalyReport ar = AnomalyReport(a.feature1 + "-" + a.feature2, i + 1);
                v_anom.push_back(ar);
            }
        }
    }
    return v_anom;
}

/**
 * A function to calculate the normal threshold.
 * @param points - the values in the normal data input
 * @param l - linear regression line.
 * @param len length of points array
 * @return the maximal deviation of the normal data from the line
 */
float SimpleAnomalyDetector::find_threshold(Point **points, Line l, int len) {
    float max = 0;
    for (int i = 0; i < len; i++) {
        float deviation = dev(*points[i], l);
        if (deviation > max) {
            max = deviation;
        }
    }
    return max;
}

/**
 * Helper function to initialize all the fields of a correlatedFeatures object.
 * @param cf vector of correlated features
 * @param col1 Name of the first column of the data table
 * @param col2 Name of the second column of the data table
 * @param v1 vector of the values of the first column
 * @param v2 vector of the values of the second column
 * @param mc the maximal correlation
 */
void SimpleAnomalyDetector::init_feature(correlatedFeatures &cf, string col1, string col2,
                                         vector<float> &v1, vector<float> &v2, float mc) {
    cf.feature1 = std::move(col1);
    cf.feature2 = std::move(col2);
    cf.corrlation = mc;
    // create a vector of points from 2 vectors of values (generate all the points)
    std::vector<Point *> points_arr = points_from_correlatedFeatures(v1, v2);
    Point **points;
    points = points_arr.data();
    cf.lin_reg = linear_reg(points, points_arr.size());
    cf.threshold = find_threshold(points, cf.lin_reg, points_arr.size()) * 1.1;
    // free all the data
    for(auto & i : points_arr)
        delete i;
}

/**
 * Helper function to create a vector of points from two vectors of values.
 * @param a the x values vector
 * @param b the y values vector
 * @return
 */
std::vector<Point *> SimpleAnomalyDetector::points_from_correlatedFeatures(std::vector<float> a, std::vector<float> b) {
    std::vector<Point *> empty_vector;
    int len = a.size();
    /*
     * iterate through all the values in the vector and create points from them
     */
    for (int i = 0; i < len; i++)
    {
        auto *temp_point_p = new Point(a[ i ], b[ i ]);
        empty_vector.emplace_back((temp_point_p));
    }
    return empty_vector;
}

