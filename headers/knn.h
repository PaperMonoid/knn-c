#ifndef KNN_H
#define KNN_H

#include "./mnist.h"

int *knn(int k_neighbors, Dataset training, char* sample, int idx);

#endif
