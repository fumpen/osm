/*
 * Runs read to put a sign in the buffer
 * and then write to put that same sign
 * in the console 
 */

#include "lib.h"

int main(void) {
  char buffer[64];
  syscall_read(0, buffer, 64);
  syscall_write(1,buffer,64);
  syscall_halt();
  return 0;
}
