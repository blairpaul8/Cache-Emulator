import random

BASE_ADDR = 0x40000000
NUM_ACCESSES = 10000


def generate_rrip_vs_lru():
    """
    Strong test where:
    - Small hot set (frequently reused)
    - Large streaming set that should NOT be kept
    LRU will get polluted, RRIP will resist.
    """
    random.seed(42)

    HOT_SET = 2 * 1024  # VERY small hot set (2KB)
    STREAM_SET = 256 * 1024  # VERY large stream (256KB)

    with open("rrip_vs_lru.trace", "w") as f:
        for i in range(NUM_ACCESSES):
            # Every 5th access is hot (frequent reuse)
            if i % 5 == 0:
                offset = random.randint(0, HOT_SET)
            else:
                # Heavy stream pressure
                offset = random.randint(HOT_SET, STREAM_SET)

            addr = BASE_ADDR + offset
            addr &= ~3
            f.write(f"0x{addr:08x}\n")


if __name__ == "__main__":
    generate_rrip_vs_lru()
    print("Generated rrip_vs_lru.trace")
