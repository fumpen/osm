/*
 * =====================================================================================
 *
 *       Filename:  usr_sem.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03-03-2016 12:24:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef KUDOS_PROC_SEM
#define KUDOS_PROC_SEM

#include "lib/types.h"
#include "vm/memory.h"
#include "kernel/spinlock.h"
#include "kernel/semaphore.h"




#define MAX_SEM 128
#define NAME_LENGTH 20

typedef struct {
    char name[NAME_LENGTH];
    int value;

    semaphore_t* sem;

} usr_sem_t;


void usr_sem_init(void);

usr_sem_t* usr_sem_open(const char* name, int value);

int usr_sem_destroy(usr_sem_t* sem);

int usr_sem_procure(usr_sem_t* sem);

int usr_sem_vacate(usr_sem_t* sem);

#endif
