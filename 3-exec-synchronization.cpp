#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    int num, tid;
    printf("Part 1 one thread does the job\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        tid = omp_get_thread_num();
        if(tid == 0) num = omp_get_num_threads();
        #pragma omp barrier // So that all threads print the new value
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    printf("Part 2 master does the job\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        tid = omp_get_thread_num();
        #pragma omp master // no implicit barrier
            if(tid == 0) num = omp_get_num_threads();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    printf("Part 3 any thread can do the job\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        tid = omp_get_thread_num();
        #pragma omp single // implicit barrier
            num = omp_get_num_threads();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    // There is an implicit barrier at the end of each parallel block, and at the end of 
    // each sections, for and single statement, unless the nowait directive is used.
    // The nowait directive can only be attached to sections, for and single. 
    // It cannot be attached to the within-loop ordered clause, for example.

    printf("Part 4 nowait removes the implicit barrier\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        tid = omp_get_thread_num();
        #pragma omp single nowait// implicit barrier
            num = omp_get_num_threads();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    // Unless you use the threadprivate clause, the only important difference between single,
    // nowait and master is that if you have multiple master blocks in a parallel section, you
    // are guaranteed that they are executed by the same thread every time, and hence, the values 
    // of private (thread-local) variables are the same.
}
