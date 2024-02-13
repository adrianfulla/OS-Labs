#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main()
{
    pid_t pid1, pid2, pid3;
    clock_t start, end;
    start = clock();
    pid1 = fork();
    if (pid1 == 0){
        pid2 = fork();
        if (pid2 == 0){
            pid3 = fork();
            if (pid3 == 0){
                for (int i = 0; i < 1000000000; i++) {printf("%d\n", i);}
            }
            else{
                for (int i = 0; i < 1000000000; i++) {printf("%d\n", i);}
                wait(NULL);
            }
        }
        else{
            for (int i = 0; i < 1000000000; i++) {printf("%d\n", i);}
                wait(NULL);
        }
    }
    else{
        wait(NULL);
    }
    end = clock();
    
    double dt = ((double)(end - start)/CLOCKS_PER_SEC);

    printf("Tiempo tomado %f\n", dt);
    return 0;
}