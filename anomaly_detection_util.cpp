

#include <cmath>
#include "anomaly_detection_util.h"

float mean(float *x, int size) {
    float sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

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
// returns the covariance of X and Y
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
//
//// returns the Pearson correlation coefficient of X and Y
//float pearson(float *x, float *y, int size) {

//}
//
//// performs a linear regression and returns the line equation
//Line linear_reg(Point **points, int size) {
//}
//
//// returns the deviation between point p and the line equation of the points
//float dev(Point p, Point **points, int size) {
//
//}
//
//// returns the deviation between point p and the line
//float dev(Point p, Line l) {
//
//}

