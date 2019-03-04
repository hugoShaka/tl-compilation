#include "library.h"
#include "arguments.h"
#include "globals.h"
#include "parser.h"

/* Manipulation de tableaux */

/* Obtenir le n-ième élément */
uint64_t* array_get(uint64_t* p, uint64_t i){
  return (uint64_t*)(*(p+i));
}

/* Définir le n-ième élément (un pointeur) */
void array_set(uint64_t* p, uint64_t i, uint64_t* v){
  *(p+i) = (uint64_t)v;
}

/* Structures de données */

/* Tuples */

/* Création de valeurs, paires, triplets et quadruplets taggés */

/* Paire */


uint64_t TYPE_PAIR = 1;
uint64_t TYPE_TRIPLE = 2;
uint64_t TYPE_QUADRUPLE = 3;
uint64_t TYPE_QUINTUPLE = 4;
uint64_t TYPE_LIST = 5;
uint64_t TYPE_INT = 6;
uint64_t TYPE_STRING = 7;
uint64_t TYPE_OPTION = 8;

uint64_t* some(uint64_t* fst){
  uint64_t* pair = zalloc(2*SIZEOFUINT64STAR);
  array_set(pair, 0, (uint64_t*)TYPE_OPTION);
  array_set(pair, 1, fst);
  return pair;
}

uint64_t* pair(uint64_t* fst, uint64_t* snd){
  uint64_t* pair = zalloc(3*SIZEOFUINT64STAR);
  array_set(pair, 0, (uint64_t*)TYPE_PAIR);
  array_set(pair, 1, fst);
  array_set(pair, 2, snd);
  return pair;
}

uint64_t* triple(uint64_t* fst, uint64_t* snd, uint64_t* thr){
  uint64_t* pair = zalloc(4*SIZEOFUINT64STAR);
  array_set(pair, 0, (uint64_t*)TYPE_TRIPLE);
  array_set(pair, 1, fst);
  array_set(pair, 2, snd);
  array_set(pair, 3, thr);
  return pair;
}

uint64_t* quadruple(uint64_t* fst, uint64_t* snd, uint64_t* thr, uint64_t* frth){
  uint64_t* pair = zalloc(5*SIZEOFUINT64STAR);
  array_set(pair, 0, (uint64_t*)TYPE_QUADRUPLE);
  array_set(pair, 1, fst);
  array_set(pair, 2, snd);
  array_set(pair, 3, thr);
  array_set(pair, 4, frth);
  return pair;
}

uint64_t* quintuple(uint64_t* fst, uint64_t* snd, uint64_t* thr, uint64_t* frth, uint64_t* fif){
  uint64_t* pair = zalloc(6*SIZEOFUINT64STAR);
  array_set(pair, 0, (uint64_t*)TYPE_QUADRUPLE);
  array_set(pair, 1, fst);
  array_set(pair, 2, snd);
  array_set(pair, 3, thr);
  array_set(pair, 4, frth);
  array_set(pair, 5, fif);
  return pair;
}

uint64_t node_type(uint64_t* p){
  return (uint64_t)array_get(p, 0);
}
/* Accesseurs [fst] et [snd] */
uint64_t* fst(uint64_t* p){
  return array_get(p,1);
}
uint64_t* snd(uint64_t* p){
  return array_get(p,2);
}
uint64_t* thr(uint64_t* p){
  return array_get(p,3);
}
uint64_t* frth(uint64_t* p){
  return array_get(p,4);
}
uint64_t* fif(uint64_t* p){
  return array_get(p,5);
}

uint64_t* make_int(uint64_t n){
  uint64_t * p = zalloc(2*SIZEOFUINT64STAR);
  array_set(p, 0, (uint64_t*)TYPE_INT);
  array_set(p, 1, (uint64_t*)n);
  return p;
}

void check_is_int(uint64_t* l){
  if(node_type(l) != TYPE_INT){
    print((uint64_t*)"check_is_int: error: not a int");
    exit(-1);
  }
}


uint64_t int_get(uint64_t* l){
  check_is_int(l);
  return (uint64_t)array_get(l, 1);
}

uint64_t is_int(uint64_t* s, uint64_t n){
  return int_get(s) == n;
}

uint64_t* make_string(uint64_t* n){
  uint64_t * p = zalloc(2*SIZEOFUINT64STAR);
  array_set(p, 0, (uint64_t*)TYPE_STRING);
  array_set(p, 1, n);
  return p;
}

void check_is_string(uint64_t* l){
  if(node_type(l) != TYPE_STRING){
    print((uint64_t*)"check_is_string: error: not a string");
    exit(-1);
  }
}

uint64_t* string_get(uint64_t* l){
  check_is_string(l);
  return array_get(l, 1);
}

uint64_t is_string(uint64_t* s, uint64_t* n){
  return string_compare(string_get(s), n);
}


/* Listes */
/* On construit les listes avec [cons(x,l)] (la liste composé de l'élément [x]
   suivi de la liste [l]) et [nil], la liste vide. */

uint64_t* cons(uint64_t* elt, uint64_t* l) {
  uint64_t * p = zalloc(3*SIZEOFUINT64STAR);
  array_set(p, 0, (uint64_t*)TYPE_LIST);
  array_set(p, 1, pair(elt, l));
  return p;
}

uint64_t* nil() {
  uint64_t * p = zalloc(2*SIZEOFUINT64STAR);
  array_set(p, 0, (uint64_t*)TYPE_LIST);
  array_set(p, 1, NULL);
  return p;
}

/* Parcours de liste : [get_elt(l)] renvoie l'élément en tête de liste et
   [next_elt(l)] renvoie un pointeur vers le reste de la liste. */

void check_is_list(uint64_t* l){
  if(node_type(l) != TYPE_LIST){
    print((uint64_t*)"check_is_list: error: not a list");
    exit(-1);
  }
}

uint64_t* get_elt(uint64_t* l) {
  check_is_list(l);
  return fst(array_get(l,1));
}

uint64_t* next_elt(uint64_t* l) {
  check_is_list(l);
  return snd(array_get(l,1));
}

uint64_t is_empty(uint64_t* l){
  check_is_list(l);
  return array_get(l,1) == NULL;
}

/* Expressions */
uint64_t EINT = 0;
uint64_t EADD = 3;
uint64_t ESUB = 4;
uint64_t EMUL = 5;
uint64_t EDIV = 6;
uint64_t EMOD = 7;
uint64_t EVAR = 8;
uint64_t ENEG = 13;


uint64_t* string_of_expr_tag(uint64_t et){
  if (et == EINT) return (uint64_t*) "EINT";
  if (et == EADD) return (uint64_t*) "EADD";
  if (et == ESUB) return (uint64_t*) "ESUB";
  if (et == EMUL) return (uint64_t*) "EMUL";
  if (et == EDIV) return (uint64_t*) "EDIV";
  if (et == EMOD) return (uint64_t*) "EMOD";
  if (et == EVAR) return (uint64_t*) "EVAR";
  if (et == ENEG) return (uint64_t*) "ENEG";
  return (uint64_t*) "<unexpected expr tag>";
}


uint64_t* assoc_string_get(uint64_t* l, uint64_t* id){
  if(!is_empty(l)){
    uint64_t* elt = get_elt(l);
    if (is_string(fst(elt), id)){
      return snd(elt);
    }
    return assoc_string_get(next_elt(l), id);
  }
  return NULL;
}

uint64_t* assoc_string_set(uint64_t* l, uint64_t* id, uint64_t* v){
  if(!is_empty(l)){
    uint64_t* elt = get_elt(l);
    if (is_string(fst(elt), id)){
      return cons(pair(make_string(id), v),next_elt(l));
    }
    return cons(elt,assoc_string_set(next_elt(l),id,v));
  } else {
    return cons(pair(make_string(id),v),l);
  }
}

uint64_t* list_append(uint64_t* l1, uint64_t* l2){
  if(!is_empty(l1)){
    return cons(get_elt(l1), list_append(next_elt(l1), l2));
  }
  return l2;
}

uint64_t* list_nth(uint64_t* l, uint64_t n){
  if(!is_empty(l)){
    if(n <= 0){
      return get_elt(l);
    }
    return list_nth(next_elt(l), n - 1);
  }
  return NULL;
}


uint64_t* make_terms(uint64_t* term, uint64_t* other){
  return NULL;
}

uint64_t* make_factors(uint64_t* factor, uint64_t* other){
  return NULL;
}
