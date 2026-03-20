import subprocess
import matplotlib.pyplot as plt

blocks = [1, 2, 4, 8, 512]
sets = [512, 256, 128, 64, 1]
size = 64

files = ["linear.trace", "random.trace"]

lru_results = {}  # store results per file
rrip_results = {}  # store results per file

for file in files:
    lru_results[file] = []
    
    for i in range(len(blocks)):
        b = blocks[i]
        s = sets[i]

        cmd = [
            "./cache_emulator",
            "--blocks", str(b),
            "--sets", str(s),
            "--size", str(size),
            "--trace", f"./trace_files/{file}",
            "--analyze"
        ]

        # Run the command and capture output
        completed = subprocess.run(cmd, capture_output=True, text=True)

        output = completed.stdout.strip()

        # Convert output to number (adjust depending on format)
        try:
            value = float(output)
        except ValueError:
            value = output  # fallback if it's not a clean number

        lru_results[file].append(value)

for file in files:
    rrip_results[file] = []
    
    for i in range(len(blocks)):
        b = blocks[i]
        s = sets[i]

        cmd = [
            "./cache_emulator",
            "--blocks", str(b),
            "--sets", str(s),
            "--size", str(size),
            "--trace", f"./trace_files/{file}",
            "--policy",
            "rrip",
            "--analyze"
        ]

        # Run the command and capture output
        completed = subprocess.run(cmd, capture_output=True, text=True)

        output = completed.stdout.strip()

        # Convert output to number (adjust depending on format)
        try:
            value = float(output)
        except ValueError:
            value = output  # fallback if it's not a clean number

        rrip_results[file].append(value)

fig, axes = plt.subplots(2, 2, figsize=(12, 10))

x_positions = list(range(len(blocks)))
x_labels = [str(b) for b in blocks]

for i, file in enumerate(files):
    miss_rates = lru_results[file]

    axes[0][i].plot(x_positions, miss_rates, marker='o')
    axes[0][i].set_xticks(x_positions)
    axes[0][i].set_xticklabels(x_labels)
    axes[0][i].set_xlabel("Blocks")
    axes[0][i].set_ylabel("Miss Rate")
    axes[0][i].set_title(f"{file} (LRU)")
    axes[0][i].grid()

for i, file in enumerate(files):
    miss_rates = rrip_results[file]

    axes[1][i].plot(x_positions, miss_rates, marker='o')
    axes[1][i].set_xticks(x_positions)
    axes[1][i].set_xticklabels(x_labels)
    axes[1][i].set_xlabel("Blocks")
    axes[1][i].set_ylabel("Miss Rate")
    axes[1][i].set_title(f"{file} (RRIP)")
    axes[1][i].grid()

# Row titles
fig.text(0.5, 0.95, "USING LRU", ha='center', fontsize=16)
fig.text(0.5, 0.48, "USING RRIP", ha='center', fontsize=16)

# Adjust layout so everything fits nicely
fig.subplots_adjust(hspace=0.6)

# Save final combined image
plt.savefig("analysis/comparison.png", dpi=300)

plt.close()