# Cache-Emulator

## Cache Emulator for ECE-356 Computer Systems Architecture

# Run the Emulator

NOTE: This is 32kB cache block size 64B 8-way associativity.

```
./cache_emulator --blocks 8 --sets 64  --size 64 --trace ./trace_files/random_64kB.trace 
```

To change associativity you need to recalculate number of sets.

## Cache Details

- The cache is defined by three numbers
  - --sets -> number of sets
  - --blocks -> number of blocks per set
  - --size -> block size in bytes

Total cache = set x blocks x block_size

- A block is a chunck of memory of --size bytes
  - Identified by a tag

- A set is a container of blocks

- Addresses are interpreted as
  | Tag | Set Index | Block Offset |

## Cache Emulator Implementation

The cache is represented by a Cache class. The main data structure to represent the cache is a 2d array that is an array of sets that holds an array of blocks at each index.

```
vector<vector<Block>> cache;
```

Additionally the blocks are represented by a struct that holds the following mata data about the block

```
struct Block {
  int tag;
  bool valid;
  chrono::time_point<chrono::steady_clock> timestamp;
  int m;
}
```

NOTE: the timestamp is used for the LRU policy and m is used for the RRIP policy.

## Hand Trace File Command

```
.\cache_emulator --blocks 2 --sets 2  --size 8 --trace ./trace_files/verification.trace
```

## Trace Walkthrough

| Time | Address | Binary | Tag | Set | Set 0 | Set 1 | Eviction | Hit/Miss |
|------|---------|--------|-----|-----|-------|-------|----------|----------|
| T1 | `0x10` | `0001 0 000` | 1 | 0 | [**1**,-] | [-,-] |  | Miss |
| T2 | `0x20` | `0010 0 000` | 2 | 0 | [1,**2**] | [-,-] |  | Miss |
| T3 | `0x10` | `0001 0 000` | 1 | 0 | [**1**,2] | [-,-] |  | **Hit** |
| T4 | `0x30` | `0011 0 000` | 3 | 0 | [1,**3**] | [-,-] | Tag 2 (T2) | Miss |
| T5 | `0x20` | `0010 0 000` | 2 | 0 | [**2**,3] | [-,-] | Tag 1 (T3) | Miss |
| T6 | `0x30` | `0011 0 000` | 3 | 0 | [2,**3**] | [-,-] |  | **Hit** |
| T7 | `0x48` | `0100 1 000` | 4 | 1 | [2,3] | [**4**,-] |  | Miss |
| T8 | `0x30` | `0011 0 000` | 3 | 0 | [2,**3**] | [4,-] |  | **Hit** |
| T9 | `0x18` | `0001 1 000` | 1 | 1 | [2,3] | [4,**1**] |  | Miss |
| T10 | `0x18` | `0001 1 000` | 1 | 1 | [2,3] | [4,**1**] |  | **Hit** |
