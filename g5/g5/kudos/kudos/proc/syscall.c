/*
 * System calls.
 */
#include <cswitch.h>
#include "proc/syscall.h"
#include "kernel/halt.h"
#include "kernel/panic.h"
#include "lib/libc.h"
#include "kernel/assert.h"
#include "vm/memory.h"
#include "proc/process.h"
#include "fs/vfs.h"
#include "drivers/device.h"
#include "drivers/gcd.h"


int syscall_write(int filehandle, const void *buffer, int length) {
    
    gcd_t *gcd;
    device_t *dev;

    if(filehandle == FILEHANDLE_STDOUT || filehandle == FILEHANDLE_STDERR){
        dev = device_get(TYPECODE_TTY, 0);
        gcd = (gcd_t *)dev->generic_device;
	return gcd->write(gcd, (void*) buffer, length);
    }
    else{
        int written = vfs_write(filehandle, (void*) buffer, length);

        if (written <= length){
            return -5;
        }

        return written;
    }

}

int syscall_read(int filehandle, void *buffer, int length) {
    
    gcd_t *gcd;
    device_t *dev;

    if(filehandle == FILEHANDLE_STDIN){
        dev = device_get(TYPECODE_TTY, 0);
        gcd = (gcd_t *)dev->generic_device;
	return gcd->read(gcd, buffer, length);
    }
    else{
        int read = vfs_write(filehandle, (void*) buffer, length);

        if (read <= length){
            return -5;
        }

        return read;
    }
}

int syscall_open(const char *pathname){
    openfile_t file = vfs_open((char*)pathname);

    if(file < 0){
        return file;
    }

    return file;
}

int syscall_close(int filehandle){
    int closeFile = vfs_close(filehandle);

    if(closeFile != 0){
        return closeFile;
    }

    return closeFile;
}


int syscall_create(const char *pathname, int size){
    if(size > VFS_NAME_LENGTH){
        return VFS_LIMIT;
    }

    int createFile = vfs_create((char*)pathname, size);

    if(createFile != 0){
        return createFile;
    }

    return createFile;
}


int syscall_delete(const char *pathname){
    int removeFile = vfs_remove((char*)pathname);

    if(removeFile != 0){
        return removeFile;
    }

    return removeFile;
}

int syscall_seek(int filehandle, int offset){
  int seekFile = vfs_seek(filehandle, offset);

  if(seekFile != 0){
      return seekFile;
  }

  return seekFile;
}


int syscall_filecount(const char *pathname){
    int countFile = vfs_filecount((char*)pathname);

    if(countFile != 0){
        return countFile;
    }

    return countFile;
}

int syscall_file(const char *pathname, int nth, char *buffer){
    int fileN = vfs_file((char*)pathname, nth, buffer);

    if(fileN != 0){
        return fileN;
    }

    return fileN;
}
/**
 * Handle system calls. Interrupts are enabled when this function is
 * called.
 */
uintptr_t syscall_entry(uintptr_t syscall,
                        uintptr_t arg0, uintptr_t arg1, uintptr_t arg2)
{
  int retval = 0;

  arg0 = arg0;
  arg1 = arg1;
  arg2 = arg2;
  /* When a syscall is executed in userland, register a0 contains
   * the number of the syscall. Registers a1, a2 and a3 contain the
   * arguments of the syscall. The userland code expects that after
   * returning from the syscall instruction the return value of the
   * syscall is found in register v0. Before entering this function
   * the userland context has been saved to user_context and after
   * returning from this function the userland context will be
   * restored from user_context.
   */
  
  switch(syscall) {
  case SYSCALL_HALT:
    halt_kernel();
    break;
  case SYSCALL_READ:
    return syscall_read(arg0, (void*)arg1, arg2);
    break;
  case SYSCALL_WRITE:
    return syscall_write(arg0, (const void*)arg1, arg2);
    break;
  case SYSCALL_SPAWN:
    return process_spawn((char*) arg0, (char const**) arg1);
    break;
  case SYSCALL_EXIT:
    process_exit((process_id_t) arg0);
    break;
  case SYSCALL_JOIN:
    return process_join((process_id_t) arg0);
    break;
  case SYSCALL_OPEN:
    return syscall_open((const char*)arg0);
    break;
  case SYSCALL_CREATE:
    return syscall_create((const char*)arg0, arg1);
    break;
  case SYSCALL_CLOSE:
    return syscall_close(arg0);
    break;
  case SYSCALL_DELETE:
    return syscall_delete((const char*)arg0);
    break;
  case SYSCALL_SEEK:
    return syscall_seek(arg0, arg1);
    break;
  case SYSCALL_FILECOUNT:
    return syscall_filecount((const char*)arg0);
    break;
  case SYSCALL_FILE:
    return syscall_file((const char*)arg0, arg1, (char*)arg2);
    break;
  default:
    KERNEL_PANIC("Unhandled system call\n");
  }

  return retval;
}
