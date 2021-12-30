cmake_minimum_required(VERSION 3.20)
project(AP1)

set(CMAKE_CXX_FLAGS -pthread)

#add_executable(AP1 timeseries.cpp SimpleAnomalyDetector.cpp anomaly_detection_util.cpp main.cpp MainTrain.cpp)
add_executable(AP1 timeseries.cpp SimpleAnomalyDetector.cpp anomaly_detection_util.cpp minCircle.cpp
        HybridAnomalyDetector.cpp CLI.cpp MainTrain.cpp Server.cpp)
