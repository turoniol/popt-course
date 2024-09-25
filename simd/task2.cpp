#include "task2.h"

#include "common.h"

#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

template <class T> class aligned_allocator : public std::allocator<T> {
  using Parent = std::allocator<T>;

public:
  using value_type = typename Parent::value_type;
  using size_type = typename Parent::size_type;
  using difference_type = typename Parent::difference_type;

  template <class U> struct rebind { using other = aligned_allocator<U>; };

  aligned_allocator() noexcept = default;
  aligned_allocator(const aligned_allocator &) noexcept = default;
  template <class U> aligned_allocator(const aligned_allocator<U> &) noexcept {}

  T *allocate(size_type n) {
    void *p;
    if (posix_memalign(&p, 64, n * sizeof(value_type))) {
      throw std::bad_alloc();
    }

    return static_cast<T *>(p);
  }

  void deallocate(T *p, size_type) noexcept { free(p); }
};

void run_task2() {
  using alligned_vec = std::vector<float, aligned_allocator<float>>;

  const auto nSize = ARRAY_SIZE + 117;

  const auto a = generate_random_range<alligned_vec>(nSize);
  const auto b = generate_random_range<alligned_vec>(nSize);

  benchmark_arrays_addition(a, b);
}
