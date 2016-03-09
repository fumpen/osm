/*
 * =====================================================================================
 *
 *       Filename:  helloWorld.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02-03-2016 14:52:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "lib.h"
#include "../kudos/proc/syscall.h"



int main(void){
    
    usr_sem_t *sem1;
    usr_sem_t *sem2;


    sem1 = syscall_usr_sem_open("sem1", -1);
    sem2 = syscall_usr_sem_open("sem2", -1);

       
    syscall_usr_sem_procure(sem2);

    for(int i = 0; i < 5000; i++);

    printf("Second print!\n");

    syscall_usr_sem_vacate(sem1);
    syscall_usr_sem_procure(sem2);

    return 0;
}

