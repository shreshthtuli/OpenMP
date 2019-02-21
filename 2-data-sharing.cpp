#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    
    #pragma omp parallel 
    {
        int num = omp_get_num_threads(); // Num threads in this parallel region
        int tid = omp_get_thread_num();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    printf("Part 1 data race not exposed as each thread writes separtely to tid\n");
    int num, tid;
    #pragma omp parallel 
    {
        num = omp_get_num_threads(); // Num threads in this parallel region
        tid = omp_get_thread_num();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    printf("Part 2 data race exposed as tid is shared and all threads see wwhat the last thread writes\n");
    num = 0, tid = 0;
    #pragma omp parallel 
    {
        num = omp_get_num_threads(); // Num threads in this parallel region
        tid = omp_get_thread_num();
        sleep(1);
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    printf("Part 3 solution is to declare tid as private which then becomes thread local (on its stack)\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        num = omp_get_num_threads(); // Num threads in this parallel region
        tid = omp_get_thread_num();
        sleep(1);
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    printf("Part 4 thread 0 is master thread\n");
    num = 0, tid = 0;
    printf("master : hello-world %x of %x\n", &tid, &num);
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        num = omp_get_num_threads(); // Num threads in this parallel region
        tid = omp_get_thread_num();
        printf("hello-world tid = %d, %x of %x\n", tid, &tid, &num);
    } // Implicit barrier here

}
