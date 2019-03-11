#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "dump_ast.h"
#include "expr_eval.h"
#include <stdio.h>

uint64_t* state;

uint64_t lookup(uint64_t* id){
    //id doit arriver comme un objet string
    printf1((uint64_t*) "Looking %s\n", string_get(id));
    uint64_t* liste_pos = state;
    while (!is_empty(liste_pos)){
        if (string_compare(string_get(id), fst(liste_pos)) == 1){
            return int_get(snd(liste_pos));
        }
        liste_pos = next_elt(liste_pos);
    }
    printf("Error in lookup\n");
    return 0;
}

void set(uint64_t* id, uint64_t val){
    printf2((uint64_t*) "Setting %s : %d\n", id, (uint64_t*) val);
    state = set_recursive(state, id, val);
    dump_state();
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
    uint64_t* affectations = fst(ast);
    uint64_t* retour = snd(ast);
    uint64_t i = 0;
    dump_state();
    // itération sur les affectations
    while (!is_empty(affectations)){
        printf1((uint64_t*) "reading affectation %d \n",(uint64_t*) i);
        uint64_t* affectation = get_elt(affectations);
        set(string_get(fst(affectation)), eval_expr(snd(affectation)));

        affectations = next_elt(affectations);
        i = i+1;
    }

    dump_state();

    return eval_expr(retour);
}

uint64_t eval_expr(uint64_t* ast){
    uint64_t first = int_get(fst(ast));
    printf1((uint64_t*) "%d \n",(uint64_t*) first);
    uint64_t* second = snd(ast);
    if (first == EINT){
        print((uint64_t *) "EINT\n");
        return int_get(second);
    } else if (first == EADD){
        print((uint64_t *) "EADD \n");
        return eval_expr(second) + eval_expr(thr(ast));
    } else if (first == ESUB){
        print((uint64_t *) "ESUB\n");
        return eval_expr(second) - eval_expr(thr(ast));
    } else if (first == EMUL){
        print((uint64_t *) "EMUL\n");
        return eval_expr(second) * eval_expr(thr(ast));
    } else if (first == EVAR){
        print((uint64_t *) "EVAR\n");
        printf1((uint64_t*) "%d\n", (uint64_t*) lookup(second));
        return lookup(second);
    } else{
        print((uint64_t *) "Error in eval_expr");
        return 0;
    }
}

void dump_state(){
    uint64_t* my_state = state;
    while(!is_empty(my_state)){
        printf2((uint64_t *) "%s : %d", fst(my_state),(uint64_t*) int_get(snd(my_state)));
        my_state = next_elt(my_state);

    }
}
