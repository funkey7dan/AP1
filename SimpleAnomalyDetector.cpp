
#include <tuple>
#include "SimpleAnomalyDetector.h"


SimpleAnomalyDetector::SimpleAnomalyDetector() {
    threshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
    // vector to hold the most correlating column for each column - pair of indices
    vector<correlatedFeatures> correlations_vector;
    int len = ts.getRowSize(), vector_size = ts.getColSize(); // get number of columns
    for (int i = 0; i < len; i++) {
        auto vect1 = ts.getDataBase()[i].second.data();
        float max_correlation = 0;
        int correlating_index = -1;
        for (int j = i + 1; i < len; j++) {
            auto vect2 = ts.getDataBase()[j].second.data();
            float pearson_value = abs(pearson(vect1, vect2, vector_size));
            if (pearson_value > max_correlation) {
                max_correlation = pearson_value;
                correlating_index = j;
            }
        }
        correlatedFeatures cf_temp;
        cf_temp.feature1 = ts.getColName(i);
        cf_temp.feature2 = ts.getColName(correlating_index);
        cf_temp.corrlation = max_correlation;
        // TODO:calculate threshold for each pair
        cf_temp.threshold = 0.9;
        std::vector<Point> points_arr = points_from_correlatedFeatures(ts.getDataBase()[i].second,
                                                                       ts.getDataBase()[correlating_index].second);
        Point **points;
        *points = &points_arr[0];
        cf_temp.lin_reg = linear_reg(points,points_arr.size());
//        cf_temp->(linear_reg(points,points_arr.size()));
        correlations_vector.push_back(cf_temp);
    }
    ts.set_correlation_vector(correlations_vector);
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}

