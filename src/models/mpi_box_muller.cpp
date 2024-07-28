#include <mpi.h>
#include <iostream>
#include <fstream>
#include "random_generator.h"

void mpi_algorithm(int Mmax, unsigned int seed) {
    int rank, size;

    // Initialize an MPI session
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get the number of processes

    int N = size;  // Total number of processes

    // Output the number of processes and the rank of the current process
    std::cout << "N = " << N << std::endl;
    std::cout << "Core = " << rank << std::endl;

    // Initialize random number generator
    RandomGenerator random_gen(seed + rank);

    if (rank == 0) {
        double E = 0.0, V = 0.0;
        int M = 0;
        double message[3] = {E, V, static_cast<double>(M)};

        int target = 1 + (rand() % (N - 1));
        MPI_Send(message, 3, MPI_DOUBLE, target, 0, MPI_COMM_WORLD);

        while (true) {
            MPI_Recv(message, 3, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            E = message[0];
            V = message[1];
            M = static_cast<int>(message[2]);

            if (M == Mmax) {
                std::ofstream outfile("output.txt");
                std::cerr << "E/Mmax= " << E / Mmax << std::endl;
                std::cerr << "V/Mmax - E^2/Mmax^2= " << V / Mmax - E * E / (Mmax * Mmax) << std::endl;
                outfile << "E/Mmax= " << E / Mmax << std::endl;
                outfile << "V/Mmax - E^2/Mmax^2= " << V / Mmax - E * E / (Mmax * Mmax) << std::endl;
                outfile.close();
                break;
            } else {
                auto [x1, x2] = random_gen.generate_normal_pair();

                E += x1 * x1 + x2 * x2;
                V += (x1 * x1 + x2 * x2) * (x1 * x1 + x2 * x2);
                M++;

                int target;
                do {
                    target = rand() % N;
                } while (target == rank);

                message[0] = E;
                message[1] = V;
                message[2] = static_cast<double>(M);
                MPI_Send(message, 3, MPI_DOUBLE, target, 0, MPI_COMM_WORLD);
            }
        }

        for (int i = 1; i < N; ++i) {
            MPI_Send(message, 3, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        }
    } else {
        double message[3];
        while (true) {
            MPI_Status status;
            MPI_Recv(message, 3, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == 1) {
                break;
            }

            double E = message[0];
            double V = message[1];
            int M = static_cast<int>(message[2]);

            if (M < Mmax) {
                auto [x1, x2] = random_gen.generate_normal_pair();

                E += x1 * x1 + x2 * x2;
                V += (x1 * x1 + x2 * x2) * (x1 * x1 + x2 * x2);
                M++;

                int target;
                do {
                    target = rand() % N;
                } while (target == rank);

                message[0] = E;
                message[1] = V;
                message[2] = static_cast<double>(M);
                MPI_Send(message, 3, MPI_DOUBLE, target, 0, MPI_COMM_WORLD);
            } else {
                MPI_Send(message, 3, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
}
