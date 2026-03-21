#include<stdio.h>
#include<memory.h>
#include<unistd.h> /*to get page size*/
#include<sys/mman.h> /* to use mmap()*/

static size_t SYSTEM_PAGE_SIZE = 0;

void 
mm_init(){
	SYSTEM_PAGE_SIZE = getpagesize();
}

/* function to request vm page from kernel */
static void *
mm_get_new_pages_from_kernel(int units){
	char *vm_pages= mmap(
	0,
	units * SYSTEM_PAGE_SIZE,
	PROT_READ|PROT_WRITE|PROT_EXEC,
	MAP_ANON|MAP_PRIVATE,
	0,0);

   	if(vm_pages == MAP_FAILED){
		printf("Error: VM Page Allocation Failed\n");
		return NULL;
	}
	memset(vm_pages, 0, units * SYSTEM_PAGE_SIZE);
	return (void *)vm_pages;
}

static void
mm_return_vm_page_to_kernel (void *vm_page, int units){
	if(munmap(vm_page, units * SYSTEM_PAGE_SIZE)){
		printf("Error: Could not munmap to kernel");
	}

}

int 
main(int argc, char **argv) {
    mm_init();

    printf("VM page size: %lu\n", SYSTEM_PAGE_SIZE);
    void* addr1 = mm_get_new_pages_from_kernel(1);
    void* addr2 = mm_get_new_pages_from_kernel(1);
    printf("page 1 = %p, page 2 = %p\n", addr1, addr2);

    if (addr1 == MAP_FAILED) {
        printf("Allocation failed\n");
    } else {
        printf("Allocated at %p\n", addr1);
    }

    return 0;
}
