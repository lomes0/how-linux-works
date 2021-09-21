#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')

extern int optind, optopt, opterr;
extern char *optarg;

char buf[100];
char* out;
static int append = 0;

void read_stdin() {
        int l = read(STDIN_FILENO, buf, sizeof(buf)/ sizeof(char) - 1);

        if (l == -1) {
                // handle error
                exit(EXIT_FAILURE);
        }
        buf[l-1] = '\0';
}

void write2file() {
        // writing to file
        // mode_t pr;
        int fd;
        int flags;

        flags = O_WRONLY;
        if (append)
                flags |= O_APPEND;
        fd = open(out, flags);

        close(fd);
}

/* Print "usage" message and exit */
static void usage_error(char *progName, char *msg, int opt)
{
        if (msg != NULL && opt != 0)
                fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
        fprintf(stderr, "Usage: %s [-p arg] [-x]\n", progName);
        exit(EXIT_FAILURE);
}

void fatal(const char* err) {
        fprintf(stderr, "%s", err);
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
        int opt;
        int append = 0;

        /*
         * Parsing arguments...
         * ./tee -f file [-a]
         */
        while ((opt = getopt(argc, argv, ":f:a")) != -1) {

                switch (opt) {
                        case 'f': out = optarg;
                                  break;
                        case 'a': append++;
                                  break;
                        case ':': usage_error(argv[0], "Missing argument", optopt);
                        case '?': usage_error(argv[0], "Unrecognized option", optopt);
                        default: fatal("Unexpected case in switch()");
                }
        }

        // read stdin
        read_stdin();
        printf("Writing %s to %s\n", buf, out);

        write2file();
        exit(EXIT_SUCCESS);

        return 0;
}
