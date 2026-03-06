#include "cache.hpp"
#include <chrono>
#include <cmath>
using namespace std;

Cache::Cache(int sets, int blocks, int size, string trace, bool rrip) {
  this->sets = sets;
  this->blocks = blocks;
  this->size = size;
  this->trace = trace;
  this->rrip = rrip;

  // initailize values to zero
  this->num_accesses = 0;
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
    Block temp = {0, false, chrono::steady_clock::now(), -1};
    this->cache[i].resize(blocks, temp);
  }
}

Cache::~Cache() { this->fin.close(); }

// Run the cache emulator with Least Recently Used eviction policy
void Cache::run() {
  string temp;
  while (getline(this->fin, temp)) {
    // need to convert memory address to int
    string hex_string = temp.substr(2);
    int address = stoi(hex_string, nullptr, 16);

    int set_index = (address >> offset_bits) & (sets - 1);
    int tag = address >> (offset_bits + index_bits);

    // delete debug statements later.
    // printf("\n");
    // printf("set_index: %d\n", set_index);
    // printf("tag: %d\n", tag);

    this->num_accesses += 1;
    // Them memory address was found in the cache
    if (search_cache(set_index, tag)) {
      this->num_hits += 1;
    } else {
      // memory address not in the cache need to enforce LRU
      Block temp_block = {tag, true, chrono::steady_clock::now()};

      if (this->rrip) {
        rrip_policy(set_index, temp_block);
      } else {
        replace_oldest(set_index, temp_block);
      }
      this->num_misses += 1;
    }
  }

  printf("accesses: %d\n", num_accesses);
  printf("num_hits: %d\n", num_hits);
  printf("num_misses: %d\n", num_misses);
  double miss_rate = (num_misses / (double)num_accesses) * 100;
  printf("Miss Rate: %.2lf%%\n", miss_rate);
}

bool Cache::search_cache(int set_index, int tag) {
  for (uint i = 0; i < blocks; i++) {
    Block temp = cache[set_index][i];
    if (temp.tag == tag && temp.valid) {
      // If cache hit set m value for RRIP to 0
      // We can do this when using LRU and just ignore m value.
      temp.m = 0;
      return true;
    }
  }

  // Not in cache
  return false;
}

void Cache::replace_oldest(int set_index, Block b) {
  for (uint i = 0; i < blocks; i++) {
    // if tag = 0 this block hasn't been filled yet so put the new block b in
    // there
    if (cache[set_index][i].tag == 0) {
      cache[set_index][i] = b;
      return;
    }
  }

  // find oldest block index
  uint oldest_idx = 0;
  for (uint i = 1; i < blocks; i++) {
    if (cache[set_index][i].timestamp <
        cache[set_index][oldest_idx].timestamp) {
      oldest_idx = i;
    }
  }

  cache[set_index][oldest_idx] = b;
}

void Cache::rrip_policy(int set_index, Block b) {
  // if m = -1 this block hasn't been used yet insert new block into the set.
  for (uint i = 0; i < blocks; i++) {
    if (cache[set_index][i].m == -1) {
      // New insertions set m value to 2
      b.m = 2;
      cache[set_index][i] = b;
    }
  }

  // using this as a flag to see if we found a block with m = 3 to evict
  bool found = false;
  while (!found) {
    for (uint i = 0; i < blocks; i++) {
      if (cache[set_index][i].m == 3) {
        b.m = 2;
        cache[set_index][i] = b;
        found = true;
        return;
      }
    }
    // If we reach here we didn't find a block with
    // an m = 3. So now loop through and increment each one
    // until we find one that is equal to 3.
    for (uint j = 0; j < blocks; j++) {
      cache[set_index][j].m += 1;
    }
  }
}

void Cache::print_values() {
  printf("offset_bits: %u\n", this->offset_bits);
  printf("index_bits: %u\n", this->index_bits);
}

void Cache::print_cache() {
  for (uint i = 0; i < sets; i++) {
    printf("Set: %d\n", i);
    for (uint j = 0; j < blocks; j++) {
      printf("     tag: %d\n", cache[i][j].tag);
    }
    printf("\n\n");
  }
}
