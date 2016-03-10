/*
 * =====================================================================================
 *
 *       Filename:  tlb1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10-03-2016 14:19:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "lib.h"


/*-----------------------------------------------------------------------------
 *  Test should fail because the largest size of array is 952
 *-----------------------------------------------------------------------------*/
int main(void){

    int large[953];

    large[0] = 100;

    printf("%d\n", large[0]);


    return 0;
}
