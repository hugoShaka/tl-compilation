extern uint64_t  myargc;
extern uint64_t* myargv;
extern uint64_t* myname;

extern void init_arguments(uint64_t argc, uint64_t* argv);
extern uint64_t* get_myname();
extern uint64_t number_of_remaining_arguments();
extern uint64_t* remaining_arguments();
extern uint64_t* peek_argument();
extern uint64_t* get_argument();
extern void set_argument(uint64_t* argv);
