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

uint64_t* pair(uint64_t* fst, uint64_t* snd){
  uint64_t* pair = zalloc(2*SIZEOFUINT64STAR);
  array_set(pair, 0, fst);
  array_set(pair, 1, snd);
  return pair;
}

uint64_t* triple(uint64_t* fst, uint64_t* snd, uint64_t* thr){
  uint64_t* pair = zalloc(3*SIZEOFUINT64STAR);
  array_set(pair, 0, fst);
  array_set(pair, 1, snd);
  array_set(pair, 2, thr);
  return pair;
}

uint64_t* quadruple(uint64_t* fst, uint64_t* snd, uint64_t* thr, uint64_t* frth){
  uint64_t* pair = zalloc(4*SIZEOFUINT64STAR);
  array_set(pair, 0, fst);
  array_set(pair, 1, snd);
  array_set(pair, 2, thr);
  array_set(pair, 3, frth);
  return pair;
}

uint64_t* quintuple(uint64_t* fst, uint64_t* snd, uint64_t* thr, uint64_t* frth, uint64_t* fif){
  uint64_t* pair = zalloc(5*SIZEOFUINT64STAR);
  array_set(pair, 0, fst);
  array_set(pair, 1, snd);
  array_set(pair, 2, thr);
  array_set(pair, 3, frth);
  array_set(pair, 4, fif);
  return pair;
}

/* Accesseurs [fst] et [snd] */
uint64_t* fst(uint64_t* p){
  return array_get(p,0);
}
uint64_t* snd(uint64_t* p){
  return array_get(p,1);
}
uint64_t* thr(uint64_t* p){
  return array_get(p,2);
}
uint64_t* frth(uint64_t* p){
  return array_get(p,3);
}
uint64_t* fif(uint64_t* p){
  return array_get(p,4);
}

/* Listes */
/* On construit les listes avec [cons(x,l)] (la liste composé de l'élément [x]
   suivi de la liste [l]) et [nil], la liste vide. */

uint64_t* cons(uint64_t* elt, uint64_t* l) {
  return pair(elt,l);
}

uint64_t* nil = NULL;

/* Parcours de liste : [get_elt(l)] renvoie l'élément en tête de liste et
   [next_elt(l)] renvoie un pointeur vers le reste de la liste. */

uint64_t* get_elt(uint64_t* l) {
  return (uint64_t*)(*(l + 0));
}

uint64_t* next_elt(uint64_t* l) {
  return (uint64_t*)(*(l + 1));
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

uint64_t* make_terms(uint64_t* term, uint64_t* other){
 return NULL;
}

uint64_t* make_factors(uint64_t* factor, uint64_t* other){
 return NULL;
}


