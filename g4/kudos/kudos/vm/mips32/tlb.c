/*
 * TLB handling
 */

#include "kernel/panic.h"
#include "kernel/assert.h"
#include <tlb.h>
#include <pagetable.h>

/* 
 * "do_we_panic" funktionen har den funktion at bestemme hvilken situation vi er i
 * når vi kalder en af de tre func nedenunder. er vi i kernen, returnere vi 1,
 * er vi i userland og valid bit er unvalid, kan vi returnere 1, og er der inted galt
 * kan vi returnere 0.
 * OBS! så vidt jeg ved, kan man ikke tjekke for en valid bit medmindre der er en page
 * altså hvis det første tjek evaluere false, skal vi verken lukke programmet i userland eller
 * kalde kernel_panic, men gøre hvad funktionen burde goere
*/
int do_we_panic(pagetable_t *pagetable){
  /* her skal "ubestemt_var" være "true" hvis "valid bit" er usand for det aktuelle page
   * se filen "tlb.h" og undersoeg om vi kan tilgaa den var herinde */
  if(ubestemt_var){
    if (pagetable != NULL){
      kprintf("evaluated as userland \n ");
      /* is in userland */
      return 2;
    }else{
      kprintf("evaluated as kernel \n ");
      /* is in kernel-mode */
      return 1;
    }
  }else{
    /* no error (yet...) */
    return 0;
  }
}

void tlb_modified_exception(void)
{
  pagetable_t *pagetable = thread_get_current_thread_entry()->pagetable;
  int where_are_we;

  /* if we're in kernel-mode kernel panic is called */
  where_are_we = do_we_panic(pagetable);
  if (where_are_we == 1){
  KERNEL_PANIC("Unhandled TLB modified exception");
  }

  /* if */
}

void tlb_load_exception(void)
{
  pagetable_t *pagetable = thread_get_current_thread_entry()->pagetable;
  int where_are_we;

  /* if we're in kernel-mode kernel panic is called */
  where_are_we = do_we_panic(pagetable);
  if (where_are_we == 1){
  KERNEL_PANIC("Unhandled TLB load exception");
  }
  
}

void tlb_store_exception(void)
{
  pagetable_t *pagetable = thread_get_current_thread_entry()->pagetable;
  int where_are_we;

  /* if we're in kernel-mode kernel panic is called */
  where_are_we = do_we_panic(pagetable);
  if (where_are_we == 1){
  KERNEL_PANIC("Unhandled TLB store exception");
  }
}

/*
 * Fill TLB with given pagetable. This function is used to set memory
 * mappings in CP0's TLB before we have a proper TLB handling system.
 * This approach limits the maximum mapping size to 128kB.
 *
 * @param pagetable Mappings to write to TLB.
 *
 */

/*
void tlb_fill(pagetable_t *pagetable)
{
  if(pagetable == NULL)
    return;

   * Check that the pagetable can fit into TLB. This is needed until
     we have proper VM system, because the whole pagetable must fit
     into TLB. *
  KERNEL_ASSERT(pagetable->valid_count <= (_tlb_get_maxindex()+1));

  _tlb_write(pagetable->entries, 0, pagetable->valid_count);

  * Set ASID field in Co-Processor 0 to match thread ID so that
     only entries with the ASID of the current thread will match in
     the TLB hardware. *
  _tlb_set_asid(pagetable->ASID);
}
*/
