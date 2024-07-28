#include "random_generator.h"
#include <cmath>

RandomGenerator::RandomGenerator(unsigned int seed)
    : generator(seed), distribution(0.0, 1.0) {}

double RandomGenerator::generate_uniform() {
    return distribution(generator);
}

std::pair<double, double> RandomGenerator::generate_normal_pair() {
    double u1 = generate_uniform();
    double u2 = generate_uniform();
    double x1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    double x2 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
    return std::make_pair(x1, x2);
}
