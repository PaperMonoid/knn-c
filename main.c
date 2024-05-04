#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./headers/mnist.h"
#include "./headers/knn.h"


int main() {
  Dataset training = load_training_data();
  Dataset testing = load_testing_data();

  int idx = 4;

  display_label(testing, idx);
  display_digit_bw(testing, idx);

  printf("BEFORE %d\n", idx);

  int *min_idx = knn(5, training, testing.images, idx);

  printf("------------------\n");
  display_label(training, min_idx[0]);
  display_digit_bw(training, min_idx[0]);
  display_label(training, min_idx[1]);
  display_digit_bw(training, min_idx[1]);
  display_label(training, min_idx[2]);
  display_digit_bw(training, min_idx[2]);
  display_label(training, min_idx[3]);
  display_digit_bw(training, min_idx[3]);
  display_label(training, min_idx[4]);
  display_digit_bw(training, min_idx[4]);

  free(min_idx);
  free(training.images);
  free(training.labels);
  free(testing.images);
  free(testing.labels);
  return 0;
}
