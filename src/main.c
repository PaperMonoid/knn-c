#include <stdlib.h>
#include <stdio.h>
#include "mnist.c"


float distances(float* x1, float* x2, int n_features, int n_samples) {
  #pragma omp parallel for
  for (int i = 0; i < n_samples && i + 8 < i + n_features; i += 8) {

  }
}

int main() {


  return 0;
}
