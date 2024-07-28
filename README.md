
# High-Frequency Trading Simulation with MPI

## Overview
This project implements a high-frequency trading simulation using parallel computing with MPI (Message Passing Interface). The main objective is to achieve significant speedup in random variable generation for trading simulations using the Box-Muller Transformation.

## Performance Highlights
- **5x Speedup**: Achieved a 5x speedup in random variable generation.
- **40% Latency Reduction**: Optimized algorithm latency by 40% using low-latency techniques such as busy-waiting and zero-copy networking.

For detailed performance results, refer to the [Performance Results](docs/performance_results.md).

## Usage
To run the main simulation:
\`\`\`bash
mpirun -np <number_of_processes> ./mpi_box_muller <Mmax>
\`\`\`
- \`<number_of_processes>\`: The number of MPI processes to use.
- \`<Mmax>\`: The maximum number of samples to generate.

Example:
\`\`\`bash
mpirun -np 4 ./mpi_box_muller 1000000
\`\`\`

To run the benchmark:
\`\`\`bash
mpirun -np 1 ./benchmark <Mmax> <optimized>
\`\`\`
- \`<optimized>\`: 0 for non-optimized, 1 for optimized.

Example:
\`\`\`bash
mpirun -np 1 ./benchmark 1000000 1
\`\`\`

