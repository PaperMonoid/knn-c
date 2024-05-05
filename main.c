#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include "./headers/mnist.h"
#include "./headers/knn.h"


void start_timer(struct timeval *start) {
    gettimeofday(start, NULL);
}

long stop_timer(struct timeval *start, struct timeval *stop) {
    gettimeofday(stop, NULL);
    return ((stop->tv_sec - start->tv_sec) * 1000000 +
	    stop->tv_usec - start->tv_usec) / 1000;
}


int main() {
  Dataset training = load_training_data();
  Dataset testing = load_testing_data();

  struct timeval stop, start;
  start_timer(&start);

  int total = 0;
  int correct = 0;
  int incorrect = 0;
  for (int i = 0; i < testing.n_images; i++) {
    int label = knn(5, training, testing.images, i);
    total++;
    if (label == testing.labels[i]) {
      correct++;
    } else {
      incorrect++;
    }
  }

  long milli = stop_timer(&start, &stop);

  printf("Elapsed %ld millis\n", milli);
  printf("Total %d\n", total);
  printf("Correct %d\n", correct);
  printf("Incorrect %d\n", incorrect);
  printf("Accuracy %f\n", ((float) (correct)) / ((float) total));

  //display_label(testing, idx);
  //display_digit_bw(testing, idx);

  //printf("------------------\n");
  //printf("Prediction %d \n", label);

  free(training.images);
  free(training.labels);
  free(testing.images);
  free(testing.labels);
  return 0;
}
