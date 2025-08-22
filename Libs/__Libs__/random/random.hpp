#ifndef MERCURY_RANDOM_HPP
#define MERCURY_RANDOM_HPP

#include <random>
#include <vector>
#include <algorithm>

namespace mrandom {

    inline std::mt19937 &engine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    inline int rand_int(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine());
    }

    inline double rand_double(double min, double max) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(engine());
    }

    inline float rand_float(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(engine());
    }
}

#endif // MERCURY_RANDOM_HPP
