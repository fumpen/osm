/*
 * =====================================================================================
 *
 *       Filename:  usr_sem.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03-03-2016 12:28:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <arch.h>
#include <stddef.h>             // NULL, comes from GCC.


#include "proc/usr_sem.h"
#include "proc/elf.h"
#include "kernel/thread.h"
#include "kernel/assert.h"
#include "kernel/interrupt.h"
#include "kernel/config.h"
#include "fs/vfs.h"
#include "kernel/sleepq.h"
#include "vm/memory.h"
#include "lib/libc.h" 
#include "drivers/device.h"     // device_*
#include "drivers/gcd.h"        // gcd_*
#include "kernel/assert.h"      // KERNEL_ASSERT
#include "proc/syscall.h"       // FILEHANDLE_*


static usr_sem_t sem_table[MAX_SEM];
spinlock_t proc_lock;


void usr_sem_init(void){
    for(int i = 0; i < MAX_SEM; i++){
        sem_table[i].value = -1;
    }
}


int find_free_sem()
{   
    int free = -1;

    int i;

    for(i = 0; i < MAX_SEM; i++)
    {
        if(sem_table[i].value == -1){
            free = i;
            break;
        }
    }

    return free;
}

usr_sem_t* usr_sem_open(const char* name, int value){
 


    interrupt_status_t intr;
    intr = _interrupt_disable();
    spinlock_acquire(&proc_lock);


    int length = strlen(name);
    

    /*-----------------------------------------------------------------------------
     *  If the length of the name extends the Max name length
     *-----------------------------------------------------------------------------*/
    if(length > NAME_LENGTH){
        return NULL;
    }


    /*-----------------------------------------------------------------------------
     *  A fresh semaphore of the given name will be created with value, unless
     *  a semaphore of that name already exists.
     *-----------------------------------------------------------------------------*/
    if(value >= 0){ 
        
        for(int i = 0; i < MAX_SEM; i++){ 
            int compareName = stringcmp(sem_table[i].name, name);

            if(compareName == 0){
                    kwrite("EQUAL!!!\n");
                     return NULL;
            }
        }

        int free = find_free_sem();

        sem_table[free].sem = semaphore_create(value);
        stringcopy(sem_table[free].name, name, NAME_LENGTH);
        sem_table[free].value = value;
        
        spinlock_release(&proc_lock);
        _interrupt_set_state(intr);

        return &sem_table[free];
    }
    else{
        for(int i = 0; i < MAX_SEM; i++){
            if(stringcmp(sem_table[i].name, name) == 0){
                
                spinlock_release(&proc_lock);
                _interrupt_set_state(intr);
                
                return &sem_table[i];
            }
        }
    }


    spinlock_release(&proc_lock);
    _interrupt_set_state(intr);
    
    return NULL;
}

int usr_sem_destroy(usr_sem_t* sem){

    interrupt_status_t intr;
    intr = _interrupt_disable();
    spinlock_acquire(&proc_lock);

    if(sem->value < 0){
        kprintf("The process is blocked\n");
        return -1;
    }

    sem->value = -1;

    spinlock_release(&proc_lock);
    _interrupt_set_state(intr);

    return 0;
}


int usr_sem_procure(usr_sem_t* sem){
   
    if(sem >= sem_table && sem <= &sem_table[MAX_SEM - 1]){
        semaphore_P(sem->sem);
    }else{
        return -1;
    }

    return 0;

}


int usr_sem_vacate(usr_sem_t* sem){

    if(sem >= sem_table && sem <= &sem_table[MAX_SEM - 1]){
        semaphore_V(sem->sem);
    }else{
        return -1;
    }

    return 0;

}
