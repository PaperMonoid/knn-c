#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../headers/mnist.h"


char* load_images(const char *filename,
		int *n_rows,
		int *n_cols,
		int *n_images,
		int *image_size) {
  size_t items_read;
  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL) {
    perror("Error opening image file");
    return NULL;
  }

  // read header information
  int magic_number = 0;
  items_read = fread(&magic_number, sizeof(int), 1, file);
  if (items_read != 1) {
    perror("Failed to read magic number");
    fclose(file);
    return NULL;
  }
  items_read = fread(n_images, sizeof(int), 1, file);
  if (items_read != 1) {
    perror("Failed to read number of images");
    fclose(file);
    return NULL;
  }
  items_read = fread(n_rows, sizeof(int), 1, file);
  if (items_read != 1) {
    perror("Failed to read number of rows");
    fclose(file);
    return NULL;
  }
  items_read = fread(n_cols, sizeof(int), 1, file);
  if (items_read != 1) {
    perror("Failed to read number of columns");
    fclose(file);
    return NULL;
  }

  // convert big endian to little endian
  magic_number = __builtin_bswap32(magic_number);
  *n_images = __builtin_bswap32(*n_images);
  *n_rows = __builtin_bswap32(*n_rows);
  *n_cols = __builtin_bswap32(*n_cols);

  *image_size = (*n_rows) * (*n_cols);

  char *images = malloc(sizeof(char) * (*image_size) * (*n_images));
  if (images == NULL) {
    perror("Failed to allocate memory for images");
    fclose(file);
    return NULL;
  }

  items_read = fread(images, sizeof(char), (*image_size) * (*n_images), file);
  if (items_read != (unsigned long) (*image_size) * (*n_images)) {
    perror("Failed to read images");
    fclose(file);
    return NULL;
  }

  fclose(file);
  return images;
}


char* load_labels(const char *filename, int *n_labels) {
  size_t items_read;
  FILE *file;
  file = fopen(filename, "rb");
  if (file == NULL) {
    perror("Error opening labels file");
    return NULL;
  }

  // read header information
  int magic_number = 0;
  items_read = fread(&magic_number, sizeof(int), 1, file);
  if (items_read != 1) {
    perror("Failed to read magin number");
    fclose(file);
    return NULL;
  }
  items_read = fread(n_labels, sizeof(int), 1, file);
  if (items_read != 1) {
    perror("Failed to read number of labels");
    fclose(file);
    return NULL;
  }

  // convert big endian to little endian
  magic_number = __builtin_bswap32(magic_number);
  *n_labels = __builtin_bswap32(*n_labels);

  char *labels = malloc(sizeof(char) * (*n_labels));
  if (labels == NULL) {
    perror("Failed to allocate memory for labels");
    fclose(file);
    return NULL;
  }

  items_read = fread(labels, sizeof(char), *n_labels, file);
  if (items_read != (unsigned long)*n_labels) {
    perror("Failed to read labels");
    fclose(file);
    return NULL;
  }

  fclose(file);
  return labels;
}


Dataset load_training_data() {
  Dataset data;
  data.images = load_images("mnist/train-images.idx3-ubyte",
			    &data.n_rows,
			    &data.n_cols,
			    &data.n_images,
			    &data.image_size);
  data.labels = load_labels("mnist/train-labels.idx1-ubyte",
			    &data.n_images);
  return data;
}


Dataset load_testing_data() {
  Dataset data;
  data.images = load_images("mnist/t10k-images.idx3-ubyte",
			    &data.n_rows,
			    &data.n_cols,
			    &data.n_images,
			    &data.image_size);
  data.labels = load_labels("mnist/t10k-labels.idx1-ubyte",
			    &data.n_images);
  return data;
}


void display_label(Dataset data, int index) {
  char *labels = data.labels;
  printf("%d\n", labels[index]);
}


void display_digit_hex(Dataset data, int index) {
  char *images = data.images;
  int image_size = data.image_size;
  int offset = index * image_size;

  if (images != NULL) {
    // Print the image data
    for (int i = offset; i < (offset + image_size); i++) {
      printf("%02x", images[i] & 0xff);    // Print hex representation
      if ((i + 1) % 28 == 0) printf("\n"); // New line after every 28 bytes
      if ((i + 1) % image_size == 0) printf("\n");
    }
    printf("\n");
  }
}


void display_digit_bw(Dataset data, int index) {
  char *images = data.images;
  int image_size = data.image_size;
  int offset = index * image_size;

  if (images != NULL) {
    // Print the image data
    for (int i = offset; i < (offset + image_size); i++) {
      unsigned char value = images[i] & 0xff;
      if (value < 5) {
	printf(" ");
      } else if (value < 20) {
	printf("░");
      } else if (value < 50) {
	printf("▒");
      } else if (value < 100) {
	printf("▓");
      } else {
	printf("█");
      }
      if (value < 5) {
	printf(" ");
      } else if (value < 20) {
	printf("░");
      } else if (value < 50) {
	printf("▒");
      } else if (value < 100) {
	printf("▓");
      } else {
	printf("█");
      }
      if ((i + 1) % 28 == 0) printf("\n"); // New line after every 28 bytes
      if ((i + 1) % image_size == 0) printf("\n");
    }
    printf("\n");
  }
}


void test() {
  int n_rows = 0, n_cols = 0, n_images = 0, image_size = 0;
  char *images = load_images("mnist/t10k-images.idx3-ubyte",
			     &n_rows,
			     &n_cols,
			     &n_images,
			     &image_size);

  if (images != NULL) {
    // Print the image data
    int offset = 0 * image_size;
    for (int i = offset; i < (offset + image_size*10); i++) {
      printf("%02x ", images[i] & 0xff);  // Print hex representation
      if ((i + 1) % 28 == 0) printf("\n"); // New line after every 28 bytes
      if ((i + 1) % image_size == 0) printf("\n");
    }
    printf("\n");

    free(images);
  }

  int n_labels = 0;
  char *labels = load_labels("mnist/t10k-labels.idx1-ubyte", &n_labels);

  if (labels != NULL) {
    // Process the labels
    //for (int i = 0; i < n_labels; i++) {
    for (int i = 0; i < 10; i++) {
      printf("Label %d: %d\n", i, labels[i]);
    }

    free(labels); // Free allocated memory
  }
}
