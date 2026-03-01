#include "cache.hpp"
#include <chrono>
#include <cmath>
using namespace std;

Cache::Cache(int sets, int blocks, int size, string trace) {
  this->sets = sets;
  this->blocks = blocks;
  this->size = size;
  this->trace = trace;

  // initailize values to zero
  this->num_hits = 0;
  this->num_misses = 0;
  this->hit_miss_ratio = 0.0;

  this->fin.open(trace);

  this->offset_bits = log2(this->size);
  this->index_bits = log2(this->sets);

  // initialize cache data structure
  this->cache.resize(sets);
  for (int i = 0; i < sets; i++) {
    // intialize each block
    Block temp = {0, false, chrono::steady_clock::now()};
    this->cache[i].resize(blocks, temp);
  }
}

Cache::~Cache() { this->fin.close(); }

// main method of cahce emulator
void Cache::run() {
  string temp;
  while (getline(this->fin, temp)) {
    // need to convert memory address to int
    string hex_string = temp.substr(2);
    int address = stoi(hex_string, nullptr, 16);

    int set_index = (address >> offset_bits) & (sets - 1);
    int tag = address >> (offset_bits + index_bits);

    // delete debug statements later.
    printf("\n");
    printf("set_index: %d\n", set_index);
    printf("tag: %d\n", tag);

    // Them memory address was found in the cache
    if (search_cache(set_index, tag)) {
      this->num_hits += 1;
    } else {
      // memory address not in the cache need to enforce LRU
      this->num_misses += 1;
    }

    // NOTE some forward thinking if it is a miss then we need to enforce the
    // LRU policy by evicting the least recently used and replacing it with the
    // new tag for the memory address we are currently proccessing.
  }
  printf("num_misses: %d\n", num_misses);
}

bool Cache::search_cache(int set_index, int tag) {
  for (uint i = 0; i < blocks; i++) {
    Block temp = cache[set_index][i];
    if (temp.tag == tag && temp.valid) {
      return true;
    }
  }

  // Not in cache
  return false;
}

void Cache::print_values() {
  printf("offset_bits: %u\n", this->offset_bits);
  printf("index_bits: %u\n", this->index_bits);
}
