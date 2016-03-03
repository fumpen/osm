#include <stdio.h>  // printf, scanf, stdin
#include <ctype.h>  // isspace
#include <pthread.h>

#include "queue.h"

static struct queue queue;


void *push(void *args){

    args = args;
    queue_push(&queue, 2);

    printf("PUSH ID 1\n");    

    return NULL;
}



void *push2(void *args){

    args = args;
    queue_push(&queue, 3);

    printf("PUSH ID 2 \n");    

    return NULL;
}

void *pop(void *args){
    
    int *x_ptr = (int *)args;

    printf("BLOCK\n");
    queue_pop(&queue, &x_ptr);
    printf("DATA: %d\n", x_ptr);

    return NULL;
}

int
main() {
    pthread_t thread_ID, thread_ID2;



    queue_init(&queue);
    printf("Queue init\n");


    int *x;

    pthread_create(&thread_ID, NULL, pop, &x);
    pthread_create(&thread_ID2, NULL, push, NULL);

    pthread_join(thread_ID, NULL);
    
    for(int i = 0; i < 50000; i++);
    
    pthread_join(thread_ID2, NULL);
    

    printf("QUEUE DONE\n");

    return 0;
}
