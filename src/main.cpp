#include <iostream>
#include "models/mpi_box_muller.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <Mmax>" << std::endl;
        return 1;
    }

    int Mmax = std::stoi(argv[1]);
    std::cout << "Mmax = " << Mmax << std::endl;
    unsigned int seed = 123;

    mpi_algorithm(Mmax, seed);

    return 0;
}
