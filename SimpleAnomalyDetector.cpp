
#include <tuple>
#include <iostream>
#include <ostream>
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"


SimpleAnomalyDetector::SimpleAnomalyDetector() {
    threshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() = default;


void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub

    int len = ts.getRowSize(), vector_size = ts.getColSize(); // get number of columns
    vector<pair<basic_string<char>, vector<float>>> dataBase = ts.getDataBase();
    for (int i = 0; i < len; i++) {
        std::pair<std::string, std::vector<float>> temp_pair1 = (dataBase)[i];
        float *vect1 = temp_pair1.second.data();
        float max_correlation = 0;
        int correlating_index = -1;

        for (int j = i + 1; j < len; j++) {
            std::pair<std::string, std::vector<float>> temp_pair2 = (dataBase)[j];
            float *vect2 = temp_pair2.second.data();
            float pearson_value = abs(pearson(vect1, vect2, vector_size));
            if (pearson_value > max_correlation) {
                max_correlation = pearson_value;
                correlating_index = j;
            }
            if (max_correlation < this->threshold) {
                correlating_index = -1;
            }
        }
        if (correlating_index == -1) {
            continue;
        }
        correlatedFeatures cf_temp;
        init_feature(cf_temp, ts.getColName(i), ts.getColName(correlating_index),
                     dataBase[i].second, dataBase[correlating_index].second, max_correlation);
        this->cf.push_back(cf_temp);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> v_anom;
    for(correlatedFeatures a : cf){
        vector<float> col1 = ts.get_col_by_name(a.feature1);
        vector<float> col2 = ts.get_col_by_name(a.feature2);
        int len = col1.size();
        for(int i = 0; i < len; i++){
            Point p = Point(col1[i], col2[i]);
            float devf = dev(p, a.lin_reg);
            float threshold = a.threshold;
            if (devf > threshold){
                AnomalyReport ar = AnomalyReport(a.feature1 + "-" + a.feature2, i + 1);
                v_anom.push_back(ar);
            }
        }
    }
    return v_anom;
}

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

void SimpleAnomalyDetector::init_feature(correlatedFeatures &cf, string col1, string col2,
                                         vector<float> &v1, vector<float> &v2, float mc) {
    cf.feature1 = col1;
    cf.feature2 = col2;
    cf.corrlation = mc;
    std::vector<Point *> points_arr = points_from_correlatedFeatures(v1, v2);
    Point **points;
    points = points_arr.data();// TODO: check plaster

    cf.lin_reg = linear_reg(points, points_arr.size());
    cf.threshold = find_threshold(points, cf.lin_reg, points_arr.size()) * 1.1;
    for(int i = 0; i < points_arr.size(); i++)
        delete points_arr[i];
}

std::vector<Point *> SimpleAnomalyDetector::points_from_correlatedFeatures(std::vector<float> a, std::vector<float> b) {
    std::vector<Point *> empty_vector;
    int len = a.size();
    for (int i = 0; i < len; i++)
    {
        Point *temp_point_p = new Point(a[ i ], b[ i ]);
        empty_vector.emplace_back((temp_point_p));
        //delete temp_point_p;
    }
    return empty_vector;
}

