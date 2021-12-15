
#include "HybridAnomalyDetector.h"
/*
 * this class inherits SimpleAnomalyDetector.
 * we use it when threshold in learnNormal is between 0.9 and 0.5.
 */
HybridAnomalyDetector::HybridAnomalyDetector() {
}
/**
 * destructor
 */
HybridAnomalyDetector::~HybridAnomalyDetector() {
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
void HybridAnomalyDetector::init_feature(correlatedFeatures &cf, string col1, string col2, vector<float> &v1,
                                         vector<float> &v2, float mc) {
    SimpleAnomalyDetector::init_feature(cf, col1, col2, v1, v2, mc);
    if (mc > 0.5 && mc < threshold) {
        cf.feature1 = std::move(col1);
        cf.feature2 = std::move(col2);
        cf.corrlation = mc;
        // create a vector of points from 2 vectors of values (generate all the points)
        std::vector<Point *> points_arr = points_from_correlatedFeatures(v1, v2);
        Point **points;
        points = points_arr.data();
        //cf.lin_reg = Line(0, 0);
        cf.circ_reg = findMinCircle(points,points_arr.size());
        cf.threshold = cf.circ_reg.radius * 1.1;
        // free all the data
        for (auto &i: points_arr)
            delete i;
        this->cf.push_back(cf);
    }
}
