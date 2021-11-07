
#include <tuple>
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

        for (int j = i + 1; j < len - 1; j++) {
            std::pair<std::string, std::vector<float>> temp_pair2 = (dataBase)[j];
            float *vect2 = temp_pair2.second.data();
            float pearson_value = abs(pearson(vect1, vect2, vector_size));
            if (pearson_value > max_correlation) {
                max_correlation = pearson_value;
                correlating_index = j;
            }
            if (max_correlation < this->threshold) {
                continue;
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
    // TODO Auto-generated destructor stub
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
}

