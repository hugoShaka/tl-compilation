
extern uint64_t REG_ZERO ;
extern uint64_t REG_RET  ;
extern uint64_t REG_SP   ;


extern uint64_t RV_CONST;
extern uint64_t RV_ADD;
extern uint64_t RV_SUB;
extern uint64_t RV_MUL;
extern uint64_t RV_LOAD;
extern uint64_t RV_STORE;
extern uint64_t RV_LABEL;
extern uint64_t RV_MOVE;
extern uint64_t RV_BEQ;
extern uint64_t RV_BLT;
extern uint64_t RV_BLE;
extern uint64_t RV_BGT;
extern uint64_t RV_BGE;
extern uint64_t RV_BNE;
extern uint64_t RV_JMP;

uint64_t* string_of_instr(uint64_t i);

uint64_t* make_const(uint64_t rd, uint64_t i);
uint64_t* make_add(uint64_t rd, uint64_t rs1, uint64_t rs2);
uint64_t* make_mul(uint64_t rd, uint64_t rs1, uint64_t rs2);
uint64_t* make_sub(uint64_t rd, uint64_t rs1, uint64_t rs2);
uint64_t* make_load(uint64_t rd, uint64_t rs, uint64_t i);
uint64_t* make_store(uint64_t rd, uint64_t i, uint64_t rs);
uint64_t* make_label(uint64_t i);
uint64_t* make_move(uint64_t rd, uint64_t rs);

uint64_t* make_branch(uint64_t cmp, uint64_t rs1, uint64_t rs2, uint64_t lab);

uint64_t* make_beq(uint64_t rs1, uint64_t rs2, uint64_t lab);
uint64_t* make_blt(uint64_t rs1, uint64_t rs2, uint64_t lab);
uint64_t* make_ble(uint64_t rs1, uint64_t rs2, uint64_t lab);
uint64_t* make_bgt(uint64_t rs1, uint64_t rs2, uint64_t lab);
uint64_t* make_bge(uint64_t rs1, uint64_t rs2, uint64_t lab);
uint64_t* make_bne(uint64_t rs1, uint64_t rs2, uint64_t lab);
uint64_t* make_jmp(uint64_t lab);

void print_reg(uint64_t r);
void show_riscv_instr(uint64_t* i);
void show_riscv_prog(uint64_t* p);
