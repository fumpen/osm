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

    int prog2;

    printf("CREATE 1\n ");
    sem1 = syscall_usr_sem_open("sem1", 0);

    printf("CREATE 2\n ");
    sem2 = syscall_usr_sem_open("sem2", 0);

    prog2 = syscall_spawn("[disk]hWorld.mips32", NULL);
    prog2 = prog2;

    printf("Get first print!!\n");

    for(int i = 0; i < 5000; i++);
    syscall_usr_sem_vacate(sem2);
    syscall_usr_sem_procure(sem1);

    printf("Thrid print!\n");
    
    for(int i = 0; i < 6000; i++);
    syscall_usr_sem_vacate(sem2);


    return 0;
}
