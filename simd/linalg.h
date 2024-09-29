#pragma once

#include "aligned_allocator.h"

using linvec = aligned_vecf;

namespace sisd {
void vector_add(linvec &result, const linvec &left, const linvec &right);
float vector_dot(const linvec &left, const linvec &right);
} // namespace sisd

namespace simd {
void vector_add(linvec &result, const linvec &left, const linvec &right);
float vector_dot(const linvec &left, const linvec &right);
} // namespace simd