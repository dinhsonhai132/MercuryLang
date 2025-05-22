#include "./include/ram.h"

MERCURY_API __mer_core_data__ vector<table*> __push_to_ram(table *t, Mer_uint8_t ram) {
    switch (ram) {
    case REGISTER_1_ADDRESS:
        _R1.push_back(t);
        return _R1;
    case REGISTER_2_ADDRESS:
        _R2.push_back(t);
        return _R2;
    case REGISTER_3_ADDRESS:
        _R3.push_back(t);
        return _R3;
    }

    return _R1;
}

MERCURY_API __mer_core_data__ vector<table*> __pop_from_ram(Mer_uint8_t ram) {
    switch (ram) {
    case REGISTER_1_ADDRESS:
        _R1.pop_back();
        return _R1;
    case REGISTER_2_ADDRESS:
        _R2.pop_back();
        return _R2;
    case REGISTER_3_ADDRESS:
        _R3.pop_back();
        return _R3;
    }

    return _R1;
}