#include <cmath>
#include "anomaly_detection_util.h"

/**
 * Calculate the mean of a given range
 * @param x - array of floats
 * @param size - size of the sample
 * @return the mean of the range
 */
float mean(float *x, int size) {
    float sum = 0; // sum of the elements in the X array

    // sums all the elements in the array
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    // return the mean
    return sum / size;
}

/**
 * Calculate the variance of the given array
 * @param x array of floats
 * @param size size of the array
 * @return variance
 */
float var(float *x, int size) {
    float mu = mean(x, size);
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += pow((x[i] - mu), 2);
    }
    return sum / size;
}
//
//
/**
 * returns the covariance of X and Y
 * @param x
 * @param y
 * @param size
 * @return
 *
 */
//@todo Implement Cov function
//float cov(float *x, float *y, int size) {
//
//}
//
/**
 * returns the Pearson correlation coefficient of X and Y
 * @param x
 * @param y
 * @param size
 * @return
 */
// @todo Implement pearson function
//float pearson(float *x, float *y, int size) {
//
//}
////
//
/**
 * performs a linear regression and returns the line equation
 * @param points
 * @param size
 * @return
 */
 //@todo Implement linear_reg function
//Line linear_reg(Point **points, int size) {
//}
//
/**
 * returns the deviation between point p and the line equation of the points
 * @param p
 * @param points
 * @param size
 * @return
 */
//@todo Implement dev function
//float dev(Point p, Point **points, int size) {
//
//}
//
//
/**
 * returns the deviation between point p and the line
 * @param p
 * @param l
 * @return
 */
// @todo Implement dev function
//float dev(Point p, Line l) {
//
//}

