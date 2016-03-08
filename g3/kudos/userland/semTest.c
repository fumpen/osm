/*
 * =====================================================================================
 *
 *       Filename:  semTest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03-03-2016 15:17:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "lib.h"




int main(void) {
    
    
    usr_sem_t *sem1;
    usr_sem_t *sem2;

    printf("CREATE 1\n ");
    sem1 = syscall_usr_sem_open("child", 100);
    printf("1 SEM CREATED \n");

    printf("CREATE 2\n ");
    sem2 = syscall_usr_sem_open("child", 100);
    printf("2 SEM CREATED\n");

    syscall_usr_sem_procure(sem1);
    syscall_usr_sem_procure(sem2);

    printf("END!\n\n");

    return 0;
}
