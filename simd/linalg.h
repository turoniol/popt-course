#pragma once

#include "aligned_allocator.h"

using linvec = aligned_vecf;

struct matrix {
  linvec data;
  std::size_t nRows;
  std::size_t nColumns;
};

inline auto allocate_matrix(std::size_t nRows, std::size_t nColumns) -> matrix {
  return {aligned_vecf(nRows * nColumns), nRows, nColumns};
}

namespace sisd {
void vector_add(linvec &result, const linvec &left, const linvec &right);
float vector_dot(const linvec &left, const linvec &right);
void matmul(matrix &result, const matrix &left, const matrix &right);
} // namespace sisd

namespace simd {
void vector_add(linvec &result, const linvec &left, const linvec &right);
float vector_dot(const linvec &left, const linvec &right);
void matmul(matrix &result, const matrix &left, const matrix &right);
} // namespace simd