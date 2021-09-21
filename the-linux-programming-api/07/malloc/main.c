#include <stdio.h>
#include <alloca.h>

void foo() {

        const int len = 100000;

        void* p = alloca(sizeof(int)*len);

        for (int i = 0; i < len; i++) {

                int* t = ((int*)p + i);
                *t = i;
        }

        for (int i = 0; i < len; i++) {

                int* t = ((int*)p + i);
                printf("%p = %d\n", t, *t);
        }
}

int main(int argc, const char* argv[]) {


        /*
         * As it turns out, we can resize the stack.
         */
        foo();
}
