open Grammar_parser
open Ll_parser
open Printing


let grammar_file = ref "expr_grammar.g"
let table_file = ref "table.html"
let parser_c_file = ref "expr_parser.c"
let parser_h_file = ref "expr_parser.h"
let parser_dir = ref "expr"

let int_of_lltype = function
  | First i
  | Follow i -> i

let nth_rule (toks,nts,rules) a =
  (List.nth rules (int_of_lltype a - 1))


let make_nt (table: string*string -> lltype list) (toks,nts,rules) oc n () =
  Printf.fprintf oc "uint64_t* parse_%s(){\n" n;
  Printf.fprintf oc "  uint64_t* p;\n";
  List.iter
    (fun t ->
       let rules = List.map (fun a -> nth_rule (toks,nts,rules) a) (table (n,t)) in
       match rules with
         [] -> ()
       | (_,pl,act)::_ ->
         Printf.fprintf oc "  if(symbol ==  %s){\n" t;
         Printf.fprintf oc "    p = smalloc(%d * SIZEOFUINT64STAR);\n" (List.length pl);
         List.iteri
           (fun i t ->
              if List.mem t toks
              then Printf.fprintf oc "    *(p + %d) = (uint64_t) eat(%s);\n" i t
              else Printf.fprintf oc "    *(p + %d) = (uint64_t) parse_%s();\n" i t)
           pl;
         Printf.fprintf oc "\n    %s\n  }\n" (resolve_vars act);
    )
    toks;
  let expected = List.filter (fun t -> List.length (table (n,t)) > 0) toks in
  Printf.fprintf oc "  syntax_error_message((uint64_t*) \"error while parsing %s\");\n" n;
  Printf.fprintf oc "  print((uint64_t*)\"Expected one of \");\n";
  begin
    match expected with
      [] -> Printf.fprintf oc "print((uint64_t*)\"{}\");\n"
    | a::r -> Printf.fprintf oc "printf1((uint64_t*)\"{ %%s\", string_of_token(%s));\n" a;
      List.iter (fun t ->
          Printf.fprintf oc "printf1((uint64_t*)\", %%s\", string_of_token(%s));\n" t;
        ) r;
      Printf.fprintf oc "print((uint64_t*)\"}\");\n"
  end;
  Printf.fprintf oc "  printf1((uint64_t*)\" but got '%%s' instead.\\n\", string_of_symbol(symbol));\n";
  Printf.fprintf oc "  exit(1);\n";
  Printf.fprintf oc "  return NULL;\n";
  Printf.fprintf oc "}\n"

let make_parser  (table: string*string -> lltype list) (toks,nts,rules) oc () =
  Printf.fprintf oc "#include \"%s\"\n" !parser_h_file;
  Printf.fprintf oc "#include \"library.h\"\n";
  Printf.fprintf oc "#include \"parser.h\"\n";
  Printf.fprintf oc "#include \"lexer.h\"\n";
  Printf.fprintf oc "#include \"ast.h\"\n";
  List.iter (fun n -> make_nt table (toks,nts,rules) oc n ()) nts

let make_header (toks,nts,rules) oc () =
  List.iter (fun n -> Printf.fprintf oc "uint64_t* parse_%s();\n" n) nts

let _ =
  Arg.parse
    [("-g", Arg.Set_string grammar_file, "Input grammar file (.g)");
     ("-t", Arg.Set_string table_file, "Where to output tables (.html)");
     ("-pc", Arg.Set_string parser_c_file, "Where to output the parser code (.c)");
     ("-ph", Arg.Set_string parser_h_file, "Where to output the parser header (.h)");
     ("-pdir", Arg.Set_string parser_dir, "In which folder to put the parser files")
    ] print_endline "Usage: ";
  let (toks, nts, rules) = parse_grammar !grammar_file in
  iter_nullnt (toks, nts, rules) ();
  iter_first (toks, nts, rules) ();
  iter_follownt (toks, nts, rules) ();
  fill_lltable (toks, nts, rules) ();
  let oc = open_out !table_file in
  print_html (toks, nts, rules) oc ();
  close_out oc;
  let oc = open_out (Printf.sprintf "%s/%s" !parser_dir !parser_c_file) in
  make_parser (fun (n,t) -> hashget_def lltable (n,t) []) (toks, nts, rules) oc ();
  close_out oc;
  let oc = open_out (Printf.sprintf "%s/%s" !parser_dir !parser_h_file) in
  make_header (toks, nts, rules) oc ();
  close_out oc;

