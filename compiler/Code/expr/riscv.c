#include "library.h"
#include "ast.h"

/* Registers */

uint64_t REG_ZERO = 0;
uint64_t REG_RET  = 1;
uint64_t REG_SP   = 2;

/* Instructions */

uint64_t RV_CONST = 1;
uint64_t RV_ADD = 2;
uint64_t RV_SUB = 3;
uint64_t RV_MUL = 4;
uint64_t RV_LOAD = 5;
uint64_t RV_STORE = 6;
uint64_t RV_LABEL = 7;
uint64_t RV_MOVE = 8;
uint64_t RV_BEQ = 9;
uint64_t RV_BLT = 10;
uint64_t RV_BLE = 11;
uint64_t RV_BGT = 12;
uint64_t RV_BGE = 13;
uint64_t RV_BNE = 14;
uint64_t RV_JMP = 15;

uint64_t* string_of_instr(uint64_t i){
  if(i == RV_CONST) return (uint64_t*)"RV_CONST";
  else if(i == RV_ADD) return (uint64_t*)"RV_ADD";
  else if(i == RV_SUB) return (uint64_t*)"RV_SUB";
  else if(i == RV_MUL) return (uint64_t*)"RV_MUL";
  else if(i == RV_LOAD) return (uint64_t*)"RV_LOAD";
  else if(i == RV_STORE) return (uint64_t*)"RV_STORE";
  else if(i == RV_LABEL) return (uint64_t*)"RV_LABEL";
  else if(i == RV_MOVE) return (uint64_t*)"RV_MOVE";
  else if(i == RV_BEQ) return (uint64_t*)"RV_BEQ";
  else if(i == RV_BLT) return (uint64_t*)"RV_BLT";
  else if(i == RV_BLE) return (uint64_t*)"RV_BLE";
  else if(i == RV_BGT) return (uint64_t*)"RV_BGT";
  else if(i == RV_BGE) return (uint64_t*)"RV_BGE";
  else if(i == RV_BNE) return (uint64_t*)"RV_BNE";
  else if(i == RV_JMP) return (uint64_t*)"RV_JMP";
  else return (uint64_t*) "unexpected instruction";
}

uint64_t* make_const(uint64_t rd, uint64_t i){
  return triple((uint64_t*)RV_CONST, (uint64_t*)rd, (uint64_t*)i);
}
uint64_t* make_add(uint64_t rd, uint64_t rs1, uint64_t rs2){
  return quadruple((uint64_t*)RV_ADD, (uint64_t*)rd, (uint64_t*)rs1, (uint64_t*)rs2);
}
uint64_t* make_mul(uint64_t rd, uint64_t rs1, uint64_t rs2){
  return quadruple((uint64_t*)RV_MUL, (uint64_t*)rd, (uint64_t*)rs1, (uint64_t*)rs2);
}
uint64_t* make_sub(uint64_t rd, uint64_t rs1, uint64_t rs2){
  return quadruple((uint64_t*)RV_SUB, (uint64_t*)rd, (uint64_t*)rs1, (uint64_t*)rs2);
}
uint64_t* make_load(uint64_t rd, uint64_t rs, uint64_t i){
  return quadruple((uint64_t*)RV_LOAD, (uint64_t*)rd, (uint64_t*)rs, (uint64_t*)i);
}
uint64_t* make_store(uint64_t rd, uint64_t i, uint64_t rs){
  return quadruple((uint64_t*)RV_STORE, (uint64_t*)rd, (uint64_t*)i, (uint64_t*)rs);
}
uint64_t* make_label(uint64_t i){
  return pair((uint64_t*)RV_LABEL, (uint64_t*)i);
}
uint64_t* make_move(uint64_t rd, uint64_t rs){
  return triple((uint64_t*)RV_MOVE, (uint64_t*)rd, (uint64_t*)rs);
}

uint64_t* make_branch(uint64_t cmp, uint64_t rs1, uint64_t rs2, uint64_t lab){
  return quadruple((uint64_t*)cmp, (uint64_t*)rs1, (uint64_t*)rs2, (uint64_t*)lab);
}

uint64_t* make_beq(uint64_t rs1, uint64_t rs2, uint64_t lab){
  return make_branch(RV_BEQ, rs1, rs2, lab);
}
uint64_t* make_blt(uint64_t rs1, uint64_t rs2, uint64_t lab){
  return make_branch(RV_BLT, rs1, rs2, lab);
}
uint64_t* make_ble(uint64_t rs1, uint64_t rs2, uint64_t lab){
  return make_branch(RV_BLE, rs1, rs2, lab);
}
uint64_t* make_bgt(uint64_t rs1, uint64_t rs2, uint64_t lab){
  return make_branch(RV_BGT, rs1, rs2, lab);
}
uint64_t* make_bge(uint64_t rs1, uint64_t rs2, uint64_t lab){
  return make_branch(RV_BGE, rs1, rs2, lab);
}
uint64_t* make_bne(uint64_t rs1, uint64_t rs2, uint64_t lab){
  return make_branch(RV_BNE, rs1, rs2, lab);
}
uint64_t* make_jmp(uint64_t lab){
  return pair((uint64_t*)RV_JMP, (uint64_t*)lab);
}

void print_reg(uint64_t r){
  if(r == REG_ZERO) print((uint64_t*)"zero");
  else if(r == REG_RET) print((uint64_t*)"ret");
  else if(r == REG_SP) print((uint64_t*)"sp");
  else printf1((uint64_t*)"r%d", (uint64_t*)r);
}

void show_riscv_instr(uint64_t* i){
  uint64_t op = (uint64_t)fst(i);

  if(op == RV_CONST) {
    print_reg((uint64_t)snd(i));
    printf1((uint64_t*)" <- %d\n", thr(i));
  }
  else if(op == RV_ADD) {
    print_reg((uint64_t)snd(i));
    print((uint64_t*)" <- add(");
    print_reg((uint64_t)thr(i));
    print((uint64_t*)",");
    print_reg((uint64_t)frth(i));
    print((uint64_t*)")\n");
  }
  else if(op == RV_SUB) {
    print_reg((uint64_t)snd(i));
    print((uint64_t*)" <- sub(");
    print_reg((uint64_t)thr(i));
    print((uint64_t*)",");
    print_reg((uint64_t)frth(i));
    print((uint64_t*)")\n");
  }
  else if(op == RV_MUL) {
    print_reg((uint64_t)snd(i));
    print((uint64_t*)" <- mul(");
    print_reg((uint64_t)thr(i));
    print((uint64_t*)",");
    print_reg((uint64_t)frth(i));
    print((uint64_t*)")\n");
  }
  else if(op == RV_LOAD) {
    print_reg((uint64_t)snd(i));
    print((uint64_t*)" <- *(");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)" + %d)\n", frth(i));
  }
  else if(op == RV_STORE) {
    print((uint64_t*)"*(");
    print_reg((uint64_t)snd(i));
    printf1((uint64_t*)" + %d) <- ", thr(i));
    print_reg((uint64_t)frth(i));
    print((uint64_t*)"\n");
  }
  else if(op == RV_LABEL) {
    printf1((uint64_t*)"L%d:\n", snd(i));
  }
  else if(op == RV_MOVE) {
    print_reg((uint64_t)snd(i));
    print((uint64_t*)" <- ");
    print_reg((uint64_t)thr(i));
    print((uint64_t*)"\n");
  }
  else if(op == RV_BEQ) {
    print((uint64_t*)"beq ");
    print_reg((uint64_t)snd(i));
    print((uint64_t*)", ");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)", L%d\n", frth(i));
  }
  else if(op == RV_BLT) {
    print((uint64_t*)"blt ");
    print_reg((uint64_t)snd(i));
    print((uint64_t*)", ");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)", L%d\n", frth(i));
  }
  else if(op == RV_BLE) {
    print((uint64_t*)"ble ");
    print_reg((uint64_t)snd(i));
    print((uint64_t*)", ");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)", L%d\n", frth(i));
  }
  else if(op == RV_BGT) {
    print((uint64_t*)"bgt ");
    print_reg((uint64_t)snd(i));
    print((uint64_t*)", ");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)", L%d\n", frth(i));
  }
  else if(op == RV_BGE) {
    print((uint64_t*)"bge ");
    print_reg((uint64_t)snd(i));
    print((uint64_t*)", ");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)", L%d\n", frth(i));
  }
  else if(op == RV_BNE) {
    print((uint64_t*)"bne ");
    print_reg((uint64_t)snd(i));
    print((uint64_t*)", ");
    print_reg((uint64_t)thr(i));
    printf1((uint64_t*)", L%d\n", frth(i));
  }
  else if(op == RV_JMP) {
    printf1((uint64_t*)"jmp L%d\n", snd(i));
  }
  else {
    print((uint64_t*)"unrecognized instruction\n");
  }
}

void show_riscv_prog(uint64_t* p){
  while(!is_empty(p)){
    show_riscv_instr(get_elt(p));
    p = next_elt(p);
  }
}
