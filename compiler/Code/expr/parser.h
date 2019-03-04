extern uint64_t SYM_EOF; // end of file
extern uint64_t SYM_IDENTIFIER;  // identifier
extern uint64_t SYM_INTEGER;  // integer
extern uint64_t SYM_VOID;  // void
extern uint64_t SYM_UINT64;  // uint64_t
extern uint64_t SYM_SEMICOLON;  // ;
extern uint64_t SYM_IF;  // if
extern uint64_t SYM_ELSE;  // else
extern uint64_t SYM_PLUS;  // +
extern uint64_t SYM_MINUS;  // -
extern uint64_t SYM_ASTERISK;  // *
extern uint64_t SYM_DIV; // /
extern uint64_t SYM_EQUALITY; // ==
extern uint64_t SYM_ASSIGN; // =
extern uint64_t SYM_LPARENTHESIS; // (
extern uint64_t SYM_RPARENTHESIS; // )
extern uint64_t SYM_LBRACE; // {
extern uint64_t SYM_RBRACE; // }
extern uint64_t SYM_WHILE; // while
extern uint64_t SYM_RETURN; // return
extern uint64_t SYM_COMMA; // ,
extern uint64_t SYM_LT; // <
extern uint64_t SYM_LEQ; // <=
extern uint64_t SYM_GT; // >
extern uint64_t SYM_GEQ; // >=
extern uint64_t SYM_NOTEQ; // !=
extern uint64_t SYM_MOD; // %
extern uint64_t SYM_CHARACTER; // character
extern uint64_t SYM_STRING; // string
extern uint64_t SYM_EXTERN; // global variable declaration
extern uint64_t SYM_INCLUDE;

extern uint64_t* SYMBOLS;


// Functions defined locally

extern void reset_parser();

extern void compile_cstar();
extern void syntax_error_message(uint64_t* message);

extern uint64_t* eat(uint64_t tok);
