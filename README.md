
# mmap(),munmap()

## Allocation and DeAllocation of memory
These linux operating provided system calls.

Size of the virtual memory is constant on the system (8192 B on most system)
We usually use malloc/calloc to allocate dynamic memory in our program
To start with, we need to learn how we can request underlying linux OS the complete VM page


Out Linux Memory Manager (a user space process) requests a VM page to the kernel or we can say issues a request to the linux kernel system 
When linux kernel receives the request it returns the pointer to the virtual memory page
The allocation is done as entirely one virtual memory page


So our Linux memory manager can not request any arbitrary memory size from the kernel the request should be of one entire virtual page or any integral of VM page size.
