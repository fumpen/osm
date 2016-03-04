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



void usr_sem_init(void){
    for(int i = 0; i < MAX_SEM; i++){
        sem_table[i].value = -1;
    }
}
usr_sem_t* usr_sem_open(const char* name, int value){
 
    int length = strlen(name);

    if(length > NAME_LENGTH){
        return NULL;
    }

    if(value >= 0)
    {
        int i;

        for(i = 0; i < MAX_SEM; i++){
            if(stringcmp(sem_table[i].name, name) == 0){
                return NULL;
            }
                sem_table[i].sem = semaphore_create(value);
                stringcopy(sem_table[i].name, name, NAME_LENGTH);
                sem_table[i].value = 0;
                return &sem_table[i];

        }

    }

    
    for(int i = 0; i < MAX_SEM; i++){
        if(stringcmp(sem_table[i].name, name) == 0){
            return &sem_table[i];
        }
    }

    return NULL;

}

int usr_sem_destroy(usr_sem_t* sem){

    interrupt_status_t intr;
    intr = _interrupt_disable();
    spinlock_acquire(&sem->slock);

    if(sem->value < 0){
        kprintf("The process is blocked\n");
        return -1;
    }

    semaphore_destroy(sem->sem);
    
    for(int i = 0; i < MAX_SEM; i++){
        if(stringcmp(sem->name, sem_table[i].name) == 0){
            sem_table[i].value = -1;
        }
    }

    spinlock_release(&sem->slock);
    _interrupt_set_state(intr);

    return 0;
}


int usr_sem_procure(usr_sem_t* sem){
    
    for(int i = 0; i < MAX_SEM; i++){
        if(&(sem_table[i]) == sem){
            semaphore_P(sem->sem);
            return 0;
        }
    }

    return -1;
}


int usr_sem_vacate(usr_sem_t* sem){

    for(int i = 0; i < MAX_SEM; i++){
        if(&(sem_table[i]) == sem){
            semaphore_V(sem->sem);

            return 0;
        }
    }

    return -1;
}
