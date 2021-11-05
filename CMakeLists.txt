cmake_minimum_required(VERSION 3.20)
project(AP1)

set(CMAKE_CXX_STANDARD 11)

add_executable(AP1 unit_tests.cpp timeseries.cpp SimpleAnomalyDetector.cpp anomaly_detection_util.cpp MainTrain.cpp)
