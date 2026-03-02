# Cache-Emulator

## Cache Emulator for ECE-356 Computer Systems Architecture

# Starting Notes on cache Emulator

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

Note: if block size on it  is direct mapped
      if blocks > 1 it is set associative

# Testing the emulator

The assignment states the following for testing part 1
Using the Baseline LRU and the random.trace file:
• Fix cache size at 32KB and block size at 64B.
• Vary associativity: Direct Mapped, 2-way, 4-way, 8-way, Fully Associative.
• Plot: Miss Rate vs. Associativity.

NOTE: to calculate sets you can use the following formula

  sets = capacity / (blocks x block_size)
