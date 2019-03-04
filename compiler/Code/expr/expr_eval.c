#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "dump_ast.h"
#include "expr_eval.h"
#include <stdio.h>

uint64_t* state;

uint64_t lookup(uint64_t* id){
    uint64_t* liste_pos = state;
    while (!is_empty(liste_pos)){
        if (string_compare(id, fst(liste_pos)) == 1){
            return int_get(snd(liste_pos));
        }
        liste_pos = next_elt(liste_pos);
    }
    printf("Error in lookup\n");
    return 0;
}

void set(uint64_t* id, uint64_t val){
    state = set_recursive(state, id, val);
}

uint64_t* set_recursive(uint64_t* sub_state, uint64_t* id, uint64_t val){
    if (is_empty(sub_state)){
        // return nil();
        return cons(pair(id, make_int(val)), nil());
    }
    if (string_compare(id, fst(get_elt(sub_state)))){
        return cons(pair(id, make_int(val)), next_elt(sub_state));
    }else {
        return cons(get_elt(sub_state), set_recursive(next_elt(sub_state), id, val));
    }
}

uint64_t eval_ast(uint64_t* ast) {
  /* Initialisation de l'état */
  state = nil();

  return 0;
}
