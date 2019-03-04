OCB=ocamlbuild -use-ocamlfind -cflag -g
SRC=parser_generator.ml grammar_parser.ml ll_parser.ml list_utils.ml printing.ml grammar_lexer.mll grammar_parser_yacc.mly
TG = parser_generator

all: $(TG)

$(TG): $(TG).native
	cp $(TG).native $(TG)

parser_generator.native: $(SRC)
	$(OCB) parser_generator.native

clean:
	rm -f $(TG).native $(TG)
