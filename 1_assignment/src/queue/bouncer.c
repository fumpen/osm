#include <stdio.h>  // printf, scanf, stdin
#include <ctype.h>  // isspace

#include "queue.h"


struct queue q;

static inline char
skip_spaces() {
  char c;

  do {
    c = getc(stdin);
  } while (isspace(c));

  return c;
}

static inline void
skip_until_space() {
  char c;

  do {
    c = getc(stdin);
  } while (!(isspace(c) || c == EOF));
}

void
loop() {
  char op = 0;
  int pri = 0;
  int retval;

  while(1) {

    op = skip_spaces();

    switch (op) {
    case EOF:
      return;
      break;

    case 'p':
      if (q.count == 0) 
      { // TODO: Try to pop an element off of the queue.
        printf("!! Queue underflow.\n");
      } else {
        queue_pop(&q, &pri);
        printf("=> %d\n", pri);
      }
      break;

    case 'e':
      return;
      break;

    default:
      ungetc(op, stdin);
      if (scanf("%d", &pri) == 1) {
        if (queue_push(&q, pri) != 0) {
            // TODO: Try to insert the read priority into the queue.
          printf("!! Queue overflow.\n");
        }
      } else {
        skip_until_space();
        printf("Invalid input!\n");
      }
    }
  }
}

void
shutdown() {
  // TODO: Pop everything off of the queue.
    int count;
    int place;
    for(count = 0; count <= q.count; count++){
        queue_pop(&q, &place);
    }
}

int
main() {
  // TODO: Initialize the queue.
  queue_init(&q);

  loop();

  shutdown();

  // TODO: Destroy the queue.
  queue_destroy(&q);

  return 0;
}
