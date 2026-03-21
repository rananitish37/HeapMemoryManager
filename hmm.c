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

int main() {
    mm_init();

    void* ptr = mm_get_new_pages_from_kernel(1);

    if (ptr == MAP_FAILED) {
        printf("Allocation failed\n");
    } else {
        printf("Allocated at %p\n", ptr);
    }

    return 0;
}
