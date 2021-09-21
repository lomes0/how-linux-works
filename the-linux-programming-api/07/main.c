#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int
main(int argc, char *argv[])
{

        const int num_pages = 199;

        /*
         * Get current data segment end point.
         */
        void* c1 = sbrk(0);

        /*
         * Allocate num_pages * PAGE_SIZE bytes.
         * Kernel will assign at least num_pages.
         */
        void* ptrs[num_pages];
        for (int i = 0; i < num_pages; i++)
                ptrs[i] = malloc(PAGE_SIZE);

        /*
         * Get current data segment end point.
         */
        void* c2 = sbrk(0);
        printf("%p bytes = %ld pages\n", (void*)(c2-c1), (c2-c1) / PAGE_SIZE);


        for (int i = 0; i < num_pages; i++)
                free(ptrs[i]);

        return 0;
}
