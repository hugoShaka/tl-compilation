#include "globals.h"
#include "riscv.h"
#include "ast.h"
#include "library.h"


uint64_t* riscv_state;
uint64_t* riscv_stack;
uint64_t riscv_stack_size;

uint64_t* assoc_get(uint64_t* l, uint64_t* id){
  if(!is_empty(l)){
    uint64_t* elt = get_elt(l);
    if ((uint64_t)fst(elt) == (uint64_t) id){
      return snd(elt);
    }
    return assoc_get(next_elt(l), id);
  }
  return NULL;
}

uint64_t* assoc_set(uint64_t* l, uint64_t* id, uint64_t* v){
  if(!is_empty(l)){
    uint64_t* elt = get_elt(l);
    if ((uint64_t)fst(elt) == (uint64_t) id){
      return cons(pair(id, v),next_elt(l));
    }
    return cons(elt,assoc_set(next_elt(l),id,v));
  } else {
    return cons(pair(id,v),l);
  }
}

void dump_riscv_state(){
  uint64_t* s = riscv_state;
  while(!is_empty(s)){
    uint64_t* e = get_elt(s);
    print_reg((uint64_t)fst(e));
    printf1((uint64_t*)" = %d\t", snd(e));
    s = next_elt(s);
  }
}

void check_valid_offset(uint64_t ofs){
  if(ofs < 0) {
    printf1((uint64_t*) "Trying to write in stack at offset %d.\n", (uint64_t*)ofs);
    exit(-1);
  }
  if(ofs >= riscv_stack_size) {
    printf1((uint64_t*) "Trying to write in stack at offset %d.\n", (uint64_t*)ofs);
    exit(-1);
  }
  if(ofs % REGISTERSIZE != 0){
    printf2((uint64_t*) "Trying to write in stack at misaligned offset %d. (should be a multiple of %d)\n", (uint64_t*)ofs, (uint64_t*)REGISTERSIZE);
    exit(-1);
  }
}

void write_stack(uint64_t ofs, uint64_t v){
  check_valid_offset(ofs);
  *(riscv_stack + ofs / REGISTERSIZE) = v;
}

uint64_t load_stack(uint64_t ofs){
  check_valid_offset(ofs);
  return *(riscv_stack + ofs / REGISTERSIZE);
}

uint64_t* riscv_labels;

void setup_labels(uint64_t* prog){
  uint64_t n = 0;
  riscv_labels = nil();
  while(!is_empty(prog)){
    uint64_t* instr = get_elt(prog);
    uint64_t op = (uint64_t)fst(instr);
    if(op == RV_LABEL){
      uint64_t* lab = snd(instr);
      riscv_labels = assoc_set(riscv_labels, lab, some((uint64_t*)n));
    }
    n = n + 1;
    prog = next_elt(prog);
  }
}

uint64_t resolve_label(uint64_t lab){
  uint64_t* line = assoc_get(riscv_labels, (uint64_t*)lab);
  if(line){
    return (uint64_t)fst(line);
  } else {
    printf1((uint64_t*) "Trying to jump to undefined label L%d.\n", (uint64_t*)lab);
    exit(-1);
    return -1;
  }
}

uint64_t eval_riscv_at(uint64_t* prog, uint64_t n){
  uint64_t* instr = list_nth(prog, n);
  if(!instr){
    return (uint64_t)assoc_get(riscv_state, (uint64_t*)REG_RET);
  }
  if(debug_riscv){
    dump_riscv_state();
    print((uint64_t*)"\nExecuting ");
    show_riscv_instr(instr);
  }
  uint64_t op = (uint64_t)fst(instr);
  uint64_t succ = n + 1;
  if(op == RV_CONST) {
    riscv_state = assoc_set(riscv_state, snd(instr), thr(instr));
  }
  else if(op == RV_ADD) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,thr(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,frth(instr));
    riscv_state = assoc_set(riscv_state, snd(instr), (uint64_t*) (n1 + n2));
  }
  else if(op == RV_SUB) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,thr(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,frth(instr));
    riscv_state = assoc_set(riscv_state, snd(instr), (uint64_t*) (n1 - n2));
  }
  else if(op == RV_MUL) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,thr(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,frth(instr));
    riscv_state = assoc_set(riscv_state, snd(instr), (uint64_t*) (n1 * n2));
  }
  else if(op == RV_LOAD) {
    uint64_t rd = (uint64_t)assoc_get(riscv_state,thr(instr));
    uint64_t ofs = (uint64_t)frth(instr);
    riscv_state = assoc_set(riscv_state, snd(instr),
                            (uint64_t*)load_stack(rd + ofs));
  }
  else if(op == RV_STORE) {
    uint64_t rd = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t ofs = (uint64_t)thr(instr);
    uint64_t v = (uint64_t)assoc_get(riscv_state, frth(instr));
    write_stack(rd + ofs, v);
  }
  else if(op == RV_LABEL) {
  }
  else if(op == RV_MOVE) {
    riscv_state = assoc_set(riscv_state, snd(instr),
                            assoc_get(riscv_state,thr(instr)));
  }
  else if(op == RV_BEQ) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,thr(instr));
    if (n1 == n2) succ = resolve_label((uint64_t)frth(instr));
  }
  else if(op == RV_BLT) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,thr(instr));
    if (n1 < n2) succ = resolve_label((uint64_t)frth(instr));
    printf3((uint64_t*)"blt r%d, r%d, L%d\n", snd(instr), thr(instr), frth(instr));
  }
  else if(op == RV_BLE) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,thr(instr));
    if (n1 <= n2) succ = resolve_label((uint64_t)frth(instr));
    printf3((uint64_t*)"ble r%d, r%d, L%d\n", snd(instr), thr(instr), frth(instr));
  }
  else if(op == RV_BGT) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,thr(instr));
    if (n1 > n2) succ = resolve_label((uint64_t)frth(instr));
    printf3((uint64_t*)"bgt r%d, r%d, L%d\n", snd(instr), thr(instr), frth(instr));
  }
  else if(op == RV_BGE) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,thr(instr));
    if (n1 >= n2) succ = resolve_label((uint64_t)frth(instr));
    printf3((uint64_t*)"bge r%d, r%d, L%d\n", snd(instr), thr(instr), frth(instr));
  }
  else if(op == RV_BNE) {
    uint64_t n1 = (uint64_t)assoc_get(riscv_state,snd(instr));
    uint64_t n2 = (uint64_t)assoc_get(riscv_state,thr(instr));
    if (n1 != n2) succ = resolve_label((uint64_t)frth(instr));
    printf3((uint64_t*)"bne r%d, r%d, L%d\n", snd(instr), thr(instr), frth(instr));
  }
  else if(op == RV_JMP) {
    succ = (uint64_t)resolve_label((uint64_t)snd(instr));
  }
  else {
    print((uint64_t*)"unrecognized instruction\n");
  }
  return eval_riscv_at(prog, succ);
}

uint64_t eval_riscv_prog(uint64_t* prog){
  riscv_stack_size = 100 * REGISTERSIZE;
  riscv_stack = zalloc(riscv_stack_size);
  riscv_state = nil();
  riscv_state = assoc_set(riscv_state, (uint64_t*)REG_SP, (uint64_t*)(riscv_stack_size));
  setup_labels(prog);
  uint64_t v = eval_riscv_at(prog, 0);
  if(debug_riscv){
    dump_riscv_state();
    print((uint64_t*)"\n");
  }
  return v;
}
