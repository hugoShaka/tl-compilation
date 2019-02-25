#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"

uint64_t* state;

uint64_t lookup(uint64_t* id){
  return -1;
}

void set(uint64_t* id, uint64_t val){

}

uint64_t eval_ast(uint64_t* ast) {
  /* Initialisation de l'état */
  state = nil;
  return 0;
}
