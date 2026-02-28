#ifndef CACHE_HPP
#define CACHE_HPP

#include <fstream>
#include <string>
using namespace std;

class Cache {
private:
  int sets;
  int blocks;
  int size;
  string trace;
  ifstream fin;

public:
  Cache(int sets, int blocks, int size, string trace);
  ~Cache();
};

#endif // !CACHE_HPP
