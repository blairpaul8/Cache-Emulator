#include "cache.hpp"
using namespace std;

Cache::Cache(int sets, int blocks, int size, string trace) {
  this->sets = sets;
  this->blocks = blocks;
  this->size = size;
  this->trace = trace;

  this->fin.open(trace);
}

Cache::~Cache() { this->fin.close(); }
