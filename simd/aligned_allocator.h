#pragma once

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

using aligned_vecf = std::vector<float, aligned_allocator<float>>;