#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./headers/mnist.h"
#include "./headers/distances.h"


int main() {
  Dataset training = load_training_data();
  Dataset testing = load_testing_data();

  display_label(training, 0);
  display_digit_bw(training, 0);

  display_label(testing, 0);
  display_digit_bw(testing, 0);

  float *d = distances(training.images,
		       testing.images,
		       0,
		       training.image_size,
		       training.n_images);

  float min_distance = d[0];
  int min_idx = 0;
  for (int i = 0; i < training.n_images; i++) {
    if (d[i] < min_distance) {
      min_distance = d[i];
      min_idx = i;
    }
  }

  printf("------------------\n");
  printf("MIN DISTANCE: %f\n", min_distance);
  display_label(training, min_idx);
  display_digit_bw(training, min_idx);

  free(training.images);
  free(training.labels);
  free(testing.images);
  free(testing.labels);
  return 0;
}
