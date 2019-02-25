uint64_t* source_name = (uint64_t*) 0; // name of source file
uint64_t  source_fd   = 0;             // file descriptor of open source file

uint64_t* assembly_name = (uint64_t*) 0; // name of assembly file
uint64_t  assembly_fd   = 0; // file descriptor of open assembly file

uint64_t* output_name = (uint64_t*) 0;
uint64_t  output_fd   = 1; // 1 is file descriptor of standard output

uint64_t PAGESIZE = 4096;
