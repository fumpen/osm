/*
 * TLB handling
 */

#include "kernel/panic.h"
#include "kernel/assert.h"
#include "kernel/thread.h"
#include <tlb.h>
#include <pagetable.h>


void lookupAdd(){
    

    /*-----------------------------------------------------------------------------
     *  Gets the state parameters for TLB exception
     *-----------------------------------------------------------------------------*/
    tlb_exception_state_t tlb_state;
    _tlb_get_exception_state(&tlb_state);


    /*-----------------------------------------------------------------------------
     *  Gets the current thread and pagetable
     *-----------------------------------------------------------------------------*/
    thread_table_t* current_thread = thread_get_current_thread_entry();
    pagetable_t* pagetable = current_thread->pagetable;

    /*-----------------------------------------------------------------------------
     *  If no entry is found, then we are in kernel mode or access outside of mem
     *-----------------------------------------------------------------------------*/
    if(pagetable == NULL){
        kprintf("KERNEL MODE\n");
        KERNEL_PANIC("TLB exception");
    }

    /*-----------------------------------------------------------------------------
     *  The failing virtual address (bits 31..13)
     *-----------------------------------------------------------------------------*/
    uint32_t badvpn2 = tlb_state.badvpn2;
    uint32_t badaddr = tlb_state.badvaddr;

    tlb_entry_t* entry = NULL;


    /*-----------------------------------------------------------------------------
     *  To distinguishe between (TLB refil) or (TLB invalid) compare VP2N with badvpn,
     *  if VPN2 is equal to badvpn2 then refil.
     *  ____________________________________________________________________________
     *  
     *  VPN2: is the page pair number. VPN2 describes which consecutive 2 page region
     *  of virtual address space this entry maps.
     *  ____________________________________________________________________________
     *  
     *  valid_count: is the number of valid mapping entries in the pagetable
     *-----------------------------------------------------------------------------*/

    for(unsigned int i = 0; i < pagetable->valid_count; i++){
            if(pagetable->entries[i].VPN2 == badvpn2){
                uint32_t evenodd = !(badaddr & 4096);
                if(evenodd){
                    if(pagetable->entries[i].V0){
                        entry = &(pagetable->entries[i]);
                        _tlb_write_random(entry); 
                    }
                    else{
                       process_exit(current_thread->process_id);
                    }
                }
                else{
                    if(pagetable->entries[i].V1){
                        entry = &(pagetable->entries[i]);
                        _tlb_write_random(entry);
                    }
                    else{
                        process_exit(current_thread->process_id);
                    }
                }
            }
    }

}

void tlb_modified_exception(void)
{

    /*-----------------------------------------------------------------------------
     * Checks if the exception is in userland or kernel mode. 
     *-----------------------------------------------------------------------------*/
    thread_table_t* current_thread = thread_get_current_thread_entry();
    pagetable_t* pagetable = current_thread->pagetable;

    /*-----------------------------------------------------------------------------
     *  If exception is in userland mode, the process should exit
     *-----------------------------------------------------------------------------*/
    if(pagetable != NULL){
        process_exit(current_thread->process_id);
    }

   /*-----------------------------------------------------------------------------
    * If exception is in kernel mode, the kernel panic
    *-----------------------------------------------------------------------------*/ 
    KERNEL_PANIC("Unhandled TLB modified exception");
}

void tlb_load_exception(void)
{
  
    lookupAdd();
}

void tlb_store_exception(void)
{
 
    lookupAdd();
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
