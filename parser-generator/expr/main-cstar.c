#include "library.h"
#include "arguments.h"
#include "lexer.h"
#include "parser.h"
#include "compiler.h"

// -----------------------------------------------------------------
// ----------------------------- MAIN ------------------------------
// -----------------------------------------------------------------

// ------------------------- INITIALIZATION ------------------------


void print_cstar_usage() {
  printf2((uint64_t*) "%s: usage: cstar { %s } \n",
    get_myname(),
      (uint64_t*) "-c { source } ");
}

uint64_t cstar() {
  uint64_t* option;

  if (number_of_remaining_arguments() == 0)
    print_cstar_usage();
  else {
    init_scanner();

    while (number_of_remaining_arguments() > 0) {
      option = get_argument();

      if (string_compare(option, (uint64_t*) "-c"))
        selfie_compile();

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
