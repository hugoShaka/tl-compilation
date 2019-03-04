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
  return 0;
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
