#include <mpi.h>
#include <iostream>
#include "random_generator.h"

void test_random_generator() {
    RandomGenerator random_gen(123);
    auto [x1, x2] = random_gen.generate_normal_pair();

    std::cout << "Random values: " << x1 << ", " << x2 << std::endl;
}

int main(int argc, char* argv[]) {
    MPI_Init(NULL, NULL);

    test_random_generator();

    MPI_Finalize();
    return 0;
}
