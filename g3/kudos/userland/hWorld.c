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

    printf("Starting hWorld!!\n");
    
    int test, test1;

    t = syscall_usr_sem_open("test1", 10);
    test = syscall_usr_sem_procure(t);
    
    printf("procure: %d\n", test);
    
    test1 = syscall_usr_sem_vacate(t);
    printf("vacate: %d\n", test1);

    printf("DONE\n");

    return 0;
}

