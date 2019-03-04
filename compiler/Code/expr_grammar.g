tokens SYM_EOF SYM_IDENTIFIER SYM_INTEGER SYM_PLUS SYM_MINUS SYM_ASTERISK SYM_LPARENTHESIS SYM_RPARENTHESIS SYM_ASSIGN SYM_SEMICOLON SYM_RETURN
non-terminals S ASSIGNS ASSIGN EXPR TERM TERMS FACTOR FACTORS
rules
S -> ASSIGNS SYM_RETURN EXPR SYM_EOF { return pair($1, $3); }
ASSIGNS -> ASSIGN ASSIGNS {return cons($1,$2);}
ASSIGNS -> {return nil();}
ASSIGN -> SYM_IDENTIFIER SYM_ASSIGN EXPR SYM_SEMICOLON {return pair(make_string($1),$3);}
EXPR -> TERM TERMS {return make_terms($1,$2);}
TERM -> FACTOR FACTORS {return make_factors($1,$2);}
TERMS -> SYM_PLUS TERM TERMS {return cons(pair(make_int(SYM_PLUS),$2),$3);}
TERMS -> SYM_MINUS TERM TERMS {return cons(pair(make_int(SYM_MINUS),$2),$3);}
TERMS -> {return nil();}
FACTOR -> SYM_INTEGER {return pair(make_int(EINT), make_int(atoi($1)));}
FACTOR -> SYM_IDENTIFIER {return pair(make_int(EVAR),make_string($1));}
FACTOR -> SYM_LPARENTHESIS EXPR SYM_RPARENTHESIS {return $2;}
FACTORS -> SYM_ASTERISK FACTOR FACTORS {return cons(pair(make_int(EMUL),$2),$3);}
FACTORS -> {return nil();}
