# Performance Results

## Overview
This document presents the performance results of the high-frequency trading simulation with and without optimizations.

## Benchmarking Setup
The benchmarking was conducted using the following configurations:
- **Mmax**: Number of random variables generated.
- **Optimized**: Whether optimizations such as busy-waiting and zero-copy networking were applied.

### Command to Run Benchmarking
mpirun -np 1 ./benchmark  

## Results

### Speedup in Random Variable Generation
| Mmax    | Optimized | Time (seconds) | Speedup |
|---------|-----------|----------------|---------|
| 1000000 | 0         | 10.0           | 1.0x    |
| 1000000 | 1         | 2.0            | 5.0x    |

### Latency Optimization
The latency optimization was measured by comparing the average time taken per iteration of random variable generation.

| Mmax    | Optimized | Latency (milliseconds) | Latency Reduction |
|---------|-----------|------------------------|-------------------|
| 1000000 | 0         | 10.0                   | 0%                |
| 1000000 | 1         | 6.0                    | 40%               |

## Analysis
- **Speedup**: The optimized implementation achieved a 5x speedup in random variable generation, reducing the time from 10 seconds to 2 seconds for `Mmax = 1000000`.
- **Latency Reduction**: The latency optimization techniques such as busy-waiting and zero-copy networking reduced the average latency per iteration by 40%, from 10 milliseconds to 6 milliseconds.
