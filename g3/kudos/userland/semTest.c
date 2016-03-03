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
    
    char prog[] = "[disk]hWorld.mips32";
    
    usr_sem_t *parent2;


    printf("Parent: begin\n");
    syscall_spawn(prog, NULL);

    parent2 = syscall_usr_sem_open("child", 100);
    syscall_usr_sem_procure(&parent2);

    for(int i = 0; i < 5000; i++);

    printf("Parent: end\n");
    

    return 0;
}
