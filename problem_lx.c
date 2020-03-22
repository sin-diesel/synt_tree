#include "problem_lx.h"
#include <ctype.h>

struct ret_t {

    int num;
    int shift;

};

void skip_spaces(const char* str) {

    assert(str);
    while (isspace(*str)) {
        ++str;
    }

}
void getnum(const char* str, struct ret_t* ret) {

    assert(str);
    int num = 0;
    int i = 0;

    while (isdigit(*str)) {

        num = num * 10;
        ++i;
        num += *str - '0';
        ++str;

    }
    ret->num = num;
    ret->shift = i;

}

struct lex_array_t lex_string(const char *str) {

    assert(str != NULL);

    struct lex_array_t larr = { malloc(ICAP * sizeof(struct lexem_t)),
                                0,
                                ICAP };
    assert(larr.lexems != NULL);

    int count = 0;
    int num = 0;

    while (*str != '\0') {

        struct ret_t* ret_data = (struct ret_t*) calloc(1, sizeof(struct ret_t));

        skip_spaces(str);

        if (*str == '(') {
            larr.lexems[count].kind = BRACE;
            larr.lexems[count].lex.b = LBRAC;
        } else if (*str == ')') {
            larr.lexems[count].kind = BRACE;
            larr.lexems[count].lex.b = RBRAC;
        }
        else if (*str == '+') {
            larr.lexems[count].kind = OP;
            larr.lexems[count].lex.op = ADD;
        }
        else if (*str == '*') {
            larr.lexems[count].kind = OP;
            larr.lexems[count].lex.op = MUL;
        }
        else if (*str == '/') {
            larr.lexems[count].kind = OP;
            larr.lexems[count].lex.op = DIV;
        }
        else if (*str == '-') {
            larr.lexems[count].kind = OP;
            larr.lexems[count].lex.op = SUB;
        }
        else if (*str != '\0') {
            getnum(str, ret_data);
            larr.lexems[count].kind = NUM;
            larr.lexems[count].lex.num = ret_data->num;
            str += ret_data->shift - 1;
        } else {
            free(larr.lexems);
            larr.lexems = NULL;
        }

        free(ret_data);
        ++str;
        ++count;

    }

    // TODO:
    // for each char in str
    //   if char reminds space, skip it
    //   if char reminds number, lex number
    //   if char reminds brace, lex brace
    //   if char reminds operation, lex operation
    //   otherwise free lex array, return NULL

    return larr;
}

static void
print_op(enum operation_t opcode) {
    switch(opcode) {
        case ADD: printf(" PLUS"); break;
        case SUB: printf(" MINUS"); break;
        case MUL: printf(" MUL"); break;
        case DIV: printf(" DIV"); break;
        default: assert(0 && "unknown opcode");
    }
}

static void
print_brace(enum braces_t bracetype) {
    switch(bracetype) {
        case LBRAC: printf(" LBRAC"); break;
        case RBRAC: printf(" RBRAC"); break;
        default: assert(0 && "unknown bracket");
    }
}

static void
print_num(int n) {
    printf(" NUMBER:%d", n);
}

void
print_lexem(struct lexem_t lxm) {
    switch(lxm.kind) {
        case OP: print_op(lxm.lex.op); break;
        case BRACE: print_brace(lxm.lex.b); break;
        case NUM: print_num(lxm.lex.num); break;
        default: assert(0 && "unknown lexem");
    }
}

void dump_lexarray(struct lex_array_t pl) {
    int i;
    assert(pl.lexems != NULL);
    for (i = 0; i < pl.size; ++i)
        print_lexem(pl.lexems[i]);
}
