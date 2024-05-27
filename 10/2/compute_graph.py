import matplotlib.pyplot as plt

# Benchmark results
sequential_times = {
    125: 0.090159,
    250: 0.673094,
    500: 5.441002
}

parallel_times = {
    125: {1: 0.106275, 2: 0.053673, 4: 0.030352, 8: 0.019109, 12: 0.021199},
    250: {1: 0.877507, 2: 0.445015, 4: 0.230918, 8: 0.123333, 12: 0.145078},
    500: {1: 7.003008, 2: 3.509375, 4: 1.791540, 8: 0.939657, 12: 0.728203},
}

# Compute speedup and efficiency
speedup = {}
efficiency = {}

for size, seq_time in sequential_times.items():
    parallel_times_for_size = parallel_times[size]
    speedup[size] = {threads: seq_time / par_time for threads, par_time in parallel_times_for_size.items()}
    efficiency[size] = {threads: speed / threads for threads, speed in speedup[size].items()}

# Plotting
fig, axs = plt.subplots(3, 1, figsize=(10, 15))

# Plot elapsed time
for size, times in parallel_times.items():
    threads = sorted(times.keys())
    times = [times[t] for t in threads]
    axs[0].plot(threads, times, marker='o', label=f'Size {size}')
axs[0].set_xlabel('Number of Threads')
axs[0].set_ylabel('Elapsed Time (seconds)')
axs[0].set_title('Elapsed Time vs Number of Threads')
axs[0].legend()
axs[0].grid(True)

# Plot speedup
for size, spd in speedup.items():
    threads = sorted(spd.keys())
    spd = [spd[t] for t in threads]
    axs[1].plot(threads, spd, marker='o', label=f'Size {size}')
axs[1].set_xlabel('Number of Threads')
axs[1].set_ylabel('Speedup')
axs[1].set_title('Speedup vs Number of Threads')
axs[1].legend()
axs[1].grid(True)

# Plot efficiency
for size, eff in efficiency.items():
    threads = sorted(eff.keys())
    eff = [eff[t] for t in threads]
    axs[2].plot(threads, eff, marker='o', label=f'Size {size}')
axs[2].set_xlabel('Number of Threads')
axs[2].set_ylabel('Efficiency')
axs[2].set_title('Efficiency vs Number of Threads')
axs[2].legend()
axs[2].grid(True)

plt.tight_layout()

plt.savefig('plot.png')

plt.show()
