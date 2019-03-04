# Compiler flags
CFLAGS := -Wall -g -O0 -m64 -D'main(a,b)=main(int argc, char** argv)' -Duint64_t='unsigned long long' -DNULL='(uint64_t*) 0' -fno-builtin

HEADERS= \
	arguments.h \
	ast.h \
	expr_dump.h \
	compiler.h \
	expr_parser.h \
	globals.h \
	lexer.h \
	library.h \
	memory.h \
	parser.h \
	preprocessor.h \
	expr_eval.h \
	dump_ast.h \
	riscv.h \
	genriscv.h \
	eval_riscv.h

CFILES=\
	arguments.c \
	ast.c \
	expr_dump.c \
	compiler.c \
	expr_parser.c \
	globals.c \
	library.c \
	parser.c \
	preprocessor.c \
	lexer.c \
	expr_eval.c \
	dump_ast.c \
	riscv.c \
	genriscv.c \
	eval_riscv.c

OBJS=$(CFILES:.c=.o)

TESTS=tests/*.e

all: cstar

%.o: %.c
	$(CC) $(CFLAGS) $? -c $<

cstar: ${OBJS} main-cstar.o
	$(CC) $(CFLAGS) $^ -o $@

test: $(TESTS) cstar
	@for i in $(TESTS); do \
		echo "$$i..."; \
		./cstar -c $$i; \
	done


# Clean up
clean:
	rm -rf *.o
	rm -rf *.m
	rm -rf *.s
	rm -rf cstar
