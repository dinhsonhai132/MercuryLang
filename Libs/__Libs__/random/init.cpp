#include <Mercury.h>

START_DLL

DLL_EXPORT table* random(table* args[]) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    double result = dist(gen);

    table *tab = MER_VALUE(result);
    tab->ref_count = 0;
    return tab;
}

END_DLL