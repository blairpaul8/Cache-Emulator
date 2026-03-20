# Cache-Emulator

## Cache Emulator for ECE-356 Computer Systems Architecture

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

## Testing the emulator

The assignment states the following for testing part 1
Using the Baseline LRU and the random.trace file:
• Fix cache size at 32KB and block size at 64B.
• Vary associativity: Direct Mapped, 2-way, 4-way, 8-way, Fully Associative.
• Plot: Miss Rate vs. Associativity.

NOTE: to calculate sets you can use the following formula

  sets = capacity / (blocks x block_size)

# Run the Emulator

NOTE: This is 32kB cache block size 64B 8-way associativity.

```
./cache_emulator --blocks 8 --sets 64  --size 64 --trace ./trace_files/random_64kB.trace 
```

To change associativity you need to recalculate number of sets.

## Requirements

You will need to run this program in linux or else there will be compile errors.

## Hand Trace File Command

```
.\cache_emulator --blocks 2 --sets 2  --size 8 --trace ./trace_files/verification.trace
```
