uint64_t  myargc = 0;
uint64_t* myargv = (uint64_t*) 0;
uint64_t* myname = (uint64_t*) 0;

uint64_t* get_argument();


void init_arguments(uint64_t argc, uint64_t* argv) {
  myargc = argc;
  myargv = argv;

  myname = get_argument();
}


uint64_t* get_myname(){
  return myname;
}

uint64_t number_of_remaining_arguments() {
  return myargc;
}

uint64_t* remaining_arguments() {
  return myargv;
}

uint64_t* peek_argument() {
  if (number_of_remaining_arguments() > 0)
    return (uint64_t*) *myargv;
  else
    return (uint64_t*) 0;
}

uint64_t* get_argument() {
  uint64_t* argument;

  argument = peek_argument();

  if (number_of_remaining_arguments() > 0) {
    myargc = myargc - 1;
    myargv = myargv + 1;
  }

  return argument;
}

void set_argument(uint64_t* argv) {
  *myargv = (uint64_t) argv;
}
