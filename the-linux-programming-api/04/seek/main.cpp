#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <cstdint>

char next_cmd() {
        char buf[1];
        int l = read(STDIN_FILENO, buf, sizeof(buf) / sizeof(char));
        if (l == -1) {
                // handle error
        }

        return buf[0];
}

int fd;
mode_t pr;
char buf[2];

int main(int argc, char* argv[]) {

        if (argc != 2 || strcmp("--help", argv[1]) == 0) {
                printf("%s ./file\n", argv[0]);
                return 0;
        }

        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
                //haneld error
                return -1;
        }

        int t = 0;
        while (t < 3) {

                t++;
                switch (next_cmd()) {
                        case 'h': {
                                          lseek(fd, -1, SEEK_CUR);
                                  }
                        case 'l': {
                                          lseek(fd, 1, SEEK_CUR);
                                  }
                        default: {
                                continue;
                                 }
                }
        }

        read(fd, buf, 1);
        buf[1] = '\0';
        printf((const char*) buf);

        if (close(fd) == -1) {
                // handle_erro
        }
}
