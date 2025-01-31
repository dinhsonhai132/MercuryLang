#include "MerLexer.h"

#define Check_char_identifier(x) ( \
    (x >= 'a' && x <= 'z') || \
    (x >= 'A' && x <= 'Z') || \
    (x == '_') \
)

#define Check_Var_name_identifier(x) { \
    (x >= 'a' && x <= 'z') || \
    (x >= 'A' && x <= 'Z') || \
    (x >= '0' && x <= '9') || \
    (x == '_') \
}

int MerLexer_getn_char(char_state *cur) {
    for (;;) {
        if (cur->cur != cur->inp) {
            if (cur->idx >= MAX_INDEX) {
                return MerCoreError_set_error_mode(cur, E_OVER_F);
            }
            cur->idx++;
            return *cur->cur++;
        }
        if (cur->isend == TRUE) {
            cur->cur = cur->inp;
            cur->idx = cur->end_idx;
        }
        if (cur->status != EOK) return EOF;
        if (!cur || !cur->cur) return EOF;
    }
}

int MerLexer_getn_to_char_by_char(char_state *cur, char cr) {
    int c;
    for (;;) {
        c = MerLexer_getn_char(cur);
        if (c == EOF) {
            return EOF;
        }

        if (c == cr) {
            return *c;
        }
    }
}

int MerLexer_getn_to_char_by_idx(char_state *cur, int idx) {
    int p = 0;
    int c;
    for (;;) {
        c = MerLexer_getn_char(cur);
        if (c == EOF) {
            return EOF;
        }

        if (p == idx) {
            return c;
        }
        p++;
    }
}

int skip_white_space(char_state *cur) {
    int c;
    for (;;) {
        c = MerLexer_getn_char(cur);
        if (c == ' ') {
            continue;
        } else if (c == EOF) {
            cur->isend = EOF;
            cur->cur = cur->inp;
            cur->tok_i
        }
    }
}