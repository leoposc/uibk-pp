import matplotlib.pyplot as plt

# Data
N_values = [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
sequential_times = [0.000008, 0.000039, 0.000207, 0.001137, 0.006283, 0.034635, 0.190891, 1.063763, 5.956524, 33.573178, 189.178032]
parallel_times = [0.003733, 0.002985, 0.003493, 0.001167, 0.001748, 0.007707, 0.020532, 0.100087, 0.525871, 2.792128, 15.392602]

# Calculate speedup
speedup = [seq / par for seq, par in zip(sequential_times, parallel_times)]

# Plotting elapsed times with absolute values
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(N_values, sequential_times, marker='o', label='Sequential')
plt.plot(N_values, parallel_times, marker='o', label='Parallel')
plt.xlabel('N (size of the Delannoy number)')
plt.ylabel('Elapsed Time (seconds)')
plt.title('Sequential vs Parallel Computation Times (Absolute)')
plt.yscale('linear')
plt.legend()
plt.grid(True)

# Plotting speedup
plt.subplot(1, 2, 2)
plt.plot(N_values, speedup, marker='o', label='Speedup')
plt.xlabel('N (size of the Delannoy number)')
plt.ylabel('Speedup')
plt.title('Speedup of Parallel Computation')
plt.legend()
plt.grid(True)

# Save the plot as delannoy_plot_absolute.png in the same directory
plt.tight_layout()
plt.savefig('delannoy_plot_absolute.png')
plt.show()

# Plotting elapsed times with logarithmic scale
plt.figure(figsize=(12, 6))

plt.subplot(1, 2, 1)
plt.plot(N_values, sequential_times, marker='o', label='Sequential')
plt.plot(N_values, parallel_times, marker='o', label='Parallel')
plt.xlabel('N (size of the Delannoy number)')
plt.ylabel('Elapsed Time (seconds)')
plt.title('Sequential vs Parallel Computation Times (Log Scale)')
plt.yscale('log')
plt.legend()
plt.grid(True)

# Plotting speedup
plt.subplot(1, 2, 2)
plt.plot(N_values, speedup, marker='o', label='Speedup')
plt.xlabel('N (size of the Delannoy number)')
plt.ylabel('Speedup')
plt.title('Speedup of Parallel Computation')
plt.legend()
plt.grid(True)

# Save the plot as delannoy_plot_log.png in the same directory
plt.tight_layout()
plt.savefig('delannoy_plot_log.png')
plt.show()
