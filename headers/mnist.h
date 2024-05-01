#ifndef MNIST_H
#define MNIST_H

char* load_images(const char *filename,
		  int *n_rows,
		  int *n_cols,
		  int *n_images,
		  int *image_size);

char* load_labels(const char *filename, int *n_labels);

typedef struct Dataset {
    char *images;
    char *labels;
    int n_rows;
    int n_cols;
    int n_images;
    int image_size;
} Dataset;

Dataset load_training_data();

Dataset load_testing_data();

void display_label(Dataset data, int index);

void display_digit_hex(Dataset data, int index);

void display_digit_bw(Dataset data, int index);

void test();

#endif
