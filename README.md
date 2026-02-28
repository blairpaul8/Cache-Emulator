# Cache-Emulator

## Cache Emulator for ECE-356 Computer Systems Architecture

# Starting Notes on cache Emulator

- The cache is defined by three numbers
  - --sets -> number of sets
  - --blocks -> number of blocks per set
  - --size -> block size in bytes

Total cache = set *blocks* block_size

- A block is a chunck of memory of --size bytes
  - Identified by a tag

- A set is a container of blocks

- Addresses are interpreted as
  | Tag | Set Index | Block Offset |

Note: if block size on it  is direct mapped
      if blocks > 1 it is set associative
