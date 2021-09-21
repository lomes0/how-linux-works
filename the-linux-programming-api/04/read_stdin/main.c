#include <stdio.h>
#include <unistd.h>

#define MAX_READ 20

int main() {

        char buf[MAX_READ + 1];
        size_t num_rd;
        
        num_rd = read(STDIN_FILENO, buf, MAX_READ);

        if (num_rd == -1) {
                return -1;
        }

        for (int i = 0; i < num_rd; i++) {
                buf[i] /= 2;
        }

        buf[num_rd] = '\0';
        printf("%s\n", buf);
}
