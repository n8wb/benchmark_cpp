#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;
#include "../lib/measure.h"
// return position of the element if found (indexing from 1),
// return -1 otherwise
template<typename T>
int32_t binary_search(std::vector<T> const& vec, T const& value) {
    int32_t l = 0;
    int32_t r = static_cast<int32_t>(vec.size() - 1);
    int32_t i;
    int32_t ret(-1);
    while(l <= r) {
        i = (l + r) / 2;
        if(vec[i] > value) {
            r = i - 1;
        }else if(vec[i] < value){
            l = i + 1;
        }else{
            ret = i + 1;
            break;
        }
    }
    return ret;
}

// read number of elements, read elements int32_to vector
std::vector<int32_t> read_vec_w_num() {
    size_t n;
    std::cin >> n;
    std::vector<int32_t> vec(n, 0);
    for (auto& val: vec)
        std::cin >> val;
    return vec;
}

int32_t main(int32_t argc, char** argv) {
    std::ios::sync_with_stdio(false);

    // 1. Read the array, and values for search
    const auto a_vec = read_vec_w_num();
    const auto b_vec = read_vec_w_num();

    // 2. Search values, write results
    std::vector<int32_t> res(b_vec.size());
    measure_and_print([&a_vec, &b_vec, &res] ()
        {
            for (size_t i = 0; i < b_vec.size(); i++)
                res[i] = binary_search(a_vec, b_vec[i]);
        });

    // 3. Write results
    /*for (auto const& r: res)
        std::cout << r << " ";*/

    return 0;
}

