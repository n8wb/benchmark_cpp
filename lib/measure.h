#ifndef MEASURE_H
#define MEASURE_H

#include <iostream>
#include <iomanip>
#include <chrono>
//https://github.com/dmitryikh/rust-vs-cpp-bench/blob/master/common/common.hpp
// measure and return time elapsed in `job` in seconds
template <typename JOB>
double measure(JOB&& job) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
    start = std::chrono::high_resolution_clock::now();
    job();
    end = std::chrono::high_resolution_clock::now();
    duration += end - start;
    return duration.count();
}

template <typename JOB>
void measure_and_print(JOB&& job) {
    const double m = measure(std::forward<JOB>(job));
    std::cerr << std::setprecision(12) << std::fixed << m << std::endl;
}

#endif