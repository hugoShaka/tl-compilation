
uint64_t* array_get(uint64_t* p, uint64_t i);
void array_set(uint64_t* p, uint64_t i, uint64_t* v);

uint64_t* pair(uint64_t* fst, uint64_t* snd);
uint64_t* triple(uint64_t* fst, uint64_t* snd, uint64_t* thr);
uint64_t* quadruple(uint64_t* fst, uint64_t* snd, uint64_t* thr, uint64_t* frth);
uint64_t* quintuple(uint64_t* fst, uint64_t* snd, uint64_t* thr, uint64_t* frth, uint64_t* fif);

uint64_t* fst(uint64_t* p);
uint64_t* snd(uint64_t* p);
uint64_t* thr(uint64_t* p);
uint64_t* frth(uint64_t* p);
uint64_t* fif(uint64_t* p);

uint64_t* cons(uint64_t* elt, uint64_t* l);
extern uint64_t* nil;

uint64_t* get_elt(uint64_t* l);
uint64_t* next_elt(uint64_t* l);

/* Expressions */
extern uint64_t EINT;
extern uint64_t EADD;
extern uint64_t ESUB;
extern uint64_t EMUL;
extern uint64_t EDIV;
extern uint64_t EMOD;
extern uint64_t EVAR;
extern uint64_t ENEG;

uint64_t* string_of_expr_tag(uint64_t et);

uint64_t* make_terms(uint64_t* term, uint64_t* other);
uint64_t* make_factors(uint64_t* factor, uint64_t* other);
