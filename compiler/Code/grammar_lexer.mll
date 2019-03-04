{
open Grammar_parser_yacc
}

let digit = ['0'-'9']
let letter = ['a'-'z' 'A'-'Z']
let id = letter (digit|letter|'_')*

rule token = parse
  | [' ' '\t'] { token lexbuf }
  | '\n' { EOL }
  | '{' { action 0 "" lexbuf }
  | "->" { ARROW }
  | "tokens" { TOK }
  | "non-terminals" { NT }
  | "rules" { RULES }
  | id as s { IDENTIFIER s }
  | eof { EOF }
  | _ as x { failwith (Printf.sprintf "unexpected char '%c'\n" x)}
and action level s = parse
  | '}' { if level = 0 then CODE s else action (level-1) (s ^ "}") lexbuf }
  | '{' { action (level + 1) (s ^ "{") lexbuf }
  | _ as x { action level (Printf.sprintf "%s%c" s x) lexbuf }
