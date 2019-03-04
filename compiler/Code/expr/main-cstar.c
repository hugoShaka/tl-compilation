#include "library.h"
#include "arguments.h"
#include "lexer.h"
#include "parser.h"
#include "compiler.h"
#include "ast.h"
#include "globals.h"
#include "dump_ast.h"
#include "expr_eval.h"
#include "genriscv.h"
#include "riscv.h"
#include "eval_riscv.h"
#include "expr_dump.h"

// -----------------------------------------------------------------
// ----------------------------- MAIN ------------------------------
// -----------------------------------------------------------------

// ------------------------- INITIALIZATION ------------------------


void print_cstar_usage() {
  printf1((uint64_t*) "%s: usage: cstar -c { source } [-show-ast file.dot] [-dump-ast] [-gen-riscv] [-dump-riscv] [-eval-riscv] \n",
    get_myname());
}


uint64_t cstar() {
  uint64_t* option;
  global_ast = nil();
  global_rv = NULL;
  debug_riscv = 0;

  if (number_of_remaining_arguments() == 0)
    print_cstar_usage();
  else {
    init_scanner();

    while (number_of_remaining_arguments() > 0) {
      option = get_argument();

      if (string_compare(option, (uint64_t*) "-c"))
        selfie_compile();
      else if (string_compare(option, (uint64_t*) "-show-ast")){
        uint64_t* dump_file = get_argument();
        output_fd = open_write_only(dump_file);
        dump_tree(global_ast);
        output_fd = 1;
       }
      else if (string_compare(option, (uint64_t*) "-dump-ast")){
        dump_ast(global_ast);
      }
      else if (string_compare(option, (uint64_t*) "-eval-ast")){
        printf1((uint64_t*) "Result = %d.\n", (uint64_t*) eval_ast(global_ast));
      }
      else if (string_compare(option, (uint64_t*) "-gen-riscv")){
        global_rv = gen_riscv_prog(global_ast);
      }
      else if (string_compare(option, (uint64_t*) "-dump-riscv")){
        if(!global_rv){
          global_rv = gen_riscv_prog(global_ast);
        }
        show_riscv_prog(global_rv);
      }
      else if (string_compare(option, (uint64_t*) "-debug-riscv")){
        debug_riscv = 1;
      }
      else if (string_compare(option, (uint64_t*) "-eval-riscv")){
        if(!global_rv){
          global_rv = gen_riscv_prog(global_ast);
        }
        printf1((uint64_t*) "Result = %d.\n", (uint64_t*) eval_riscv_prog(global_rv));
      }


      else if (number_of_remaining_arguments() == 0) {
        // remaining options have at least one argument
        print_cstar_usage();

        return EXITCODE_BADARGUMENTS;
      }
      else {
        print_cstar_usage();

        return EXITCODE_BADARGUMENTS;
      }
    }
  }

  return EXITCODE_NOERROR;
}

uint64_t main(uint64_t argc, uint64_t* argv) {
  init_arguments((uint64_t) argc, (uint64_t*) argv);

  init_library();

  return cstar();
}
