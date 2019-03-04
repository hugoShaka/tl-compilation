#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"

void dump_ast(uint64_t* ast) {
  uint64_t* affectations = fst(ast);
  uint64_t* expression = snd(ast);

// on itère sur la liste d'affectations
  print((uint64_t*) "Liste des affectations : ");
  uint64_t* elt;
  while (!is_empty(affectations)){
      elt = get_elt(affectations);
      print(fst(elt));
      print((uint64_t*) " = ");
      print_expr(snd(elt));
      affectations = next_elt(affectations);
  }

}

void print_expr(uint64_t* expr){
  uint64_t* type = fst(expr);
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
      print(snd(expr));
  }
  if (type == EVAR){
      print(snd(expr));
  }
}
