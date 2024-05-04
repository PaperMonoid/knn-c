#include <stdlib.h>
#include <stdio.h>

#include "../headers/mnist.h"
#include "../headers/distances.h"


int *knn(int k_neighbors, Dataset training, char* sample, int idx) {
  float *d = distances(training.images,
		       sample,
		       idx,
		       training.image_size,
		       training.n_images);

  int last = k_neighbors - 1;
  int *min_is = malloc(sizeof(int) * k_neighbors);
  float *min_ds = malloc(sizeof(float) * k_neighbors);

  for (int i = 0; i < k_neighbors; i++) {
    min_is[i] = 0;
    min_ds[i] = d[0];
  }

  for (int i = 0; i < training.n_images; i++) {
    if (d[i] < min_ds[last]) {
      //printf("distance %d, label: %d: %f\n", i, training.labels[i], d[i]);

      int k = 0;
      for (; k < k_neighbors; k++) {
	if (d[i] < min_ds[k]) {
	  break;
	}
      }

      int prev_i = min_is[k];
      float prev_d = min_ds[k];
      min_is[k] = i;
      min_ds[k] = d[i];

      for (k = k + 1; k < k_neighbors; k++) {
	int prev_i_ = min_is[k];
	float prev_d_ = min_ds[k];
	min_is[k] = prev_i;
	min_ds[k] = prev_d;
	prev_i = prev_i_;
	prev_d = prev_d_;
      }
    }
  }

  for (int i = 0; i < k_neighbors; i++) {
    printf("distance %d: %f\n", i, min_ds[i]);
  }

  free(d);
  free(min_ds);

  return min_is;
}
