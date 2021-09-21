#include <setjmp.h>
#include <stdio.h>

static jmp_buf env_1;
static jmp_buf env_2;

static int count = 0;

void first() {
        
        if (setjmp(env_1) == 0 && count == 0)
                return;

        longjmp(env_2, ++count);
}

void second() {
        if (setjmp(env_2) == 0) {
                count++;
                return;
        }

        longjmp(env_1, ++count);
}

int main() {

        first();
        second();

        first();
}
