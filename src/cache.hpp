#ifndef CACHE_HPP
#define CACHE_HPP

#include <chrono>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// using a timestamp for the LRU right now we can loop through that set and see
// which is the oldest. for that we will need a find_oldest helper function or
// make it a method of the class. The other option is to use a doubly linked
// list to enforce the LRU policy but this seems harder to keep up with.
struct Block {
  int tag;
  bool valid;
  chrono::time_point<chrono::steady_clock> timestamp;

  // hot cold value for RRIP Policy
  int m;
};

class Cache {
private:
  uint64_t sets;
  uint64_t blocks;
  uint64_t size;
  string trace;
  bool rrip;

  ifstream fin;

  // These are the number of bits for this break down of the memory address
  // |  Tag |  Set |  Offset  |
  int offset_bits;
  int index_bits;

  int num_accesses;
  int num_misses;
  int num_hits;
  double hit_miss_ratio;

  // Cache data structure
  vector<vector<Block>> cache;

public:
  // Constructor
  Cache(int sets, int blocks, int size, string trace, bool rrip);

  // Deconstructor
  ~Cache();

  void run();

  // this is for testing delete later.
  void print_values();
  void print_cache();

  // could come up with a better name for this
  // This function returns true if it is a cache hit
  // false if cache miss
  bool search_cache(int set_index, int tag);

  // use this for eviction for LRU
  void replace_oldest(int set_index, Block b);

  // If --policy flag is rrip we will use this run method
  void rrip_policy(int set_index, Block b);
};

#endif // !CACHE_HPP
