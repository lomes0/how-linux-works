#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

/* To get various declarations from <stdlib.h> */
extern char **environ;
int
main(int argc, char *argv[])
{
        int j;
        char **ep;
        clearenv();

        /* Erase entire environment */
        for (j = 1; j < argc; j++)
                setenv(argv[j], argv[j], 1);

        for (ep = environ; *ep != NULL; ep++)
                printf("%s\n", *ep);

        exit(EXIT_SUCCESS);
}
