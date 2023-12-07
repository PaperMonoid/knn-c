#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mnist.c"


float *distances(float* x1, float* x2, int n_features, int n_samples) {
  float *values = malloc(sizeof(float) * n_samples);

  #pragma omp parallel for
  for (int i = 0; i < n_samples; i++) {
    values[i] = 0.0f;
    for (int j = 0; j < n_features; j++) {
      int n = i*n_features + j;
      float diference = (x1[n] - x2[n]);
      values[i] += diference * diference;
    }
    values[i] = sqrt(values[i]);
  }

  return values;
}

int main() {


  return 0;
}
