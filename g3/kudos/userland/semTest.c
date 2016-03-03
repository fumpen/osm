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
    int child1, child2, child3;


    printf("Starting the 1'st program %s\n", prog);
    child1 = syscall_spawn(prog, NULL);
    printf("child1: %d\n", child1);
    
    printf("Starting the 2'nd program %s\n", prog);
    child2 = syscall_spawn(prog, NULL);
    printf("child2: %d\n", child2);
    
    printf("Starting the 3'rd program %s\n", prog);
    child3 = syscall_spawn(prog, NULL); 
    printf("child3: %d\n", child3);
    
    return 0;
}
