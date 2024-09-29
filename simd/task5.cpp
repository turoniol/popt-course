#include "task5.h"

#include <exception>
#include <string>
#include <x86intrin.h>

#include "aligned_allocator.h"
#include "common.h"

namespace {
using aligned_string =
    std::basic_string<char, std::char_traits<char>, aligned_allocator<char>>;

namespace sisd {
auto count_substring(std::string_view str, std::string_view substr) -> size_t {
  size_t result = 0;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str.compare(i, substr.size(), substr) == 0) {
      ++result;
    }
  }

  return result;
}
} // namespace sisd

namespace simd {
auto count_substring(std::string_view str, std::string_view substr) -> size_t {
  static constexpr char ELEMENTS_EQUAL = 0xFF;

  size_t result = 0;

  const auto nElements = sizeof(__m256) / sizeof(char);

  const __m256i y =
      _mm256_load_si256(reinterpret_cast<const __m256i *>(substr.data()));

  for (size_t i = 0; i < str.size(); i += nElements) {
    const __m256i x =
        _mm256_load_si256(reinterpret_cast<const __m256i *>(str.data() + i));

    const __m256i result_vector = _mm256_cmpeq_epi8(x, y);

    char temp[nElements];
    _mm256_store_si256(reinterpret_cast<__m256i *>(temp), result_vector);

    int count = 0;
    for (size_t j = 0; j < std::min(nElements, nElements); ++j) {
      if (temp[j] == ELEMENTS_EQUAL) {
        ++count;
      }
    }

    if (count == substr.size()) {
      ++result;
    }
  }

  return result;
}
} // namespace simd

auto aligned_random_string(size_t nSize) -> char * {
  char *result = nullptr;

  posix_memalign(reinterpret_cast<void **>(&result), 64, nSize);

  for (size_t i = 0; i < nSize; ++i) {
    result[i] = static_cast<char>(rand() % 26 + 97);
  }

  return result;
}
} // namespace

void run_task5() {
  auto str = aligned_random_string(95'000);
  auto substr = aligned_random_string(3);

  substr[0] = 'z';
  substr[1] = 'x';
  substr[2] = 'c';

  size_t sisd_result = 0;
  size_t simd_result = 0;

  auto str_view = std::string_view(str, 95'000);
  auto substr_view = std::string_view(substr, 3);

  const auto time1 = measure_time(
      [&] { sisd_result = sisd::count_substring(str_view, substr_view); });
  const auto time2 = measure_time(
      [&] { simd_result = simd::count_substring(str_view, substr_view); });

  print_splitter();

  std::cout << "Count substring simple:\n";
  print_results(sisd_result, time1);

  print_splitter();
  std::cout << "Count substring SIMD:\n";

  print_results(simd_result, time2);

  assert(sisd_result == simd_result);

  free(str);
  free(substr);
}
