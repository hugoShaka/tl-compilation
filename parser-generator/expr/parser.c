#include "library.h"
#include "globals.h"
#include "lexer.h"
#include "preprocessor.h"
#include "expr_parser.h"
#include "expr_dump.h"
#include "expr_eval.h"

// Global constants defined locally;

uint64_t SYM_EOF          = -1; // end of file
uint64_t SYM_IDENTIFIER   = 0;  // identifier
uint64_t SYM_INTEGER      = 1;  // integer
uint64_t SYM_VOID         = 2;  // void
uint64_t SYM_UINT64       = 3;  // uint64_t
uint64_t SYM_SEMICOLON    = 4;  // ;
uint64_t SYM_IF           = 5;  // if
uint64_t SYM_ELSE         = 6;  // else
uint64_t SYM_PLUS         = 7;  // +
uint64_t SYM_MINUS        = 8;  // -
uint64_t SYM_ASTERISK     = 9;  // *
uint64_t SYM_DIV          = 10; // /
uint64_t SYM_EQUALITY     = 11; // ==
uint64_t SYM_ASSIGN       = 12; // =
uint64_t SYM_LPARENTHESIS = 13; // (
uint64_t SYM_RPARENTHESIS = 14; // )
uint64_t SYM_LBRACE       = 15; // {
uint64_t SYM_RBRACE       = 16; // }
uint64_t SYM_WHILE        = 17; // while
uint64_t SYM_RETURN       = 18; // return
uint64_t SYM_COMMA        = 19; // ,
uint64_t SYM_LT           = 20; // <
uint64_t SYM_LEQ          = 21; // <=
uint64_t SYM_GT           = 22; // >
uint64_t SYM_GEQ          = 23; // >=
uint64_t SYM_NOTEQ        = 24; // !=
uint64_t SYM_MOD          = 25; // %
uint64_t SYM_CHARACTER    = 26; // character
uint64_t SYM_STRING       = 27; // string
uint64_t SYM_EXTERN = 28; // global variable declaration
uint64_t SYM_INCLUDE = 29; // #include preprocessor directive

uint64_t* SYMBOLS = (uint64_t *) 0;



uint64_t allocated_memory = 0; // number of bytes for global variables and strings

uint64_t number_of_calls       = 0;
uint64_t number_of_assignments = 0;
uint64_t number_of_while       = 0;
uint64_t number_of_if          = 0;
uint64_t number_of_return      = 0;

uint64_t return_branches = 0; // fixup chain for return statements

uint64_t return_type = 0; // return type of currently parsed procedure

// Functions defined locally

void     compile_cstar();

// ------------------------- INITIALIZATION ------------------------

void reset_parser() {
  number_of_calls       = 0;
  number_of_assignments = 0;
  number_of_while       = 0;
  number_of_if          = 0;
  number_of_return      = 0;

  get_symbol();
}


// -----------------------------------------------------------------
// ---------------------------- PARSER -----------------------------
// -----------------------------------------------------------------


void syntax_error_message(uint64_t* message) {
  print_line_number((uint64_t*) "syntax error", line_number);
  printf1((uint64_t*) "%s\n", message);
}

uint64_t* eat(uint64_t token){
  uint64_t* res;
  res = string_of_symbol(token);
  if (symbol == token){
    get_symbol();
    return res;
  } else {
    syntax_error_message((uint64_t*) "unexpected token");
    printf2((uint64_t*)"Expected '%s' but got '%s' instead.\n",
            string_of_token(token), string_of_symbol(symbol));
    exit(1);
    return NULL;
  }
}

void compile_cstar() {
  uint64_t* ast;

  while(source_fd != -1){
    if(debug_preprocessor)
      printf1((uint64_t *) "Source file descriptor: %d\n", (uint64_t *) source_fd);

    ast = parse_S();
    print((uint64_t*) "Parsed expression :\n");
    dump_ast(ast);
    printf1((uint64_t*) "Result = %d.\n", (uint64_t*) eval_ast(ast));

    pop_source_file();
    // If there are still files to process with partially restart the scanner and parser.
    if(source_fd != -1){
      get_character();
      get_symbol();
    }
  }
}
