#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <iomanip>
#include <chrono>
#include "../lib/measure.h"

struct node {
    int freq;
    char value;
    node* left = nullptr;
    node* right = nullptr;
    node(){}
};

class huffman_codec{
public:
    // typedef and struct declaration to organize a priority queue to build Huffman tree
    // size_t - index of the node in `nodes` vector
    // int - frequency of the node
    using code = std::pair<size_t, int>;
    struct compare {
        bool operator()(const code& op1, const code& op2) {
            return op1.second > op2.second;
        }
    };

    void build_tree(const std::unordered_map<char, int>& freq);
    void build_table();
    void clear();
    size_t size() const noexcept;
    void print_table(std::ostream& stream) const;
    std::string encode(const std::string & msg) const;
    const std::string& encode(char const c) const;

private:
    size_t _size;
    node* head = nullptr;
    std::vector<node> nodes;
    std::unordered_map<char, std::string> _table;

    void build_table(node* n, std::string code);
};

// build Huffman tree based on letters frequency
void huffman_codec::build_tree(const std::unordered_map<char, int>& freq) {
    clear();
    _size = freq.size();
    // priliminary initialize all nodes
    nodes.resize(2 * _size - 1);
    std::priority_queue<int, std::vector<code>,compare> pqueue;
    size_t i = 0;
    for(auto& v : freq) {
        nodes[i].freq = v.second;
        nodes[i].value = v.first;
        pqueue.emplace(i, v.second);
        i++;
    }
    if(_size == 1) {
        // only one letter in freq. table
        head = &nodes[0];
    } else {
        for(size_t k = _size; k < 2 * _size - 1; k++) {
            // take two most frequent nodes and create new node on top of them,
            // push the new node to priority queue
            auto const v1 = pqueue.top();
            pqueue.pop();
            auto const v2 = pqueue.top();
            pqueue.pop();
            nodes[k].left = &nodes[v1.first];
            nodes[k].right = &nodes[v2.first];
            nodes[k].freq = v1.second + v2.second;
            head = &nodes[k];
            pqueue.emplace(k, nodes[k].freq);
        }
    }
}

// build Huffman table for encoding
void huffman_codec::build_table() {
    assert(size() > 0);
    assert(head != nullptr);
    _table.clear();
    build_table(head, "");
}

void huffman_codec::clear() {
    _table.clear();
    _size = 0;
    nodes.clear();
    head = nullptr;
}

size_t huffman_codec::size() const noexcept {
    return _size;
}

// internal function for recursive tree traversal
void huffman_codec::build_table(node* n, std::string code) {
    if(n->left != nullptr) {
        // this is intermidiate node. Go deep
        assert(n->right != nullptr);
        build_table(n->left, code + "0");
        build_table(n->right, code + "1");
    } else {
        // this is leaf
        if(n == head) code = "0";
        assert(n->value != 0);
        _table[n->value] = code;
    }
}

void huffman_codec::print_table(std::ostream& stream) const {
    assert(_size > 0);
    for(size_t i = 0; i < size(); i++) {
        char c = nodes[i].value;
        stream << c << ": " << encode(c) << std::endl;
    }
}

// encode text message
std::string huffman_codec::encode(std::string const& msg) const {
    std::string ret = "";
    for(char const c : msg) {
        ret += encode(c);
    }
    return ret;
}

// encode letter
const std::string & huffman_codec::encode(char const c) const {
    assert(size() > 0);
    const auto& v = _table.find(c);
    //if(v != _table.end()) {
    return v->second;
    /*} else {
        throw std::runtime_error("Can't find letter");
    }*/
}

int main() {
    // 1.Read message
    std::ios::sync_with_stdio(false);
    std::string str;
    std::cin >> str;

    huffman_codec codec;
    std::string code;

    // 2. Calculate frequancy map for letters
    std::unordered_map<char, int> freq;
    for(char c : str) {
        freq[c]++;
    }

    measure_and_print([&codec, &str, &code,&freq] ()
        {
            
            // 3. Build Huffman tree & table
            codec.build_tree(freq);
            codec.build_table();

            // 4. Encode message
            code = codec.encode(str);
        });

    // 5. Output
    std::cout << codec.size() << " " << code.size() << std::endl;
    codec.print_table(std::cout);
    //std::cout << code << std::endl;
    return 0;
}
