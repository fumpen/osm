/*
 * Process startup.
 */

#ifndef KUDOS_PROC_PROCESS
#define KUDOS_PROC_PROCESS

#include "lib/types.h"
#include "vm/memory.h"

#define PROCESS_PTABLE_FULL  -1
#define PROCESS_ILLEGAL_JOIN -2

#define PROCESS_MAX_FILELENGTH 256
#define PROCESS_MAX_PROCESSES  128
#define PROCESS_MAX_FILES      10

typedef int process_id_t;

enum proc_state {SLEEPING, RUNNABLE, RUNNING, ZOMBIE};

typedef struct {
  /* Remove this when you add other fields. */
  process_id_t process_id;
  enum proc_state state;

} process_control_block_t;

void process_start(const char *executable, const char **argv);

process_id_t process_spawn(const char *executable, const char **argv);



#endif
