#include "library.h"
#include "globals.h"
#include "arguments.h"
#include "lexer.h"
#include "parser.h"
#include "preprocessor.h"


// Functions defined locally

void selfie_compile() {
  uint64_t link;
  uint64_t number_of_source_files;

  // link until next console option
  link = 1;

  number_of_source_files = 0;

  while (link) {
    if (number_of_remaining_arguments() == 0)
      link = 0;
    else if (load_character(peek_argument(), 0) == '-')
      link = 0;
    else {
      source_name = get_argument();

      number_of_source_files = number_of_source_files + 1;

      /* printf2((uint64_t*) "//%s: selfie compiling %s with starc\n", get_myname(), source_name); */

      // assert: source_name is mapped and not longer than MAX_FILENAME_LENGTH

      push_source_file(source_name);

      if (signed_less_than(source_fd, 0)) {
        printf2((uint64_t*) "%s: could not open input file %s\n", get_myname(), source_name);

        exit(EXITCODE_IOERROR);
      }

      reset_scanner();
      reset_parser();

      compile_cstar();

      /* printf4((uint64_t*) "//%s: %d characters read in %d lines and %d comments\n", get_myname(), */
      /*   (uint64_t*) number_of_read_characters, */
      /*   (uint64_t*) line_number, */
      /*   (uint64_t*) number_of_comments); */

      /* printf4((uint64_t*) "//%s: with %d(%.2d%%) characters in %d actual symbols\n", get_myname(), */
      /*   (uint64_t*) (number_of_read_characters - number_of_ignored_characters), */
      /*   (uint64_t*) fixed_point_percentage(fixed_point_ratio(number_of_read_characters, number_of_read_characters - number_of_ignored_characters, 4), 4), */
      /*   (uint64_t*) number_of_scanned_symbols); */
    }
  }

  if (number_of_source_files == 0)
    printf1((uint64_t*) "%s: nothing to compile, only library generated\n", get_myname());

}
