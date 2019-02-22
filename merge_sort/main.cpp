#include <cassert>
#include <iostream>
#include <queue>
#include <algorithm>
#include <memory>
#include <cstdint>
#include <iomanip>
#include <chrono>
//#include "../lib/measure.h"


template <typename func_type>
double measure(func_type&& job) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration = std::chrono::duration<double>::zero();
    start = std::chrono::high_resolution_clock::now();
    job();
    end = std::chrono::high_resolution_clock::now();
    duration += end - start;
    return duration.count();
}

template <typename func_type>
void measure_and_print(func_type&& job) {
    const double m = measure(std::forward<func_type>(job));
    std::cerr << std::setprecision(12) << std::fixed << m << std::endl;
}


template<typename T>
int64_t _merge(std::vector<T>& vec,T* tmp,const size_t left, const size_t mid, const size_t right) {
    int64_t swap_count = 0;
    const size_t size = right - left + 1;
    size_t curl = left;
    size_t curr = mid+1;

    for(size_t i = 0; i < size; i++) {

        if((curl <= mid) && (curr <= right)) {
            if(vec[curl] <= vec[curr]) {
                tmp[i] = vec[curl++];
            } else {
                tmp[i] = vec[curr++];
                swap_count += mid - curl + 1;
            }
        } else if(curl <= mid) {
            tmp[i] = vec[curl++];
        } else{
            assert(curr <= right);
            tmp[i] = vec[curr++];
        }
    }
    std::copy(tmp,&tmp[size],vec.begin()+left);

    return swap_count;
}

template<typename T>
int64_t merge_sort(std::vector<T>& vec) {
    int64_t swap_count = 0;
    size_t left_start,mid,right_end;
    const size_t n = vec.size();

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    
    auto tmp = std::make_unique<T[]>(n);//makes a new array of type T
    for (size_t curr_size = 1; curr_size <= n-1; curr_size *= 2) {
        // Pick starting point of different subarrays of current size
        
        for (left_start = 0; left_start < n-1; left_start += 2*curr_size) {
            // Find ending point of left subarray. mid+1 is starting 
            // point of right
            
            mid = left_start + curr_size - 1;
            right_end = std::min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            swap_count += _merge(vec,tmp.get(),left_start, mid, right_end);
        }
    }
    return swap_count;
}

// read number of elements, read elements into vector
std::vector<int> read_vec_w_num() {
    size_t n;
    std::cin >> n;
    std::vector<int32_t> vec(n, 0);
    for (auto& val: vec){
        std::cin >> val;
    }
    return vec;
}

int main() {
    std::ios::sync_with_stdio(false);

    // 1. Read the array
    std::vector<int32_t> vec = read_vec_w_num();

    int64_t nswap = 0;
    measure_and_print([&vec, &nswap] ()
        {
            // 2. Mergesort the array, calculate number of swaps
            nswap = merge_sort(vec);
            //std::sort(vec.begin(), vec.end());
        });

    // 3. Write result
    std::cout << nswap << std::endl;

    //auto curr = vec[0];
    /*for(int val : vec){
        if(curr > val){
            std::cerr<<"Not sorted! "<<val<<"<="<<curr<<std::endl;
            //break;
        }
        curr = val;
    }*/
    return 0;
}
