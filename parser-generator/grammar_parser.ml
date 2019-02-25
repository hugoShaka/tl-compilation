open Str
open Printing
open List_utils
open Grammar_lexer
open Grammar_parser_yacc


let parse_grammar file : string list * string list * (string * string list * string) list =
  let ic = open_in file in
  let lexbuf = Lexing.from_channel ic in
  let (toks,nts,rules) = main token lexbuf in
  let h = Hashtbl.create (List.length nts) in
  List.iter ( fun (nt,p,a) ->
      match Hashtbl.find_opt h nt with
      | None -> Hashtbl.add h nt [(nt,p,a)]
      | Some lp -> Hashtbl.replace h nt (lp@[(nt,p,a)]) ) rules;
  let rules = List.concat (List.map (fun n -> hashget_def h n []) nts) in
  (toks,nts,rules)



let dump_grammar oc (toks, nts, rules) =
  Printf.fprintf oc "tokens";
  List.iter (fun n -> Printf.fprintf oc " %s" n) toks;
  Printf.fprintf oc "\nnon-terminals ";
  List.iter (fun n -> Printf.fprintf oc " %s" n) nts;
  Printf.fprintf oc "\nrules\n";
  List.iter (fun (n,lt,a) -> Printf.fprintf oc "%s ->%s\n" n (print_seq (fun x -> x) lt)) rules
