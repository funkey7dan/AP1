//
// Created by funke on 11/5/2021.
//

#include <iostream>
#include "unit_tests.h"
int main(){
    srand (time(NULL));
    float a1=1+rand()%10, b1=-50+rand()%100;
    float a2=1+rand()%20 , b2=-50+rand()%100;


    // test the learned model: (40 points)
    // expected correlations:
    //	A-C: y=a1*x+b1
    //	B-D: y=a2*x+b2

	// test the learned model: (40 points)
	// expected correlations:
	//	A-C: y=a1*x+b1
	//	B-D: y=a2*x+b2

	generateTrainCSV(a1,b1,a2,b2);
	TimeSeries ts("trainFile1.csv");
	SimpleAnomalyDetector ad;
	ad.learnNormal(ts);
	vector<correlatedFeatures> cf=ad.getNormalModel();

	if(cf.size()!=2) {
        std::cout << cf.size() << std::endl;
        std::cout << "wrong size of correlated features (-40)" << std::endl;
    }
	else
	for_each(cf.begin(),cf.end(),[&a1,&b1,&a2,&b2](correlatedFeatures c){
		checkCorrelationTrain(c,"A","C",a1,b1); // 20 points
		checkCorrelationTrain(c,"B","D",a2,b2); // 20 points
	});
    return 0;
}