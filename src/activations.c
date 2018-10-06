#include <assert.h>
#include <math.h>
#include "uwnet.h"

double logistic_func(x) {
  return 1 / (1 + exp(-1 * x));
}

double relu_func(x) {
  return x > 0 ? x : 0;
}

double lrelu_func(x) {
  return x > 0 ? x : 0.1 * x;
}

double softmax_func(x) {
  return exp(x);
}

// Run an activation function on each element in a matrix,
// modifies the matrix in place
// matrix m: Input to activation function
// ACTIVATION a: function to run
void activate_matrix(matrix m, ACTIVATION a)
{
    int i, j;
    for(i = 0; i < m.rows; ++i){
        double sum = 0;
        for(j = 0; j < m.cols; ++j){
            int index = i * m.cols + j;
            double x = m.data[index];
            if(a == LOGISTIC){
                m.data[index] = logistic_func(x);
            } else if (a == RELU){
                m.data[index] = relu_func(x);
            } else if (a == LRELU){
                m.data[index] = lrelu_func(x);
            } else if (a == SOFTMAX){
                m.data[index] = softmax_func(x);
            }
            sum += m.data[i*m.cols + j];
        }
        if (a == SOFTMAX) {
            for (int k = 0; k < m.cols; k++) {
                m.data[i * m.cols + k] /= sum;
            }
        }
    }
}

// Calculates the gradient of an activation function and multiplies it into
// the delta for a layer
// matrix m: an activated layer output
// ACTIVATION a: activation function for a layer
// matrix d: delta before activation gradient
void gradient_matrix(matrix m, ACTIVATION a, matrix d)
{
    int i, j;
    for(i = 0; i < m.rows; ++i){
        for(j = 0; j < m.cols; ++j){
            double x = m.data[i*m.cols + j];
            // TODO: multiply the correct element of d by the gradient
        }
    }
}
