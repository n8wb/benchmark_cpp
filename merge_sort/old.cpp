#include <cassert>
#include <iostream>
#include <queue>
#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>

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

template<typename T>
long _merge(std::vector<T>& vec,T* tmp,const size_t left, const size_t mid, const size_t right) {
    long swap_count = 0;
    size_t size = right - left + 1;
    size_t curl = left;
    size_t curr = mid+1;

    //std::array<T,size> tmp;
    //T* tmp = new T[size];

    for(size_t i = 0; i < size; i++) {

        if((curl <= mid) && (curr <= right)) {
            if(vec[curl] <= vec[curr]) {
                //std::swap(vec[i+left],vec[curl++]);
                tmp[i] = vec[curl++];
            } else {
                //std::swap(vec[i+left],vec[curr++]);
                tmp[i] = vec[curr++];
                swap_count += mid - curl + 1;
            }
        } else if(curl <= mid) {
            //std::swap(vec[i+left],vec[curl++]);
            tmp[i] = vec[curl++];
        } else if(curr <= right) {
            //std::swap(vec[i+left],vec[curr++]);
            tmp[i] = vec[curr++];
        } else {
            std::cerr << "What i'm doing here?" << std::endl;
        }
    }
    std::copy(std::make_move_iterator(tmp),
                                        std::make_move_iterator(&tmp[size]),
                                        vec.begin() + left);

    //delete[] tmp;
    memset()
    return swap_count;
}

template<typename T>
long merge_sort(std::vector<T>& vec) {
    long swap_count = 0;
    size_t left_start;
    const size_t n = vec.size();

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    T* tmp = new T[n];
    for (size_t curr_size = 1; curr_size <= n-1; curr_size *= 2) {
        // Pick starting point of different subarrays of current size
        
        for (left_start = 0; left_start < n-1; left_start += 2*curr_size) {
            // Find ending point of left subarray. mid+1 is starting 
            // point of right
            
            size_t mid = left_start + curr_size - 1;
            size_t right_end = std::min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            swap_count += _merge(vec,tmp,left_start, mid, right_end);
        }
    }
    delete[] tmp;
    return swap_count;
}

// read number of elements, read elements into vector
std::vector<int> read_vec_w_num() {
    size_t n;
    std::cin >> n;
    std::vector<int> vec(n, 0);
    for (auto& val: vec)
        std::cin >> val;
    return vec;
}

int main() {
    std::ios::sync_with_stdio(false);

    // 1. Read the array
    auto vec = read_vec_w_num();

    long nswap = 0;
    measure_and_print([&vec, &nswap] ()
        {
            // 2. Mergesort the array, calculate number of swaps
            nswap = merge_sort(vec);
        });

    // 3. Write result
    std::cout << nswap << std::endl;

    auto curr = vec[0];
    for(int val : vec){
        if(curr > val){
            std::cerr<<"Not sorted! "<<val<<"<="<<curr<<std::endl;
            //break;
        }
        curr = val;
    }
    return 0;
}
