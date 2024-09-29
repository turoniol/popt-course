#pragma once

#include <ranges> // IWYU pragma: keep
#include <x86intrin.h>

template <std::ranges::random_access_range R>
void naive_add(R &result, const R &left, const R &right) {
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] = left[i] + right[i];
  }
}

template <std::ranges::random_access_range R>

void fast_add(R &result, const R &left, const R &right) {
  const int nElements = sizeof(__m256) / sizeof(float);

  for (int i = 0; i < result.size(); i += nElements) {
    const __m256 x = _mm256_loadu_ps(left.data() + i);
    const __m256 y = _mm256_loadu_ps(right.data() + i);

    const __m256 result_vector = _mm256_add_ps(x, y);

    _mm256_storeu_ps(result.data() + i, result_vector);
  }
}
