#include "library.h"
#include "ast.h"
#include "riscv.h"

uint64_t tmp_num = 2;

uint64_t new_temporary(){
    tmp_num = tmp_num + 1;
    return tmp_num;
}

uint64_t* symtab;
uint64_t current_stack_slot = 0;

uint64_t find_var(uint64_t* s){
    uint64_t* liste_pos = symtab;
    uint64_t max_stack = 0;
    while (!is_empty(liste_pos)){
        if (string_get(s) == string_get(fst(liste_pos))){
            return snd(liste_pos);
        }
        //check if max_stack
        if (snd(liste_pos) > max_stack){
            max_stack = snd(liste_pos);
        }
        liste_pos = next_elt(liste_pos);
    }
    symtab = cons(paire(s, max_stack+8), symtab);
    return max_stack+8;
}

/* Doit retourner une paire (l, r) où l est une liste d'instructions et r est le
registre résultat. */
uint64_t* compile_expression(uint64_t* e){
    return pair(nil(), (uint64_t*)0);
}

uint64_t* compile_assign(uint64_t* assign){
    return nil();
}

uint64_t* gen_riscv_prog(uint64_t* ast){
    symtab = nil();
    return nil();
}
