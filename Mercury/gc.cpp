#include "../include/gc.h"

int ref_counting_on_stack(stack *stk) {
    int total_ref = 0;
    for (auto it = stk->s_table->table.begin(); it != stk->s_table->table.end(); it++) {
        table *t = *it;
        if (t->ref_count <= 1) {
            total_ref++;
        }
    }

    return total_ref;
}

void collect(stack *stk, const char* file) {
    int total_ref = ref_counting_on_stack(stk);
    int DANGEROUS_REF = 1000;
    
    if (total_ref >= DANGEROUS_REF && !IS_CONTINUE) {
        cout << "Warning: This program has more than " << total_ref << " references on stack, which is too high. This may cause memory leak." << endl;
        std::string input;
        std::cout << "Do you want to continue? (y/n): ";
        std::getline(std::cin, input);
        if (input == "y" || input == "Y") {
            IS_CONTINUE = true;
        } else {
            cout << "Exiting program to prevent memory leak." << endl;
            exit(0);
        }
    }
}

void __unique(std::vector<table*> &tables) {
    std::unordered_set<table*> seen;
    std::vector<table*> result;
    result.reserve(tables.size());

    for (auto ptr : tables) {
        if (seen.insert(ptr).second) {  
            result.push_back(ptr);
        }
    }

    tables.swap(result);
}

void GC_collect(vector<table*> &tables, stack *stk, const char* file) {
#ifdef GC_DEBUG
    cout << "[gc.cpp] [GC_collect] [start] with size of " << tables.size() << " " << endl;
#endif
    
    int sym_ref_0 = 0;
    __unique(tables);

    for (auto it = tables.begin(); it != tables.end(); ) {
        table *t = *it;
        if (!t) {
            cout << "Error: GC: NULL table passed to GC_collect" << endl;
            MER_BREAK_POINT;
        }

        if (t->ref_count <= 0) {
#ifdef GC_DEBUG
            cout << "[gc.cpp] [GC_collect] [starting...] collecting 0x" << int(t->address) << " found at index " << sym_ref_0++ << " " << endl;
#endif
            if (MerCompiler_free_table(t)) {
                cout << "failed to free table Error: GC0" << endl;
                MER_BREAK_POINT;
            }

            it = tables.erase(it);

#ifdef GC_DEBUG
            cout << "[gc.cpp] [GC_collect] [collecting done] done collecting" << " found at index " << sym_ref_0 - 1 << " " << endl;
#endif  
        } else {
            it++;
        }
    }

#ifdef GC_DEBUG
    cout << "[gc.cpp] [GC_collect] [pass]" << endl;
#endif
}
