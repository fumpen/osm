/*
 * =====================================================================================
 *
 *       Filename:  procTest.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02-03-2016 10:56:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "lib.h"
#include "lib.h"
#include "../kudos/proc/syscall.h"



int main(void) {
 
    char prog[] = "[disk]hWorld.mips32";
    int ret;
    int child;

    printf("Starting program %s\n", prog);

    child = syscall_spawn(prog, NULL);
    
    for(int i = 0; i < 1000; i++);

    printf("Now joining child %d\n", child);
    ret = (char)syscall_join(child);

    printf("Child joined with status: %d\n", ret);
    syscall_halt();

    return 0;


 

}
