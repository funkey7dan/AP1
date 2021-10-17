/*
 * anomaly_detection_util.cpp
 *
 * Author: Insert name and ID
 */
#include <cmath>
#include <cstddef>
#include <math.h>
#include "anomaly_detection_util.h"

/**
 * Calculate the avg of a given range
 * @param x - array of floats
 * @param size - size of the sample
 * @return the avg of the range
 */
float avg(float *x, int size) {
    float sum = 0; // sum of the elements in the X array

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
    if (size <= 0) {
        throw "Division by zero!";
    }
//    if (x == NULL) {
//        throw "Array is a null ponter!";
//    }
    float mu = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow((x[i] - mu), 2);
    }
    return sum / size;
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
    if (size <= 0) {
        throw "Division by zero!";
    }
//    if (x == NULL || y==NULL) {
//        throw "Array is a null ponter!";
//    }
    float xm = avg(x, size);
    float ym = avg(y, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += (x[i] - xm) * (y[i] - ym);
    }
    return sum / size;
}

/**
 * returns the Pearson correlation coefficient of X and Y
 * @param x array of floats.
 * @param y array of floats.
 * @param size of x and y.
 * @return Pearson correlation coefficient.
 */
float pearson(float *x, float *y, int size) {
    if (size <= 0) {
        throw "Division by zero!";
    }
//    if (x == NULL || y==NULL) {
//        throw "Array is a null ponter!";
//    }
    //calculate the covariance
    float cov_xy = cov(x, y, size);
    //define the standard deviation of x and y
    float sig_x = pow(var(x, size), 0.5);
    float sig_y = pow(var(y, size), 0.5);
    return cov_xy / (sig_x * sig_y);
}

/**
 * performs a linear regression and returns the line equation
 * @param points
 * @param size
 * @return a line that represents the linear regression
 */
Line linear_reg(Point **points, int size) {
    if (size <= 0) {
        throw "Division by zero!";
    }
//    if (points == NULL) {
//        throw "Array is a null ponter!";
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
    return Line(a, b);
}

/**
 * returns the deviation between point p and the line
 * @param p
 * @param l
 * @return deviation between point Y and the expected location
 */
float dev(Point p, Line l) {
    float expected_y = l.f(p.x);
    return std::abs(expected_y - p.y);
}

/**
 * returns the deviation between point p and the line equation of the points
 * @param p
 * @param points
 * @param size
 * @return
 */
float dev(Point p, Point **points, int size) {
    if (points == NULL) {
        throw "Array is a null ponter!";
    }
//    if (size <= 0) {
//        throw "Division by zero!";
//    }
    return dev(p, linear_reg(points, size));
}



