#include "cache.hpp"
#include <fstream>
#include <iostream>
using namespace std;

enum class Flags {
  sets,
  blocks,
  size,
  trace,
  invalid,
};

Flags map_flags(string &str) {
  if (str == "--sets") {
    return Flags::sets;
  }
  if (str == "--blocks") {
    return Flags::blocks;
  }
  if (str == "--size") {
    return Flags::size;
  }
  if (str == "--trace") {
    return Flags::trace;
  }
  return Flags::invalid;
}

int main(int argc, char *argv[]) {
  if (argc < 9) {
    printf("Usage: %s --sets <num_sets> --blocks <num_blocks> --size "
           "<block_size> --trace <trace_file>\n",
           argv[0]);
  }

  int num_sets = 0;
  int num_blocks = 0;
  int block_size = 0;
  string filename = "";

  int i;
  for (i = 1; i < argc; i += 2) {
    string temp = argv[i];
    switch (map_flags(temp)) {
    case Flags::sets:
      num_sets = atoi(argv[i + 1]);
      break;
    case Flags::blocks:
      num_blocks = atoi(argv[i + 1]);
      break;
    case Flags::size:
      block_size = atoi(argv[i + 1]);
      break;
    case Flags::trace:
      filename = argv[i + 1];
      break;
    case Flags::invalid:
      printf("%s is an invalid flag.\n", argv[i]);
      return 1;
    default:
      printf("Unknown Flag.\n");
      return 1;
    }
  }

  printf("num_sets: %d\n", num_sets);
  printf("num_blocks: %d\n", num_blocks);
  printf("block_size: %d\n", block_size);
  cout << "filename: " << filename << endl;

  return 0;
}
