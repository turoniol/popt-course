#include "task4.h"

#include "common.h"
#include "linalg.h"

void run_task4() {
    auto mat1 = allocate_matrix(97, 29);
    auto mat2 = allocate_matrix(29, 53);

    auto result = allocate_matrix(mat1.nRows, mat2.nColumns);

    const auto time1 = measure_time([&] { sisd::matmul(result, mat1, mat2); });
    const auto time2 = measure_time([&] { simd::matmul(result, mat1, mat2); });

    print_splitter();

    std::cout << "Matrix multiplication simple:\n";
    print_results(result.data, time1);

    print_splitter();
    std::cout << "Matrix multiplication SIMD:\n";
    print_results(result.data, time2);

    print_splitter();

    assert_arrays_are_equal(result.data, result.data);
}
