#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "expr_dump.h"
#include <stdio.h>

void dump_ast(uint64_t* ast) {
  uint64_t* affectations = fst(ast);

// on itère sur la liste d'affectations
  print((uint64_t*) "Liste des affectations : ");
  uint64_t* elt;
  while (!is_empty(affectations)){
      elt = get_elt(affectations);
      print(string_get(fst(elt)));
      print((uint64_t*) " = ");
      print_expr(snd(elt));
      affectations = next_elt(affectations);
  }

}

void print_expr(uint64_t* expr){
  uint64_t type = int_get(fst(expr));
  if (type == EADD){
      print_expr(snd(expr));
      print((uint64_t*) "+");
      print_expr(thr(expr));
  }
  if (type == ESUB){
      print_expr(snd(expr));
      print((uint64_t*) "-");
      print_expr(thr(expr));
  }
  if (type == EMUL){
      print_expr(snd(expr));
      print((uint64_t*) "*");
      print_expr(thr(expr));
  }
  if (type == EINT){
      printf("%d",int_get(snd(expr)));
  }
  if (type == EVAR){
      printf("%s",string_get(snd(expr)));
  }
}
