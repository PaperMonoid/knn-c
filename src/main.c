#include <stdlib.h>
#include <stdio.h>
#include <math.h>

char* load_images(const char *filename,
		int *n_rows,
		int *n_cols,
		int *n_images,
		int *image_size) {
  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL) {
    perror("Error opening image file");
    return NULL;
  }

  // read header information
  int magic_number = 0;
  fread(&magic_number, sizeof(int), 1, file);
  fread(n_images, sizeof(int), 1, file);
  fread(n_rows, sizeof(int), 1, file);
  fread(n_cols, sizeof(int), 1, file);

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

  fread(images, sizeof(char), (*image_size) * (*n_images), file);

  fclose(file);
  return images;
}

char* load_labels(const char *filename, int *n_labels) {
  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL) {
    perror("Error opening labels file");
    return NULL;
  }

  // read header information
  int magic_number = 0;
  fread(&magic_number, sizeof(int), 1, file);
  fread(n_labels, sizeof(int), 1, file);

  // convert big endian to little endian
  magic_number = __builtin_bswap32(magic_number);
  *n_labels = __builtin_bswap32(*n_labels);

  char *labels = malloc(sizeof(char) * (*n_labels));
  if (labels == NULL) {
    perror("Failed to allocate memory for labels");
    fclose(file);
    return NULL;
  }

  fread(labels, sizeof(char), *n_labels, file);

  fclose(file);
  return labels;
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
    for (int i = 0; i < n_labels; i++) {
      printf("Label %d: %d\n", i, labels[i]);
    }

    free(labels); // Free allocated memory
  }
}


float distances(float* x1, float* x2, int n_features, int n_samples) {
  for (int i = 0; i < n_samples && i + 8 < i + n_features; i += 8) {

  }
}

int main() {


  return 0;
}
