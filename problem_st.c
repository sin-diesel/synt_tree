#include "problem_st.h"

// Grammar:
// expr ::= mult {+, -} expr | mult
// mult ::= term {*, /} mult | term
// term ::= ( expr ) | number

struct node_t *parse_mult_div();
struct node_t *parse_term();
struct node_t *parse_add_sub();
struct node_t *getnumber();

struct node_t *getnumber(struct lex_array_t* lexarr) { // creates a node with number

    assert(lexarr);
    struct node_t* val = (struct node_t*) calloc(1, sizeof(struct node_t));
    assert(val);

    val->data.k = NODE_VAL;
    val->data.u.d = lexarr->lexems->lex.num;

    lexarr->lexems++;

    return val;
}

struct node_t *parse_expression(struct lex_array_t* lexarr) {

    assert(lexarr);

    struct node_t* val1 = NULL;
    struct node_t* val2 = NULL;
    struct node_t* val3 = NULL;

    int op_kind = 0;

    val1 = parse_mult_div(lexarr);
    assert(val1);

    if (lexarr->lexems->kind == OP && lexarr->lexems->lex.op == ADD) {

        val2 = parse_mult_div(lexarr);
        lexarr->lexems++;
        op_kind = ADD;

    } else if (lexarr->lexems->kind == OP && lexarr->lexems->lex.op == SUB) {

        val2 = parse_mult_div(lexarr);
        lexarr->lexems++;
        op_kind = SUB;

    }

    val3 = (struct node_t*) calloc(1, sizeof(struct node_t));
    assert(val3);
    val3->data.k = NODE_OP;
    val3->data.u.op = op_kind;
    val3->left = val1;
    val3->right = val2;

    return val3;
}

struct node_t *parse_mult_div(struct lex_array_t* lexarr) {

    assert(lexarr);
    struct node_t* val1 = NULL;
    struct node_t* val2 = NULL;
    struct node_t* val3 = NULL;

    int op_kind = 0;

    val1 = parse_term(lexarr);
    if (lexarr->lexems->kind == OP && lexarr->lexems->lex.op == MUL) {

        val2 = parse_term(lexarr);
        op_kind = MUL;
        lexarr->lexems++;

    } else if (lexarr->lexems->kind == OP && lexarr->lexems->lex.op == DIV) {

        val2 = parse_term(lexarr);
        op_kind = DIV;
        lexarr->lexems++;

    }

    val3 = (struct node_t*) calloc(1, sizeof(struct node_t));
    assert(val3);
    val3->data.k = NODE_OP;
    val3->data.u.op = op_kind;
    val3->left = val1;
    val3->right = val2;

    return val3;
}

struct node_t *parse_term(struct lex_array_t* lexarr) {

    assert(lexarr);
    struct node_t* val1 = NULL;

    if (lexarr->lexems->kind == BRACE && lexarr->lexems->lex.b == LBRAC) {

        lexarr->lexems++;
        val1 = parse_expression(lexarr);
        assert(lexarr->lexems->kind == BRACE && lexarr->lexems->lex.b == RBRAC);
        lexarr->lexems++;

        return val1;
    }
    return getnumber(lexarr);
}

struct node_t *parse_add_sub(struct lex_array_t* lexarr) {

}

struct node_t *build_syntax_tree(struct lex_array_t lexarr) {
    
    while (lexarr.lexems != NULL) {
        parse_expression(&lexarr);
    }
}

int calc_result(struct node_t *top) {
  // TODO: your code here
}

void free_syntax_tree(struct node_t * top) {
  // TODO: your code here
}
