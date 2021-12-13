#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_
#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

class TimeSeries;

// for EX3+4 we can ADD to this struct but not change it.
struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
    Circle circ_reg = Circle(Point(0, 0), -1);
	float threshold; // the threshold for normal values
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	//vector<correlatedFeatures> cf;
    //float threshold;

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

    virtual bool is_anomalous(Point p, correlatedFeatures features);

protected:
    std::vector<correlatedFeatures> cf;
    float threshold;
};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
