extern uint64_t debug_preprocessor;
extern uint64_t *files_to_compile;

extern uint64_t* get_next(uint64_t *entry);
extern uint64_t* get_source_filename(uint64_t *entry);
extern uint64_t get_fd(uint64_t *entry);

extern void set_next(uint64_t *entry, uint64_t *next);
extern void set_source_filename(uint64_t *entry, uint64_t *filename);
extern void set_fd(uint64_t *entry, uint64_t fd);

extern void push_source_file(uint64_t *filename);
extern void pop_source_file();
