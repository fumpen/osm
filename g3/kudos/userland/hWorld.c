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
    
    usr_sem_t *t;

    printf("Child\n");


    t = syscall_usr_sem_open("child", 10);
    
    syscall_usr_sem_vacate(&t);

    return 0;
}

