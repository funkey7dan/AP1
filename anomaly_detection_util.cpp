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

/**
 * returns the covariance of X and Y
 * @param x array of floats.
 * @param y array of floats.
 * @param size size of arrays.
 * @return covariance between x and y.
 */
float cov(float *x, float *y, int size) {
    //xm and ym are the means of two given arrays.
    float xm = mean(x, size);
    float ym = mean(y, size);
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
 * @return
 */
 //TODO Implement linear_reg function
Line linear_reg(Point **points, int size) {

}
//
/**
 * returns the deviation between point p and the line equation of the points
 * @param p
 * @param points
 * @param size
 * @return
 */
//TODO Implement dev function
float dev(Point p, Point **points, int size) {
//
}
//
//
/**
 * returns the deviation between point p and the line
 * @param p
 * @param l
 * @return
 */
// TODO Implement dev function
float dev(Point p, Line l) {
//
}

