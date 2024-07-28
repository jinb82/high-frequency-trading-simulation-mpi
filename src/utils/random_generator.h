#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator {
public:
    RandomGenerator(unsigned int seed);
    double generate_uniform();
    std::pair<double, double> generate_normal_pair();

private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;
};

#endif // RANDOM_GENERATOR_H
