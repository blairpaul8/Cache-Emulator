import subprocess
import matplotlib.pyplot as plt

# Fixed 4-way associativity
blocks = 4
sets = 128  # adjust if needed to keep total cache size same
size = 64

files = ["linear.trace", "random_32kB.trace"]

results = {
    "Linear LRU": None,
    "Random LRU": None,
    "Linear RRIP": None,
    "Random RRIP": None,
}


def run_sim(trace_file, policy=None):
    cmd = [
        "./cache_emulator",
        "--blocks",
        str(blocks),
        "--sets",
        str(sets),
        "--size",
        str(size),
        "--trace",
        f"./trace_files/{trace_file}",
        "--analyze",
    ]

    if policy == "rrip":
        cmd.insert(-1, "--policy")
        cmd.insert(-1, "rrip")

    completed = subprocess.run(cmd, capture_output=True, text=True)
    output = completed.stdout.strip()

    try:
        return float(output)
    except ValueError:
        print(f"Error parsing output: {output}")
        return 0


# Run simulations
results["Linear LRU"] = run_sim("linear.trace")
results["Random LRU"] = run_sim("random_64kB.trace")
results["Linear RRIP"] = run_sim("linear.trace", policy="rrip")
results["Random RRIP"] = run_sim("random_64kB.trace", policy="rrip")


# Prepare bar graph
labels = list(results.keys())
values = list(results.values())

# Color mapping
colors = [
    "blue",  # Linear LRU
    "red",  # Random LRU
    "blue",  # Linear RRIP
    "red",  # Random RRIP
]

plt.figure(figsize=(10, 6))

bars = plt.bar(labels, values, color=colors, width=0.25)

plt.ylabel("Miss Rate")
plt.xlabel("Configuration")
plt.title("Miss Rate Comparison (4-Way Associativity)")

plt.xticks(rotation=20)
plt.grid(axis="y")

# ✅ Dynamic scaling + safe label placement
y_min = min(values)
y_max = max(values)
padding = (y_max - y_min) * 0.2 if y_max != y_min else 0.01

plt.ylim(y_min - padding, y_max + padding)

for i, v in enumerate(values):
    plt.text(i, v + padding * 0.1, f"{v:.4f}", ha="center", fontsize=9)

plt.tight_layout()

# Save to required location
print("saving picture")
plt.savefig("analysis/bar_graph.png", dpi=300)

plt.close()
