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


/*-----------------------------------------------------------------------------
 *  The different states a process can be in
 *-----------------------------------------------------------------------------*/
enum proc_state { UNUSED, EMBRYO, SLEEPING,
                  RUNNABLE, RUNNING, ZOMBIE };

typedef struct {
 
 /*-----------------------------------------------------------------------------
  * Process state  
  *-----------------------------------------------------------------------------*/
  enum proc_state state;
  


  /*-----------------------------------------------------------------------------
   *  Process ID
   *-----------------------------------------------------------------------------*/
  int pid;

} process_control_block_t;


/*-----------------------------------------------------------------------------
 *  Load and run the executable as a new process in a new thread
 *-----------------------------------------------------------------------------*/
process_id_t process_spawn(char const* executable, char const **argv);


/*-----------------------------------------------------------------------------
 *  Stop the current process and the kernel thread in which it runs
 *-----------------------------------------------------------------------------*/
void process_exit(int retval);



/*-----------------------------------------------------------------------------
 *  Wait for the given process to terminate
 *-----------------------------------------------------------------------------*/
int process_join(process_id_t pid);




/*-----------------------------------------------------------------------------
 *  Initialize process table
 *-----------------------------------------------------------------------------*/
void process_init(void);



/*-----------------------------------------------------------------------------
 *  Get current process
 *-----------------------------------------------------------------------------*/
process_id_t process_get_current_process(void);



/*-----------------------------------------------------------------------------
 *  Get PCB of current process
 *-----------------------------------------------------------------------------*/
process_control_block_t *process_get_current_process_entry(void);

#endif
