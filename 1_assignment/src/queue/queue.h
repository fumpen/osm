#ifndef QUEUE
#define QUEUE

struct queue {
    
    int size;
    int count;
    int *priority;

};


int queue_init(struct queue *queue);

int queue_push(struct queue *queue, int pri);

int queue_pop(struct queue *queue, int *pri_ptr);

int queue_destroy(struct queue *queue);

void heap_print(struct queue *queue);
#endif
