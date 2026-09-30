import matplotlib.pyplot as plt

# Number of MPI processes
processes = [1, 2, 4, 8]

# Exercise 2 results
exercise2_time = [0.010951, 0.006239, 0.004120, 0.002156]
exercise2_speedup = [1.000, 1.755, 2.658, 5.079]

# Exercise 3 results
exercise3_time = [0.135876, 0.075890, 0.035822, 0.019808]
exercise3_speedup = [1.000, 1.790, 3.793, 6.859]


# ==========================================
# Graph 1: Time vs Number of Processors
# ==========================================

plt.figure(figsize=(8, 5))

plt.plot(
    processes,
    exercise2_time,
    marker='o',
    label='Exercise 2 - Parallel Addition'
)

plt.plot(
    processes,
    exercise3_time,
    marker='o',
    label='Exercise 3 - Monte Carlo Pi'
)

plt.xlabel('Number of Processors')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs Number of Processors')
plt.xticks(processes)
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig('Exercise4/time_vs_processors.png', dpi=300)
plt.close()


# ==========================================
# Graph 2: Speedup vs Number of Processors
# ==========================================

plt.figure(figsize=(8, 5))

plt.plot(
    processes,
    exercise2_speedup,
    marker='o',
    label='Exercise 2 - Parallel Addition'
)

plt.plot(
    processes,
    exercise3_speedup,
    marker='o',
    label='Exercise 3 - Monte Carlo Pi'
)

# Ideal speedup reference
plt.plot(
    processes,
    processes,
    linestyle='--',
    label='Ideal Speedup'
)

plt.xlabel('Number of Processors')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Processors')
plt.xticks(processes)
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig('Exercise4/speedup.png', dpi=300)
plt.close()


print("Graphs created successfully!")
print("Exercise4/time_vs_processors.png")
print("Exercise4/speedup.png")
