%{
    
    %}

%token EOF EOL TOK NT RULES ARROW
%token<string> IDENTIFIER
%token<string> CODE

%start main
%type <string list * string list * (string * string list * string) list> main

%%

  main:
    | TOK list_ident EOL main { let (toks,nts,rules) = $4 in (toks @ $2, nts, rules) }
      | NT list_ident EOL main { let (toks,nts,rules) = $4 in (toks, nts @ $2, rules) }
      | RULES EOL rules EOF { ([],[],$3) }
    
    ;

      list_ident:
        | IDENTIFIER list_ident { $1 :: $2}
        | { [] }
    ;

      rules:
        | rule rules { $1 :: $2 }
        | {[]}
    ;

      rule:
        | IDENTIFIER ARROW list_ident EOL { ($1,$3, "return NULL;") }
        | IDENTIFIER ARROW list_ident EOL? CODE EOL { ($1,$3, $5) }
;
%%
