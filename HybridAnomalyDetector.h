

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual void init_feature(correlatedFeatures &cf, string col1, string col2,
                              vector<float> &v1, vector<float> &v2, float mc);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
