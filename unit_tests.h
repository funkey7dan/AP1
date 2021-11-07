//
// Created by funke on 11/5/2021.
//

#ifndef AP1_UNIT_TESTS_H
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "MainTrain.h"
#include <stdio.h>

#define AP1_UNIT_TESTS_H


class unit_tests {
public:
    void test_csv();
    void test_normal();
};


#endif //AP1_UNIT_TESTS_H
