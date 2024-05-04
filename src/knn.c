#include <stdlib.h>
#include <stdio.h>

#include "../headers/mnist.h"
#include "../headers/distances.h"


int knn(int k_neighbors, Dataset training, char* sample, int idx) {
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

  int *indices = malloc(sizeof(int) * k_neighbors);
  int *counts = malloc(sizeof(int) * k_neighbors);
  int size = 0;
  for (int i = 0; i < k_neighbors; i++) {
    int index_of = -1;
    for (int j = 0; j < size; j++) {
      if (indices[j] == training.labels[min_is[j]]) {
	index_of = j;
	break;
      }
    }
    if (index_of > -1) {
      counts[index_of]++;
    } else {
      indices[size] = training.labels[min_is[i]];
      counts[size] = 0;
      size++;
    }
  }

  int mode = indices[0];
  int mode_freq = counts[0];
  for (int i = 0; i < size; i++) {
    if (counts[i] > mode_freq) {
      mode = indices[i];
      mode_freq = counts[i];
    }
  }

  free(d);
  free(indices);
  free(counts);
  free(min_is);
  free(min_ds);

  return mode;
}
