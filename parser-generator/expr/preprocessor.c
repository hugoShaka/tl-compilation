#include "library.h"
#include "arguments.h"
#include "globals.h"

uint64_t debug_preprocessor = 0;

// A stack of included files;
uint64_t *files_to_compile = (uint64_t *) 0;


// included file:
// +----+---------+
// |  0 | next    | pointer to next entry
// |  1 | string  | source file name
// |  2 | string  | source file descriptor

uint64_t* get_next(uint64_t *entry) { return (uint64_t *) *entry;}
uint64_t* get_source_filename(uint64_t *entry) { return (uint64_t*) *(entry+1);}
uint64_t get_fd(uint64_t *entry) { return *(entry+2);}

void set_next(uint64_t *entry, uint64_t *next) { *entry = (uint64_t) next; }
void set_source_filename(uint64_t *entry, uint64_t *filename) { *(entry+1) = (uint64_t) filename; }
void set_fd(uint64_t *entry, uint64_t fd) { *(entry+2) = fd; }

void push_source_file(uint64_t *filename){
  uint64_t *entry;
  uint64_t fd;

  if(debug_preprocessor)
    printf1((uint64_t*) "Pushing source file: %s.", filename);

  entry = smalloc(2*SIZEOFUINT64STAR + SIZEOFUINT64);
  set_next(entry, files_to_compile);
  set_source_filename(entry, filename);

  fd = sign_extend(open(filename, O_RDONLY, 0), SYSCALL_BITWIDTH);

  if (signed_less_than(fd, 0)) {
    printf2((uint64_t*) "%s: could not open input file %s\n", get_myname(), filename);

    exit(EXITCODE_IOERROR);
  }

  if(debug_preprocessor)
    printf1((uint64_t*) "File descriptor: %d.\n", (uint64_t *) fd);

  set_fd(entry, fd);
  files_to_compile = entry;

  source_fd = fd;
}

void pop_source_file(){
  uint64_t *entry;
  uint64_t fd;
  uint64_t res;

  entry = files_to_compile;
  fd = get_fd(entry);

  if(debug_preprocessor)
    printf2((uint64_t*) "Popping source file: %s. File descriptor: %d.\n", get_source_filename(entry), (uint64_t *)fd);

  res = sign_extend(close(fd), SYSCALL_BITWIDTH);

  if(signed_less_than(res, 0)) {
    printf2((uint64_t*) "%s: could not close file descriptor %d\n", get_myname(), (uint64_t *) fd);

    exit(EXITCODE_IOERROR);
  }

  if(get_next(entry) != (uint64_t*) 0){
    files_to_compile = get_next(entry);
  }
  else{
    files_to_compile = (uint64_t *)  0;
    source_fd = -1;
    return;
  }

  fd = get_fd(files_to_compile);
  source_fd = fd;
}

