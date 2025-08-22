#include "../include/ram.h"

vector<table *> _R1 = {};
vector<table *> _R2 = {};
vector<table *> _R3 = {};

MERCURY_API __mer_core_data__ void __push_to_ram(table *t, Mer_uint8_t ram) {
    switch (ram) {
        case REGISTER_1_ADDRESS:
            _R1.push_back(t);
            break;
        case REGISTER_2_ADDRESS:
            _R2.push_back(t);
            break;
        case REGISTER_3_ADDRESS:
            _R3.push_back(t);
            break;
    }
}

MERCURY_API __mer_core_data__ void __pop_from_ram(Mer_uint8_t ram) {
    switch (ram) {
        case REGISTER_1_ADDRESS:
            _R1.pop_back();
            break;
        case REGISTER_2_ADDRESS:
            _R2.pop_back();
            break;
        case REGISTER_3_ADDRESS:
            _R3.pop_back();
            break;
    }
}