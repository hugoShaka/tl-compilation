#include "string.h"
#include "library.h"
#include "globals.h"
#include "arguments.h"
#include "parser.h"



// ------------------------ GLOBAL CONSTANTS -----------------------

uint64_t CHAR_SPACE        = ' ';
uint64_t CHAR_SEMICOLON    = ';';
uint64_t CHAR_PLUS         = '+';
uint64_t CHAR_DASH         = '-';
uint64_t CHAR_ASTERISK     = '*';
uint64_t CHAR_SLASH        = '/';
uint64_t CHAR_UNDERSCORE   = '_';
uint64_t CHAR_EQUAL        = '=';
uint64_t CHAR_LPARENTHESIS = '(';
uint64_t CHAR_RPARENTHESIS = ')';
uint64_t CHAR_LBRACE       = '{';
uint64_t CHAR_RBRACE       = '}';
uint64_t CHAR_COMMA        = ',';
uint64_t CHAR_LT           = '<';
uint64_t CHAR_GT           = '>';
uint64_t CHAR_EXCLAMATION  = '!';
uint64_t CHAR_PERCENTAGE   = '%';
uint64_t CHAR_BACKSLASH    =  92; // ASCII code 92 = backslash
uint64_t CHAR_HASH = '#';


// ------------------------ GLOBAL VARIABLES -----------------------

uint64_t line_number = 1; // current line number for error reporting

uint64_t* identifier = (uint64_t*) 0; // stores scanned identifier as string
uint64_t* integer    = (uint64_t*) 0; // stores scanned integer as string
uint64_t* string     = (uint64_t*) 0; // stores scanned string

uint64_t MAX_IDENTIFIER_LENGTH = 64;  // maximum number of characters in an identifier
uint64_t MAX_INTEGER_LENGTH    = 20;  // maximum number of characters in an unsigned integer
uint64_t MAX_STRING_LENGTH     = 128; // maximum number of characters in a string

uint64_t literal = 0; // stores numerical value of scanned integer or character

uint64_t integer_is_signed = 0; // enforce INT64_MIN limit if '-' was scanned before

uint64_t character; // most recently read character

uint64_t number_of_read_characters = 0;

uint64_t symbol; // most recently recognized symbol

uint64_t number_of_ignored_characters = 0;
uint64_t number_of_comments           = 0;
uint64_t number_of_scanned_symbols    = 0;


void get_character();

void reset_scanner() {
  line_number = 1;

  number_of_read_characters = 0;

  get_character();

  number_of_ignored_characters = 0;
  number_of_comments           = 0;
  number_of_scanned_symbols    = 0;
}


void init_scanner () {
  SYMBOLS = smalloc((SYM_INCLUDE+ 1) * SIZEOFUINT64STAR);

  *(SYMBOLS + SYM_IDENTIFIER)   = (uint64_t) "identifier";
  *(SYMBOLS + SYM_INTEGER)      = (uint64_t) "integer";
  *(SYMBOLS + SYM_VOID)         = (uint64_t) "void";
  *(SYMBOLS + SYM_UINT64)       = (uint64_t) "uint64_t";
  *(SYMBOLS + SYM_SEMICOLON)    = (uint64_t) ";";
  *(SYMBOLS + SYM_IF)           = (uint64_t) "if";
  *(SYMBOLS + SYM_ELSE)         = (uint64_t) "else";
  *(SYMBOLS + SYM_PLUS)         = (uint64_t) "+";
  *(SYMBOLS + SYM_MINUS)        = (uint64_t) "-";
  *(SYMBOLS + SYM_ASTERISK)     = (uint64_t) "*";
  *(SYMBOLS + SYM_DIV)          = (uint64_t) "/";
  *(SYMBOLS + SYM_EQUALITY)     = (uint64_t) "==";
  *(SYMBOLS + SYM_ASSIGN)       = (uint64_t) "=";
  *(SYMBOLS + SYM_LPARENTHESIS) = (uint64_t) "(";
  *(SYMBOLS + SYM_RPARENTHESIS) = (uint64_t) ")";
  *(SYMBOLS + SYM_LBRACE)       = (uint64_t) "{";
  *(SYMBOLS + SYM_RBRACE)       = (uint64_t) "}";
  *(SYMBOLS + SYM_WHILE)        = (uint64_t) "while";
  *(SYMBOLS + SYM_RETURN)       = (uint64_t) "return";
  *(SYMBOLS + SYM_COMMA)        = (uint64_t) ",";
  *(SYMBOLS + SYM_LT)           = (uint64_t) "<";
  *(SYMBOLS + SYM_LEQ)          = (uint64_t) "<=";
  *(SYMBOLS + SYM_GT)           = (uint64_t) ">";
  *(SYMBOLS + SYM_GEQ)          = (uint64_t) ">=";
  *(SYMBOLS + SYM_NOTEQ)        = (uint64_t) "!=";
  *(SYMBOLS + SYM_MOD)          = (uint64_t) "%";
  *(SYMBOLS + SYM_CHARACTER)    = (uint64_t) "character";
  *(SYMBOLS + SYM_STRING)       = (uint64_t) "string";
  *(SYMBOLS + SYM_EXTERN) = (uint64_t) "extern";
  *(SYMBOLS + SYM_INCLUDE) = (uint64_t) "include";

  character = CHAR_EOF;
  symbol    = SYM_EOF;
}

void print_symbol(uint64_t symbol) {
  if (symbol == SYM_EOF)
    printf1((uint64_t*) "%s\n", (uint64_t*) "end of file");
  else if (symbol == SYM_IDENTIFIER)
    printf1((uint64_t*) "Identifier: %s\n", (uint64_t*) identifier);
  else if (symbol == SYM_STRING)
    printf1((uint64_t*) "String: \"%s\"\n", (uint64_t*) string);
  else if (symbol == SYM_INTEGER )
    printf1((uint64_t*) "Integer: %d\n", (uint64_t*)literal);
  else if (symbol == SYM_INCLUDE )
    printf1((uint64_t*) "#%s\n", (uint64_t*) *(SYMBOLS + symbol));
  else
    printf1((uint64_t*) "%s\n", (uint64_t*) *(SYMBOLS + symbol));
}

void print_line_number(uint64_t* message, uint64_t line) {
  printf4((uint64_t*) "%s: %s in %s in line %d: ", get_myname(), message, source_name, (uint64_t*) line);
}

void syntax_error_character(uint64_t expected) {
  print_line_number((uint64_t*) "syntax error", line_number);
  print_character(expected);
  print((uint64_t*) " expected but ");
  print_character(character);
  print((uint64_t*) " found\n");
}



uint64_t is_character_new_line() {
  if (character == CHAR_LF)
    return 1;
  else if (character == CHAR_CR)
    return 1;
  else
    return 0;
}

uint64_t is_character_whitespace() {
  if (character == CHAR_SPACE)
    return 1;
  else if (character == CHAR_TAB)
    return 1;
  else
    return is_character_new_line();
}


void get_character() {
  uint64_t number_of_read_bytes;

  // assert: character_buffer is mapped

  // try to read 1 character into character_buffer
  // from file with source_fd file descriptor
  number_of_read_bytes = read(source_fd, character_buffer, 1);

  if (number_of_read_bytes == 1) {
    // store the read character in the global variable called character
    character = *character_buffer;

    number_of_read_characters = number_of_read_characters + 1;
  } else if (number_of_read_bytes == 0)
    // reached end of file
    character = CHAR_EOF;
  else {
    printf2((uint64_t*) "%s: could not read character from input file %s\n", get_myname(), source_name);

    exit(EXITCODE_IOERROR);
  }
}


uint64_t find_next_character() {
  uint64_t in_single_line_comment;
  uint64_t in_multi_line_comment;

  // assuming we are not in a comment
  in_single_line_comment = 0;
  in_multi_line_comment  = 0;

  // read and discard all whitespace and comments until a character is found
  // that is not whitespace and does not occur in a comment, or the file ends
  while (1) {
    if (in_single_line_comment) {
      get_character();

      if (is_character_new_line())
        // single-line comments end with new line
        in_single_line_comment = 0;
      else if (character == CHAR_EOF)
        // or end of file
        return character;
      else
        // count the characters in comments as ignored characters
        number_of_ignored_characters = number_of_ignored_characters + 1;

    } else if (in_multi_line_comment) {
      get_character();

      if (character == CHAR_ASTERISK) {
        // look for '*/' and here count '*' as ignored character
        number_of_ignored_characters = number_of_ignored_characters + 1;

        get_character();

        if (character == CHAR_SLASH) {
          // multi-line comments end with "*/"
          in_multi_line_comment = 0;

          get_character();
        }
      }


      if (in_multi_line_comment) {
        // keep track of line numbers for error reporting and code annotation
        if (character == CHAR_LF)
          // only linefeeds count, not carriage returns
          line_number = line_number + 1;
        else if (character == CHAR_EOF) {
          // multi-line comment is not terminated
          syntax_error_message((uint64_t*) "runaway multi-line comment");

          exit(EXITCODE_SCANNERERROR);
        }
      }

      // count the characters in comments as ignored characters including '/' in '*/'
      number_of_ignored_characters = number_of_ignored_characters + 1;

    } else if (is_character_whitespace()) {
      if (character == CHAR_LF)
        line_number = line_number + 1;

      // also count line feed and carriage return as ignored characters
      number_of_ignored_characters = number_of_ignored_characters + 1;

      get_character();

    } else if (character == CHAR_SLASH) {
      get_character();

      if (character == CHAR_SLASH) {
        // "//" begins a comment
        in_single_line_comment = 1;

        // count both slashes as ignored characters
        number_of_ignored_characters = number_of_ignored_characters + 2;

        number_of_comments = number_of_comments + 1;
      } else if (character == CHAR_ASTERISK) {
        // "/*" begins a multi-line comment
        in_multi_line_comment = 1;

        // count both slash and asterisk as ignored characters
        number_of_ignored_characters = number_of_ignored_characters + 2;

        number_of_comments = number_of_comments + 1;
      } else {
        // while looking for "//" and "/*" we actually found '/'
        symbol = SYM_DIV;

        return character;
      }

    } else
      // character found that is not whitespace and not occurring in a comment
      return character;
  }
}

uint64_t is_character_letter() {
  // ASCII codes for lower- and uppercase letters are in contiguous intervals
  if (character >= 'a')
    if (character <= 'z')
      return 1;
    else
      return 0;
  else if (character >= 'A')
    if (character <= 'Z')
      return 1;
    else
      return 0;
  else
    return 0;
}

uint64_t is_character_digit() {
  // ASCII codes for digits are in a contiguous interval
  if (character >= '0')
    if (character <= '9')
      return 1;
    else
      return 0;
  else
    return 0;
}

uint64_t is_character_letter_or_digit_or_underscore() {
  if (is_character_letter())
    return 1;
  else if (is_character_digit())
    return 1;
  else if (character == CHAR_UNDERSCORE)
    return 1;
  else
    return 0;
}

uint64_t is_character_not_double_quote_or_new_line_or_eof() {
  if (character == CHAR_DOUBLEQUOTE)
    return 0;
  else if (is_character_new_line())
    return 0;
  else if (character == CHAR_EOF)
    return 0;
  else
    return 1;
}

uint64_t identifier_string_match(uint64_t keyword) {
  return string_compare(identifier, (uint64_t*) *(SYMBOLS + keyword));
}

uint64_t preprocessor_directive(){
  if (identifier_string_match(SYM_INCLUDE))
    return SYM_INCLUDE;
  else{
    printf1((uint64_t *) "Expecting valid preprocessor directive. Found: #%s\n", identifier);
    exit(EXITCODE_SCANNERERROR);
  }

  return SYM_EOF;
}

uint64_t identifier_or_keyword() {
  if (identifier_string_match(SYM_WHILE))
    return SYM_WHILE;
  if (identifier_string_match(SYM_IF))
    return SYM_IF;
  if (identifier_string_match(SYM_UINT64))
    return SYM_UINT64;
  if (identifier_string_match(SYM_ELSE))
    return SYM_ELSE;
  if (identifier_string_match(SYM_RETURN))
    return SYM_RETURN;
  if (identifier_string_match(SYM_VOID))
    return SYM_VOID;
  if (identifier_string_match(SYM_EXTERN))
    return SYM_EXTERN;
  else
    return SYM_IDENTIFIER;
}



void handle_escape_sequence() {
  // ignoring the backslash
  number_of_ignored_characters = number_of_ignored_characters + 1;

  get_character();

  if (character == 'n')
    character = CHAR_LF;
  else if (character == 't')
    character = CHAR_TAB;
  else if (character == 'b')
    character = CHAR_BACKSPACE;
  else if (character == CHAR_SINGLEQUOTE)
    character = CHAR_SINGLEQUOTE;
  else if (character == CHAR_DOUBLEQUOTE)
    character = CHAR_DOUBLEQUOTE;
  else if (character == CHAR_PERCENTAGE)
    character = CHAR_PERCENTAGE;
  else if (character == CHAR_BACKSLASH)
    character = CHAR_BACKSLASH;
  else {
    syntax_error_message((uint64_t*) "unknown escape sequence found");

    exit(EXITCODE_SCANNERERROR);
  }
}


void get_symbol() {
  // reset previously scanned symbol
  symbol = SYM_EOF;

  if (find_next_character() != CHAR_EOF) {
    // Here comes the code of the lexer automata
    if (character == CHAR_PLUS){
      symbol = SYM_PLUS;
      get_character();
    }
    else if (character == CHAR_SEMICOLON){
      symbol = SYM_SEMICOLON;
      get_character();
    }
    else if (character == CHAR_DASH){
      symbol = SYM_MINUS;
      get_character();
    }
    else if (character == CHAR_ASTERISK){
      symbol = SYM_ASTERISK;
      get_character();
    }
    else if (character == CHAR_EQUAL){
      symbol = SYM_ASSIGN;
      get_character();
      if (character == CHAR_EQUAL){
        symbol = SYM_EQUALITY
        get_character();
      }
    }
    else if (character == CHAR_LPARENTHESIS){
      symbol = SYM_LPARENTHESIS;
      get_character();
    }
    else if (character == CHAR_RPARENTHESIS){
      symbol = SYM_RPARENTHESIS;
      get_character();
    }
    else if (character == CHAR_LBRACE){
      symbol = SYM_LBRACE;
      get_character();
    }
    else if (character == CHAR_RBRACE){
      symbol = SYM_RBRACE;
      get_character();
    }
    else if (character == CHAR_COMMA){
      symbol = SYM_COMMA;
      get_character();
    }
    else if (character == CHAR_LT){
      symbol = SYM_LT;
      get_character();
      if (character == CHAR_EQUAL){
        symbol = SYM_LEQ
        get_character();
      }
    }
    else if (character == CHAR_GT){
      symbol = SYM_GT;
      get_character();
      if (character == CHAR_EQUAL){
        symbol = SYM_GEQ
        get_character();
      }
    }
    else if (character == CHAR_EXCLAMATION){
      get_character();
      if (character == CHAR_EQUAL){
        symbol = SYM_NOTEQ
        get_character();
      }
      else {
        syntax_error_character(character);
      }

    }

    else if (character == CHAR_PERCENTAGE){
      symbol = SYM_MOD;
      get_character();
    }

    number_of_scanned_symbols = number_of_scanned_symbols + 1;
  }
  else {
    syntax_error_character(character)
  }
}

