#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*
 * * =================================================
 * *       Filename:  queue.c
 * *
 * *    Description:  A Heap max-priority queue 
 * *
 * *        Created:  
 * *       Compiler:  gcc
 * *
 * *         Author: Jeppe S. Skov & Frederik L. Henriksen
 * *
 * * =================================================
 * */



/*-----------------------------------------------------------------------------
 *  The size of the Heap after initalization
 *-----------------------------------------------------------------------------*/
#define INIT_SIZE         0



/*-----------------------------------------------------------------------------
 *  Parent node, Left child, Right child
 *-----------------------------------------------------------------------------*/
#define PARENT(i)       ((i - 1) / 2)
#define LEFTC(i)        ((i * 2) + 1)
#define RIGHTC(i)       ((i * 2) + 2)

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  queue_init
 *  Description:  Initialize the queue. Should be used before any calls to the queue
 * =====================================================================================
 */

int queue_init(struct queue *queue){
    

    /*-----------------------------------------------------------------------------
     *  queue->count contains the number of items in the queue
     *-----------------------------------------------------------------------------*/
    queue->count = 0;
    queue->size = INIT_SIZE;

    /*-----------------------------------------------------------------------------
     *  Initial memory allocation
     *-----------------------------------------------------------------------------*/
    queue->priority = (int *) malloc(sizeof(int) * 4);
   

    /*-----------------------------------------------------------------------------
     *  Checks if malloc failes
     *-----------------------------------------------------------------------------*/
    if(!queue->priority){
        return -1;
    }


    return 0;
}

/* ----- end of function queue_init ----- */




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  queue_push
 *  Description:  Insert an element as a priority
 * =====================================================================================
 */

int queue_push(struct queue *queue, int pri){
        
    int index, parent;
    


    /*-----------------------------------------------------------------------------
     *  Checks if the qeueus memeory is filled, and if then it expanse
     *-----------------------------------------------------------------------------*/
    if(queue->count == queue->size){
        
        queue->size += 4;
        queue->priority = realloc(queue->priority, sizeof(int) * queue->size);
        
        /*-----------------------------------------------------------------------------
         *  Checks if memory allocation fails
         *-----------------------------------------------------------------------------*/
        if(!queue->priority){
            return -1;
        }

    }


    /*-----------------------------------------------------------------------------
     *  Insert last of array
     *-----------------------------------------------------------------------------*/
    index = queue->count++;


    /*-----------------------------------------------------------------------------
     *  Loops through the heap to check where it should put the wanted priority
     *-----------------------------------------------------------------------------*/
    for(;index; index = parent){
        
        parent = PARENT(index);

        if (queue->priority[parent] >= pri){
            break;
        }

        queue->priority[index] = queue->priority[parent];
        
    }

        queue->priority[index] = pri;


     return 0;
}

/* ----- end of function queue_push -----   */




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  heap_print
 *  Description:  Prints the heap, for testing purpose
 * =====================================================================================
 */


void heap_print(struct queue *queue){
    
    /*-----------------------------------------------------------------------------
     *  Prints all the nodes in the Heap
     *-----------------------------------------------------------------------------*/
    int index;
    for(index = 0; index < queue->count; ++index) {

        printf("|-- %d --|", queue->priority[index]);
    }

    printf("\n");
}

/* ----- end of function heap_print ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  max_heapify
 *  Description:  To maintain the max-heap property after node removal, used in queue_pop
 * =====================================================================================
 */

void max_heapify(struct queue *queue, int node){
       
       int largest, tmp;
        


       /*-----------------------------------------------------------------------------
        *  Find left child - l, and right child - r, for node
        *-----------------------------------------------------------------------------*/
       int l = LEFTC(node);
       int r = RIGHTC(node);


        
       /*-----------------------------------------------------------------------------
        *  Checks if the left child has higher priority
        *-----------------------------------------------------------------------------*/
       if(l <= queue->count && queue->priority[l] > queue->priority[node]){
            largest = l;
       }
       else {
            largest = node;
       }


        
       /*-----------------------------------------------------------------------------
        *  Checks if the right child has higher priority
        *-----------------------------------------------------------------------------*/
       if(r <= queue->count && queue->priority[r] > queue->priority[largest]){
            largest = r;
       }
        

       /*-----------------------------------------------------------------------------
        *  If node is the largest, then the subtree rooted at the node is already a max-heap
        *  and the procedure terminates. Otherwise, one of the two children has the largest
        *  element, and priority[node] is swapped with priorirty[largest], which causes
        *  the node and its children to satisfy the max-heap property.
        *-----------------------------------------------------------------------------*/
       if(largest != node){
            tmp = queue->priority[node];
            queue->priority[node] = queue->priority[largest];
            queue->priority[largest] = tmp;
            
            max_heapify(queue, largest);
       }
}

/* ----- end of function max_heapify ----- */




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  queue_pop
 *  Description:  Pop the maximum priority out of the queue.
 *                The popped priority is stored at the given address
 *              
 * =====================================================================================
 */
int queue_pop(struct queue *queue, int *pri_ptr){
    
    *pri_ptr = queue->priority[0];
    int tmp = queue->priority[--queue->count];
   
     
    /*-----------------------------------------------------------------------------
     *  Reallocates memory if there are less needed and removes a priority
     *-----------------------------------------------------------------------------*/
  if (queue->count > 4){
    if (((queue->count + 4) <= queue->size) && (queue->size > INIT_SIZE)){
        queue->size -= 4;
        queue->priority = realloc(queue->priority, sizeof(int) * queue->size);

        if(!queue->priority){
            return -1;
        }
    }
  }

    queue->priority[0] = tmp;
    max_heapify(queue, 0);

    return 0;
}

/* ----- end of function queue_pop ----- */




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  queue_destroy
 *  Description:  Destroys the queue after usage
 * =====================================================================================
 */
int queue_destroy(struct queue *queue){
    free(queue->priority);
    
    return 0;
}

/* ----- end of function queue_destroy ----- */

