#include <omp.h>
#include <stdio.h>


int main(){

    printf("Simple with all cores\n");
    // Compiler directive which creates a team of parallel threads
    // for the given code section using fork-join model, with thread
    // id 0 to the master thread. Only master thread resumes after 
    // implicit barrier
    #pragma omp parallel 
    {
        int tid = omp_get_thread_num();
        printf("hello-world %d\n", tid);
    } // Implicit barrier here

    printf("Simple with 2 cores\n");
    #pragma omp parallel num_threads(2)// Compiler directive
    {
        int tid = omp_get_thread_num();
        printf("hello-world %d\n", tid);
    } // Implicit barrier here
}
