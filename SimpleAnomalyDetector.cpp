
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
        } // TODO: check plaster
        correlatedFeatures cf_temp;
        cf_temp.feature1 = ts.getColName(i);
        if(correlating_index==-1){
            continue;
        }
        cf_temp.feature2 = ts.getColName(correlating_index);
        cf_temp.corrlation = max_correlation;
        // TODO:calculate threshold for each pair
        cf_temp.threshold = 0.9;
        std::vector<Point*> points_arr = points_from_correlatedFeatures(dataBase[i].second,
                                                                       dataBase[correlating_index].second);
        Point **points;
        points = points_arr.data(); // TODO: check plaster

        cf_temp.lin_reg = linear_reg(points, points_arr.size());
        this->correlation_vector.push_back(cf_temp);
    }

}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}

