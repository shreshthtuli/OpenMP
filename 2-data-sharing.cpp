#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>

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

    printf("This example explicitly specifies that a is private (each thread has their own copy of it) and that b is shared (each thread accesses the same variable).\n");
    int a, b=0;
    #pragma omp parallel for private(a) shared(b)
    for(a=0; a<50; ++a)
    {
        #pragma omp atomic  // Does this operation atomically
        b += a;
    }
    printf("b = %d\n", b);

    // Note that a private copy is an uninitialized variable
    // by the same name and same type as the original variable
    std::string c = "x", d = "x", e = "x";
    int f = 3;
    
    // firstprivate copies values from already used
    #pragma omp parallel private(c) firstprivate(d) shared(e) num_threads(2)
    {
        c += "k";
        d += "k";
        e += "k";
        f += 7;
        std::cout << "c becomes (" << c << "), d is (" << d << "), e is (" << e << ")\n";
    }
    // The lastprivate clause defines a variable private as in firstprivate or private,
    // but causes the value from the last task to be copied back to the original value after
    // the end of the loop/sections construct.
}
