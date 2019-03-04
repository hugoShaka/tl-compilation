#include "expr_parser.h"
#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
uint64_t* parse_S(){
  uint64_t* p;
  if(symbol ==  SYM_IDENTIFIER){
    p = smalloc(4 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_ASSIGNS();
    *(p + 1) = (uint64_t) eat(SYM_RETURN);
    *(p + 2) = (uint64_t) parse_EXPR();
    *(p + 3) = (uint64_t) eat(SYM_EOF);

     return pair((array_get(p,1 - 1)), (array_get(p,3 - 1))); 
  }
  if(symbol ==  SYM_RETURN){
    p = smalloc(4 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_ASSIGNS();
    *(p + 1) = (uint64_t) eat(SYM_RETURN);
    *(p + 2) = (uint64_t) parse_EXPR();
    *(p + 3) = (uint64_t) eat(SYM_EOF);

     return pair((array_get(p,1 - 1)), (array_get(p,3 - 1))); 
  }
  syntax_error_message((uint64_t*) "error while parsing S");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_IDENTIFIER));
printf1((uint64_t*)", %s", string_of_token(SYM_RETURN));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_ASSIGNS(){
  uint64_t* p;
  if(symbol ==  SYM_IDENTIFIER){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_ASSIGN();
    *(p + 1) = (uint64_t) parse_ASSIGNS();

    return cons((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  if(symbol ==  SYM_RETURN){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  syntax_error_message((uint64_t*) "error while parsing ASSIGNS");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_IDENTIFIER));
printf1((uint64_t*)", %s", string_of_token(SYM_RETURN));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_ASSIGN(){
  uint64_t* p;
  if(symbol ==  SYM_IDENTIFIER){
    p = smalloc(4 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_IDENTIFIER);
    *(p + 1) = (uint64_t) eat(SYM_ASSIGN);
    *(p + 2) = (uint64_t) parse_EXPR();
    *(p + 3) = (uint64_t) eat(SYM_SEMICOLON);

    return pair(make_string((array_get(p,1 - 1))),(array_get(p,3 - 1)));
  }
  syntax_error_message((uint64_t*) "error while parsing ASSIGN");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_IDENTIFIER));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_EXPR(){
  uint64_t* p;
  if(symbol ==  SYM_IDENTIFIER){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_TERM();
    *(p + 1) = (uint64_t) parse_TERMS();

    return make_terms((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  if(symbol ==  SYM_INTEGER){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_TERM();
    *(p + 1) = (uint64_t) parse_TERMS();

    return make_terms((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  if(symbol ==  SYM_LPARENTHESIS){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_TERM();
    *(p + 1) = (uint64_t) parse_TERMS();

    return make_terms((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  syntax_error_message((uint64_t*) "error while parsing EXPR");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_IDENTIFIER));
printf1((uint64_t*)", %s", string_of_token(SYM_INTEGER));
printf1((uint64_t*)", %s", string_of_token(SYM_LPARENTHESIS));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_TERM(){
  uint64_t* p;
  if(symbol ==  SYM_IDENTIFIER){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_FACTOR();
    *(p + 1) = (uint64_t) parse_FACTORS();

    return make_factors((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  if(symbol ==  SYM_INTEGER){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_FACTOR();
    *(p + 1) = (uint64_t) parse_FACTORS();

    return make_factors((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  if(symbol ==  SYM_LPARENTHESIS){
    p = smalloc(2 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) parse_FACTOR();
    *(p + 1) = (uint64_t) parse_FACTORS();

    return make_factors((array_get(p,1 - 1)),(array_get(p,2 - 1)));
  }
  syntax_error_message((uint64_t*) "error while parsing TERM");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_IDENTIFIER));
printf1((uint64_t*)", %s", string_of_token(SYM_INTEGER));
printf1((uint64_t*)", %s", string_of_token(SYM_LPARENTHESIS));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_TERMS(){
  uint64_t* p;
  if(symbol ==  SYM_EOF){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  if(symbol ==  SYM_PLUS){
    p = smalloc(3 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_PLUS);
    *(p + 1) = (uint64_t) parse_TERM();
    *(p + 2) = (uint64_t) parse_TERMS();

    return cons(pair(SYM_PLUS,(array_get(p,2 - 1))),(array_get(p,3 - 1)));
  }
  if(symbol ==  SYM_MINUS){
    p = smalloc(3 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_MINUS);
    *(p + 1) = (uint64_t) parse_TERM();
    *(p + 2) = (uint64_t) parse_TERMS();

    return cons(pair(SYM_MINUS,(array_get(p,2 - 1))),(array_get(p,3 - 1)));
  }
  if(symbol ==  SYM_RPARENTHESIS){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  if(symbol ==  SYM_SEMICOLON){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  syntax_error_message((uint64_t*) "error while parsing TERMS");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_EOF));
printf1((uint64_t*)", %s", string_of_token(SYM_PLUS));
printf1((uint64_t*)", %s", string_of_token(SYM_MINUS));
printf1((uint64_t*)", %s", string_of_token(SYM_RPARENTHESIS));
printf1((uint64_t*)", %s", string_of_token(SYM_SEMICOLON));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_FACTOR(){
  uint64_t* p;
  if(symbol ==  SYM_IDENTIFIER){
    p = smalloc(1 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_IDENTIFIER);

    return pair(EVAR,(array_get(p,1 - 1)));
  }
  if(symbol ==  SYM_INTEGER){
    p = smalloc(1 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_INTEGER);

    return pair(make_int(EINT), make_int(atoi((array_get(p,1 - 1)))));
  }
  if(symbol ==  SYM_LPARENTHESIS){
    p = smalloc(3 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_LPARENTHESIS);
    *(p + 1) = (uint64_t) parse_EXPR();
    *(p + 2) = (uint64_t) eat(SYM_RPARENTHESIS);

    return (array_get(p,2 - 1));
  }
  syntax_error_message((uint64_t*) "error while parsing FACTOR");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_IDENTIFIER));
printf1((uint64_t*)", %s", string_of_token(SYM_INTEGER));
printf1((uint64_t*)", %s", string_of_token(SYM_LPARENTHESIS));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
uint64_t* parse_FACTORS(){
  uint64_t* p;
  if(symbol ==  SYM_EOF){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  if(symbol ==  SYM_PLUS){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  if(symbol ==  SYM_MINUS){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  if(symbol ==  SYM_ASTERISK){
    p = smalloc(3 * SIZEOFUINT64STAR);
    *(p + 0) = (uint64_t) eat(SYM_ASTERISK);
    *(p + 1) = (uint64_t) parse_FACTOR();
    *(p + 2) = (uint64_t) parse_FACTORS();

    return cons(pair(EMUL,(array_get(p,2 - 1))),(array_get(p,3 - 1)));
  }
  if(symbol ==  SYM_RPARENTHESIS){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  if(symbol ==  SYM_SEMICOLON){
    p = smalloc(0 * SIZEOFUINT64STAR);

    return nil();
  }
  syntax_error_message((uint64_t*) "error while parsing FACTORS");
  print((uint64_t*)"Expected one of ");
printf1((uint64_t*)"{ %s", string_of_token(SYM_EOF));
printf1((uint64_t*)", %s", string_of_token(SYM_PLUS));
printf1((uint64_t*)", %s", string_of_token(SYM_MINUS));
printf1((uint64_t*)", %s", string_of_token(SYM_ASTERISK));
printf1((uint64_t*)", %s", string_of_token(SYM_RPARENTHESIS));
printf1((uint64_t*)", %s", string_of_token(SYM_SEMICOLON));
print((uint64_t*)"}");
  printf1((uint64_t*)" but got '%s' instead.\n", string_of_symbol(symbol));
  exit(1);
  return NULL;
}
