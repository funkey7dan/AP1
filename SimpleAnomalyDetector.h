#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_
#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

class TimeSeries;

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold; // the threshold for normal values
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	//vector<correlatedFeatures> cf;
    float threshold;
    std::vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    virtual float find_threshold(Point** points, Line l, int len);
    virtual void init_feature(correlatedFeatures &cf, string col1, string col2,
                              vector<float> &v1, vector<float> &v2, float mc);
	vector<correlatedFeatures> getNormalModel(){
		return this->cf;
	}
    static std::vector<Point *> points_from_correlatedFeatures(std::vector<float> a, std::vector<float> b);

};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
