#include <stdlib.h>
#include <math.h>
#include <immintrin.h>


float *distances(char* x1, char* x2, int idx, int n_features, int n_samples) {
  float *values = malloc(sizeof(float) * n_samples);

#pragma omp parallel for
  for (int i = 0; i < n_samples; i++) {
    values[i] = 0.0f;
  }

#pragma omp parallel for
  for (int i = 0; i < n_samples; i++) {

    int j = 0;
    __m256 msum = _mm256_setzero_ps();
    __m256 mdiff = _mm256_setzero_ps();

    for (; j < n_features; j += 8) {
      int nx1 = i * n_features + j;
      int nx2 = idx * n_features + j;
      float x1_tmp[8];
      float x2_tmp[8];
      for (int k = 0; k < 8; k++) {
	x1_tmp[k] = (float) ((unsigned char) x1[nx1 + k]);
	x2_tmp[k] = (float) ((unsigned char) x2[nx2 + k]);
      }
      __m256 mx1 = _mm256_loadu_ps(x1_tmp);
      __m256 mx2 = _mm256_loadu_ps(x2_tmp);

      mdiff = _mm256_sub_ps(mx1, mx2);
      msum = _mm256_fmadd_ps(mdiff, mdiff, msum);
    }
    float sums[8];
    _mm256_storeu_ps(sums, msum);
    values[i] = sums[0] + sums[1] + sums[2] + sums[3] +
      sums[4] + sums[5] + sums[6] + sums[7];

    for (; j < n_features; j++) {
      int nx1 = i * n_features + j;
      int nx2 = idx * n_features + j;
      float diference = ((float)((unsigned char) x1[nx1]) -
			 (float) ((unsigned char) x2[nx2]));
      values[i] += diference * diference;
    }

    values[i] = sqrtf(values[i]);
  }

  return values;
}
