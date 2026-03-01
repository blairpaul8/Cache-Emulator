#include "cache.hpp"
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
}

Cache::~Cache() { this->fin.close(); }

// main method of cahce emulator
void Cache::run() {
  string temp;
  while (getline(this->fin, temp)) {
    // need to convert memory address to int
    string hex_string = temp.substr(2);
    int address = stoi(hex_string, nullptr, 16);

    this->set_index = (address >> offset_bits) & (sets - 1);
    this->tag = address >> (offset_bits + index_bits);

    // delete debug statements later.
    printf("\n");
    printf("set_index: %d\n", set_index);
    printf("tag: %d\n", tag);

    //  we have the set index and the tag now. We need to
    // write a method to search our cache to see if this tag is in it
    // and valid is true if so that is a cache hit otherwise a cache miss.
    // maybe that method can return a bool and we can handle hits and misses in
    // an if else block.
    //
    // NOTE some forward thinking if it is a miss then we need to enforce the
    // LRU policy by evicting the least recently used and replacing it with the
    // new tag for the memory address we are currently proccessing.
  }
}

void Cache::print_values() {
  printf("offset_bits: %u\n", this->offset_bits);
  printf("index_bits: %u\n", this->index_bits);
}
