/*
 * anomaly_detection_util.cpp
 *
 * Authors: ***REMOVED*** Daniel Bronfman & 316163922 Tomer Pardilov
 */
#include <cmath>
#include <vector>
#include <memory>
//#include <stdexcept>
#include "anomaly_detection_util.h"


/**
 * Calculate the avg of a given range
 * @param x - array of floats
 * @param size - size of the sample
 * @return the avg of the range
 */
float avg(float *x, int size) {
    float sum = 0; // sum of the elements in the X array
//    if (size <= 0) {
//        throw std::runtime_error("Division by zero!\n");
//    }
    // sums all the elements in the array
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    // return the avg
    return sum / size;
}

/**
 * Calculate the variance of the given array
 * @param x array of floats
 * @param size size of the array
 * @return variance
 */
float var(float *x, int size) {
//    if (size <= 0) {
//        throw std::runtime_error("Division by zero!\n");
//    }
//    if (x == nullptr) {
//        throw "Array is a null ponter!";
//    }
    float mu = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i){
        sum += x[i] * x[i];
    }
    return sum / size - mu * mu;
}

/**
 * returns the covariance of X and Y
 * @param x array of floats.
 * @param y array of floats.
 * @param size size of arrays.
 * @return covariance between x and y.
 */
float cov(float *x, float *y, int size) {
    //xm and ym are the avgs of two given arrays.
//    if (size <= 0) {
//        throw std::runtime_error("Division by zero!\n");
//    }
//    if (x == nullptr || y == nullptr) {
//        throw "Array is a null ponter!";
//    }
    float xm = avg(x, size);
    float ym = avg(y, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i] * y[i];
    }
    return sum / size - xm * ym;
}

/**
 * returns the Pearson correlation coefficient of X and Y
 * @param x array of floats.
 * @param y array of floats.
 * @param size of x and y.
 * @return Pearson correlation coefficient.
 */
float pearson(float *x, float *y, int size) {
//    if (size <= 0) {
//        throw std::runtime_error("Division by zero!\n");
//    }
//    if (x == nullptr || y == nullptr) {
//        throw "Array is a null pointer!";
//    }
    //calculate the covariance
    float cov_xy = cov(x, y, size);
    //define the standard deviation of x and y
    float sig_x = sqrt(var(x, size));
    float sig_y = sqrt(var(y, size));
    return cov_xy / (sig_x * sig_y);
}

/**
 * performs a linear regression and returns the line equation
 * @param points array of point objects
 * @param size of array of points
 * @return a line that represents the linear regression
 */
Line linear_reg(Point **points, int size) {
//    if (size <= 0) {
//        throw std::runtime_error("Division by zero!\n");
//    }
//    if (points == nullptr) {
//        throw "Array is a null pointer!";
//    }
    float x_array[size], y_array[size], avg_x, avg_y, a, b;
    // create arrays of the x and y values
    for (int i = 0; i < size; i++) {
        x_array[i] = points[i]->x;
        y_array[i] = points[i]->y;
    }
    a = (cov(x_array, y_array, size)) / var(x_array, size);
    avg_x = avg(x_array, size);
    avg_y = avg(y_array, size);
    b = avg_y - a * avg_x;
    Line l = Line(a, b);
    return l;
}

/**
 * Create a vector of points from 2 correlated features
 * @param cf
 * @return
 */
std::vector<Point*> points_from_correlatedFeatures(std::vector<float> a, std::vector<float> b){
    std::vector<Point*> empty_vector;
    int len = a.size();
    for (int i=0;i<len;i++){
        Point* temp_point_p = new Point(a[i],b[i]);
        empty_vector.emplace_back((temp_point_p));
        //delete temp_point_p;
    }
    return empty_vector;
}

/**
 * returns the deviation between point p and the line
 * @param p single point
 * @param l single line
 * @return deviation between point Y and the expected location
 */
float dev(Point p, Line l) {
    float expected_y = l.f(p.x);
    float res = expected_y - p.y;
    //abs value
    if (res < 0)
        res *= -1;
    return res;
}

/**
 * returns the deviation between point p and the line equation of the points
 * @param p single point
 * @param points array of point objects
 * @param size of array of points
 * @return deviation between point p and the line equation
 */
float dev(Point p, Point **points, int size) {
//    if (points == nullptr) {
//        throw "Array is a null pointer!";
//    }
//    if (size <= 0) {
//        throw std::runtime_error("Division by zero!\n");
//    }
    Line line = linear_reg(points, size);
    return dev(p, line);
}



