// -----------------------------------------------------------------
// ----------------------- BUILTIN PROCEDURES ----------------------
// -----------------------------------------------------------------

extern void      exit(uint64_t code);
extern uint64_t read(uint64_t fd, uint64_t* buffer, uint64_t bytes_to_read);
extern uint64_t write(uint64_t fd, uint64_t* buffer, uint64_t bytes_to_write);
extern uint64_t open(uint64_t* filename, uint64_t flags, uint64_t mode);
extern uint64_t close(uint64_t fd);
extern uint64_t* malloc(uint64_t size);


// Functions

extern void init_library();
extern void reset_library();

extern uint64_t two_to_the_power_of(uint64_t p);
extern uint64_t ten_to_the_power_of(uint64_t p);

extern uint64_t left_shift(uint64_t n, uint64_t b);
extern uint64_t right_shift(uint64_t n, uint64_t b);

extern uint64_t get_bits(uint64_t n, uint64_t i, uint64_t b);
extern uint64_t get_low_word(uint64_t n);
extern uint64_t get_high_word(uint64_t n);

extern uint64_t abs(uint64_t n);

extern uint64_t signed_less_than(uint64_t a, uint64_t b);
extern uint64_t signed_division(uint64_t a, uint64_t b);

extern uint64_t is_signed_integer(uint64_t n, uint64_t b);
extern uint64_t sign_extend(uint64_t n, uint64_t b);
extern uint64_t sign_shrink(uint64_t n, uint64_t b);

extern uint64_t  load_character(uint64_t* s, uint64_t i);
extern uint64_t* store_character(uint64_t* s, uint64_t i, uint64_t c);

extern uint64_t  string_length(uint64_t* s);
extern uint64_t* string_copy(uint64_t* s);
extern void      string_reverse(uint64_t* s);
extern uint64_t  string_compare(uint64_t* s, uint64_t* t);

extern uint64_t  atoi(uint64_t* s);
extern uint64_t* itoa(uint64_t n, uint64_t* s, uint64_t b, uint64_t a);

extern uint64_t fixed_point_ratio(uint64_t a, uint64_t b, uint64_t f);
extern uint64_t fixed_point_percentage(uint64_t r, uint64_t f);

extern void put_character(uint64_t c);

extern void print(uint64_t* s);
extern void println();

extern void print_character(uint64_t c);
extern void print_string(uint64_t* s);
extern void print_integer(uint64_t n);
extern void unprint_integer(uint64_t n);
extern void print_hexadecimal(uint64_t n, uint64_t a);
extern void print_octal(uint64_t n, uint64_t a);
extern void print_binary(uint64_t n, uint64_t a);

extern uint64_t print_format0(uint64_t* s, uint64_t i);
extern uint64_t print_format1(uint64_t* s, uint64_t i, uint64_t* a);

extern void printf1(uint64_t* s, uint64_t* a1);
extern void printf2(uint64_t* s, uint64_t* a1, uint64_t* a2);
extern void printf3(uint64_t* s, uint64_t* a1, uint64_t* a2, uint64_t* a3);
extern void printf4(uint64_t* s, uint64_t* a1, uint64_t* a2, uint64_t* a3, uint64_t* a4);
extern void printf5(uint64_t* s, uint64_t* a1, uint64_t* a2, uint64_t* a3, uint64_t* a4, uint64_t* a5);
extern void printf6(uint64_t* s, uint64_t* a1, uint64_t* a2, uint64_t* a3, uint64_t* a4, uint64_t* a5, uint64_t* a6);

extern uint64_t round_up(uint64_t n, uint64_t m);

extern uint64_t* smalloc(uint64_t size);
extern uint64_t* zalloc(uint64_t size);

extern uint64_t open_write_only(uint64_t* name);

extern uint64_t* touch(uint64_t* memory, uint64_t length);

// ------------------------ GLOBAL CONSTANTS -----------------------

extern uint64_t DONOTEXIT;
extern uint64_t EXIT;

extern uint64_t EXITCODE_NOERROR;
extern uint64_t EXITCODE_BADARGUMENTS;
extern uint64_t EXITCODE_IOERROR;
extern uint64_t EXITCODE_SCANNERERROR;
extern uint64_t EXITCODE_PARSERERROR;
extern uint64_t EXITCODE_COMPILERERROR;
extern uint64_t EXITCODE_OUTOFVIRTUALMEMORY;
extern uint64_t EXITCODE_OUTOFPHYSICALMEMORY;
extern uint64_t EXITCODE_DIVISIONBYZERO;
extern uint64_t EXITCODE_UNKNOWNINSTRUCTION;
extern uint64_t EXITCODE_UNKNOWNSYSCALL;
extern uint64_t EXITCODE_MULTIPLEEXCEPTIONERROR;
extern uint64_t EXITCODE_SYMBOLICEXECUTIONERROR;
extern uint64_t EXITCODE_OUTOFTRACEMEMORY;
extern uint64_t EXITCODE_UNCAUGHTEXCEPTION;

extern uint64_t SYSCALL_BITWIDTH; // integer bit width for system calls

extern uint64_t INT64_MAX; // maximum numerical value of a signed 64-bit integer
extern uint64_t INT64_MIN; // minimum numerical value of a signed 64-bit integer


extern uint64_t CPUBITWIDTH;

extern uint64_t SIZEOFUINT64; // must be the same as REGISTERSIZE
extern uint64_t SIZEOFUINT64STAR; // must be the same as REGISTERSIZE

extern uint64_t* power_of_two_table;


extern uint64_t UINT64_MAX; // maximum numerical value of an unsigned 64-bit integer

extern uint64_t WORDSIZE; // in bytes
extern uint64_t WORDSIZEINBITS;

extern uint64_t REGISTERSIZE; // must be twice of WORDSIZE


extern uint64_t MAX_FILENAME_LENGTH;

extern uint64_t* integer_buffer;   // buffer for printing integers
extern uint64_t* filename_buffer;  // buffer for opening files
extern uint64_t* binary_buffer;    // buffer for binary I/O
extern uint64_t* character_buffer; // buffer for reading and writing characters

extern uint64_t number_of_written_characters;

extern uint64_t O_RDONLY;
extern uint64_t MAC_O_CREAT_TRUNC_WRONLY;
extern uint64_t LINUX_O_CREAT_TRUNC_WRONLY;
extern uint64_t WINDOWS_O_BINARY_CREAT_TRUNC_WRONLY;
extern uint64_t S_IRUSR_IWUSR_IRGRP_IROTH;
