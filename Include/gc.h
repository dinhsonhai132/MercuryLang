#ifndef MERCURY_GARBAGE_COLLECTOR_HEADER_FILE
#define MERCURY_GARBAGE_COLLECTOR_HEADER_FILE

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#include "data.h"

#define GC_THRESHOLD 1

#define push_to_gc(o) { \
    if ((o)) { \
        if ((o)->ref_count < 1) { \
            GARBAGE_POOL.push_back((o)); \
        } \
    } \
}

int ref_counting_on_stack(stack *stk);
void collect(stack *stk, const char* file);
void GC_collect(vector<table*> &tables, stack *stk, const char* file);

#endif // MERCURY_GARBAGE_COLLECTOR_HEADER_FILE