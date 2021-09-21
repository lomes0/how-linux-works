#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUF_ZISE
#define BUF_ZISE 1024
#endif

void check_fd(int fd) {

        if (fd == -1) {
                printf("error opening file\n");
                while (1) {
                }
        }
}

void close_fd(int fd) {

        if (close(fd) == -1) {

                printf("error closing file desc\n");
                while (1) {
                }
        }
}


int main(int argc, char* argv[]) {

        int in_fd;
        int out_fd[2];
        int open_fl;
        mode_t file_pr;
        size_t num_read;
        size_t in_size;
        char buf[BUF_ZISE];

        if (argc != 2 || strcmp(argv[1], "--help") == 0) {
                printf("HELP:: %s file_path\n", argv[0]);
                return -1;
        }

        in_fd = open(argv[1], O_RDONLY);
        check_fd(in_fd);

        /*
         * Create outputs.
         */

        open_fl = O_CREAT | O_TRUNC | O_WRONLY;
        file_pr = S_IRUSR | S_IWUSR | 
                  S_IRGRP | S_IWGRP | 
                  S_IROTH | S_IWOTH;

        out_fd[0] = open("a", open_fl, file_pr);
        out_fd[1] = open("b", open_fl, file_pr);
        check_fd(out_fd[0]);
        check_fd(out_fd[1]);

        struct stat st;
        stat(argv[1], &st);
        in_size = st.st_size;

        size_t total = 0;
        int fd = out_fd[0];
        while ((num_read = read(in_fd, buf, BUF_ZISE)) > 0) {
                total += num_read;
                if (total > (in_size / 2)) {
                        fd = out_fd[1];
                }

                if (write(fd, buf, num_read) != num_read) {
                        printf("fatal writing error\n");
                        while (1) {
                        }
                }
        }


        close_fd(in_fd);
        close_fd(out_fd[0]);
        close_fd(out_fd[1]);

        return 0;
}
