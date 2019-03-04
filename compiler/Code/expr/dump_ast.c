#include "library.h"
#include "arguments.h"
#include "globals.h"
#include "parser.h"
#include "ast.h"

uint64_t node = 0;

uint64_t new_graph_node(){
  node = node + 1;
  return node;
}

uint64_t* structure_children(uint64_t* s){
  uint64_t type = (uint64_t)node_type(s);
  if(type == TYPE_PAIR)
    return cons(fst(s), cons(snd(s), nil()));
  else if(type == TYPE_TRIPLE)
    return cons(fst(s), cons(snd(s), cons(thr(s), nil())));
  else if(type == TYPE_QUADRUPLE)
    return cons(fst(s), cons(snd(s), cons(thr(s), cons (frth(s), nil()))));
  else if(type == TYPE_QUINTUPLE)
    return cons(fst(s), cons(snd(s), cons(thr(s), cons (frth(s), cons(fif(s), nil())))));
  else if(type == TYPE_LIST){
    return s;
  }
  return nil();
}

uint64_t* structure_type(uint64_t* s){
  uint64_t type = (uint64_t)node_type(s);
  if(type == TYPE_PAIR)
    return (uint64_t*)"pair";
  else if(type == TYPE_TRIPLE)
    return (uint64_t*)"triple";
  else if(type == TYPE_QUADRUPLE)
    return (uint64_t*)"quadruple";
  else if(type == TYPE_QUINTUPLE)
    return (uint64_t*)"quintuple";
  else if(type == TYPE_LIST){
    return (uint64_t*)"list";
  } else if(type == TYPE_STRING){
    return fst(s);
  }
  else {
    uint64_t* str = zalloc(30);
    itoa((uint64_t)fst(s), str, 10, 0);
    return str;
  }
}


uint64_t dump_structure(uint64_t* a){
  uint64_t n = new_graph_node();

  printf2((uint64_t*)"n%d [label=\"%s\"]\n", (uint64_t*)n, structure_type(a));
  uint64_t* list = structure_children(a);
  uint64_t i = 0;

  while(!is_empty(list)){
    uint64_t* c = get_elt(list);
    uint64_t n1 = dump_structure(c);
    printf3((uint64_t*)"n%d -> n%d [label=\"%d\"]\n", (uint64_t*)n, (uint64_t*)n1, (uint64_t*)i);
    list = next_elt(list);
    i = i + 1;
  }


  return n;

}


void show_structure(uint64_t* a){

  printf1((uint64_t*)"%s(", structure_type(a));
  uint64_t* list = structure_children(a);
  uint64_t i = 0;

  while(!is_empty(list)){
    uint64_t* c = get_elt(list);
    show_structure(c);
    list = next_elt(list);
    i = i + 1;
    if(!is_empty(list)){
      print((uint64_t*)", ");
    }
  }
  print((uint64_t*)")");
}


void dump_tree(uint64_t* a){
  print((uint64_t*) "digraph G {\n");
  dump_structure(a);
  print((uint64_t*) "}\n");
}
