// Checking the page size of the system --- Unix based
// https://en.wikipedia.org/wiki/Page_(computer_memory)

// The LSM Tree Project, CS265
// Hongyao Ma
// 04/29/2016

#include <stdio.h>
#include <unistd.h> /* sysconf(3) */

int main(void) {
	printf("The page size for this system is %ld bytes.\n",
	       sysconf(_SC_PAGESIZE)); /* _SC_PAGE_SIZE is OK too. */

	return 0;
}