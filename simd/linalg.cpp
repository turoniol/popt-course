#include "linalg.h"

#include "simd.h"
#include <cassert>

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

void sisd::matmul(matrix &result, const matrix &left, const matrix &right) {
  assert(left.nColumns == right.nRows);

  for (size_t i = 0; i < left.nRows; ++i) {
    for (size_t j = 0; j < right.nColumns; ++j) {

      result.data[i * right.nColumns + j] = 0.0f;

      for (size_t k = 0; k < left.nColumns; ++k) {

        result.data[i * right.nColumns + j] +=
            left.data[i * left.nColumns + k] *
            right.data[k * right.nColumns + j];
      }
    }
  }
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

void simd::matmul(matrix &result, const matrix &left, const matrix &right) {
  assert(left.nColumns == right.nRows);

  const int nElements = sizeof(__m256) / sizeof(float);

  for (size_t i = 0; i < left.nRows; ++i) {
    for (size_t j = 0; j < right.nColumns; ++j) {
      result.data[i * right.nColumns + j] = 0.0f;

      for (size_t k = 0; k < left.nColumns; k += nElements) {
        const __m256 x =
            _mm256_loadu_ps(left.data.data() + i * left.nColumns + k);
        const __m256 y =
            _mm256_loadu_ps(right.data.data() + k * right.nColumns + j);

        const __m256 result_vector = _mm256_mul_ps(x, y);

        float temp[nElements];
        _mm256_store_ps(temp, result_vector);

        for (int l = 0; l < nElements; ++l) {
          result.data[i * right.nColumns + j] += temp[l];
        }
      }
    }
  }
}
