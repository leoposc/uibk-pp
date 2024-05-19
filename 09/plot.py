import matplotlib.pyplot as plt

# Data for the base version
sizes = [16, 32, 64, 128, 256, 512, 1024, 2048]
times_base = [0.016249, 0.032132, 0.063514, 0.171060, 0.339008, 0.675405, 1.345899, 2.676386]

# Data for the vectorized version
times_vectorized = [0.004942, 0.008899, 0.016813, 0.032562, 0.064029, 0.132815, 0.258489, 0.508887]

# Data for the omp vectorization version
times_vectorization_omp = [0.004950, 0.008863, 0.016758, 0.032418, 0.063694, 0.132514, 0.257857, 0.512471]

# Data for the omp vectorization using double version
times_vectorization_omp_double = [0.009445, 0.018460, 0.034218, 0.065273, 0.132647, 0.257822, 0.508684, 1.566152]

# Data for the intrinsic vectorization version
times_vectorization_intrinsic = [0.004460, 0.008900, 0.018136, 0.033967, 0.065499, 0.172588, 0.340043, 0.674927]

# Plot the data
plt.figure(figsize=(12, 8))

# Plot each set of data
plt.plot(sizes, times_base, label='Base Version', marker='o')
plt.plot(sizes, times_vectorized, label='Vectorized Version', marker='o')
plt.plot(sizes, times_vectorization_omp, label='OMP Vectorization', marker='o')
plt.plot(sizes, times_vectorization_omp_double, label='OMP Vectorization Double', marker='o')
plt.plot(sizes, times_vectorization_intrinsic, label='Intrinsic Vectorization', marker='o')

# Adding titles and labels
plt.title('Performance Comparison: Various Vectorization Techniques')
plt.xlabel('Input Size')
plt.ylabel('Elapsed Time (seconds)')
plt.legend()
plt.grid(True)
plt.xscale('log')
plt.yscale('log')

# Display the plot
plt.show()
