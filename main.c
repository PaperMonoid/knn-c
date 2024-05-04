#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./headers/mnist.h"
#include "./headers/knn.h"


int main() {
  Dataset training = load_training_data();
  Dataset testing = load_testing_data();

  int idx = 19;

  display_label(testing, idx);
  display_digit_bw(testing, idx);

  int label = knn(5, training, testing.images, idx);

  printf("------------------\n");
  printf("Prediction %d \n", label);

  free(training.images);
  free(training.labels);
  free(testing.images);
  free(testing.labels);
  return 0;
}
