#include "linalg.h"

#include "simd.h"

void sisd::vector_add(linvec &result, const linvec &left, const linvec &right) {
  naive_add(result, left, right);
}

void simd::vector_add(linvec &result, const linvec &left, const linvec &right) {
  fast_add(result, left, right);
}

float sisd::vector_dot(const linvec &left, const linvec &right) {
  auto result = 0.0f;

  for (size_t i = 0; i < left.size(); ++i) {
    result += left[i] * right[i];
  }

  return result;
}

float simd::vector_dot(const linvec &left, const linvec &right) {
  const int nElements = sizeof(__m256) / sizeof(float);
  auto result = 0.0f;

  for (int i = 0; i < left.size(); i += nElements) {
    const __m256 x = _mm256_loadu_ps(left.data() + i);
    const __m256 y = _mm256_loadu_ps(right.data() + i);

    const __m256 result_vector = _mm256_mul_ps(x, y);

    float temp[nElements];
    _mm256_store_ps(temp, result_vector);

    for (int j = 0; j < nElements; ++j) {
      result += temp[j];
    }
  }

  return result;
}