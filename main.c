#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./headers/mnist.h"


float *distances(float* x1, float* x2, int n_features, int n_samples) {
  float *values = malloc(sizeof(float) * n_samples);

#pragma omp parallel for
  for (int i = 0; i < n_samples; i++) {
    values[i] = 0.0f;
  }

#pragma omp parallel for
  for (int i = 0; i < n_samples; i++) {
    for (int j = 0; j < n_features; j++) {
      int n = i * n_features + j;
      float diference = (x1[n] - x2[n]);
      values[i] += diference * diference;
    }
    values[i] = sqrtf(values[i]);
  }

  return values;
}

int main() {
  Dataset training = load_training_data();
  Dataset testing = load_testing_data();

  display_label(training, 0);
  display_digit_bw(training, 0);

  display_label(testing, 0);
  display_digit_bw(testing, 0);

  free(training.images);
  free(training.labels);
  free(testing.images);
  free(testing.labels);
  return 0;
}
