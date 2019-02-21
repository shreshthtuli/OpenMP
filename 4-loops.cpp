#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <string>

int main(){

    int fac = 1;
    float start = omp_get_wtime();
    printf("#pragma omp parallel for is for for loops\n");
    #pragma omp parallel for
    for(int n=2; n<=10; ++n)
        #pragma omp atomic
            fac *= n; // This operation is done atomically on shared variable
    printf("Fact 10 is %d, in seconds = %f\n", fac, omp_get_wtime() - start);
    // For loops with iterations known a-priori

    fac = 1;
    start = omp_get_wtime();
    printf("(Faster) Reduction can be used to build private copy, parallelise, merge private copies. Usage <reduction(operator:list)>\n");
    #pragma omp parallel for reduction(*:fac)
    for(int n=2; n<=10; ++n)
        fac *= n;
    printf("Fact 10 is %d, in seconds = %f\n", fac, omp_get_wtime() - start);

    // Reduction is equivalent to:
    // int factorial(int number)
    // {
    // int fac = 1;
    // #pragma omp parallel
    // {
    //     int omp_priv = 1; /* This value comes from the table shown above */
    //     #pragma omp for nowait
    //     for(int n=2; n<=number; ++n)
    //     omp_priv *= n;
    //     #pragma omp atomic
    //     fac *= omp_priv;
    // }
    // return fac;
    // }


    /*Critical Construct*/
    printf("Critical construct helps to execute a block of code as critical section\n");
    int sum = 0, tid, sumLocal;
    int a[10];
    for(int i = 0; i < 10 ; a[i++] = 2);
    # pragma omp parallel shared (a,sum) private(tid,sumLocal)
    {
        tid = omp_get_thread_num();
        sumLocal = 0;
        #pragma omp for
            for(int i=0;i<10;i++)
                sumLocal += a[i];

        #pragma omp critical (update_sum) // name of the block
            sum += sumLocal; // mutual exclusion here (can also be done as atomic)
    }
    printf("sum = %d\n", sum);

    fac = 1;
    start = omp_get_wtime();
    printf("Default scheduling is static (least overhead)\n");
    #pragma omp parallel for schedule(static) reduction(*:fac)
    for(int n=2; n<=10; ++n)
        fac *= n; // This operation is done atomically on shared variable
    printf("Fact 10 is %d, in seconds = %f\n", fac, omp_get_wtime() - start);

    fac = 1;
    start = omp_get_wtime();
    printf("static with smaller chunk size (default = 1)\n");
    #pragma omp parallel for schedule(static, 1) reduction(*:fac)
    for(int n=2; n<=10; ++n)
        fac *= n; // This operation is done atomically on shared variable
    printf("Fact 10 is %d, in seconds = %f\n", fac, omp_get_wtime() - start);

    fac = 1;
    start = omp_get_wtime();
    printf("Dynamic (max overhead)\n");
    #pragma omp parallel for schedule(dynamic) reduction(*:fac)
    for(int n=2; n<=10; ++n)
        fac *= n; // This operation is done atomically on shared variable
    printf("Fact 10 is %d, in seconds = %f\n", fac, omp_get_wtime() - start);

    fac = 1;
    start = omp_get_wtime();
    printf("Guided - dynamic but chunk sizwe decreases over time\n");
    #pragma omp parallel for schedule(guided) reduction(*:fac)
    for(int n=2; n<=10; ++n)
        fac *= n; // This operation is done atomically on shared variable
    printf("Fact 10 is %d, in seconds = %f\n", fac, omp_get_wtime() - start);

    // schedule(runtime) -- the decision of scheduling strategy decided at runtime
    // default(none) -- The most useful purpose on the default clause is to check
    // whether you have remembered to consider all variables for the private/shared
    // question, using the default(none) setting.
    // The default clause can also be used to set that all variables are shared by
    // default (default(shared)).

    // #pragma omp for collapse(2) can collapse nested loops to expose parallelism

    // #pragma omp for ordered with #pragma omp ordered{} used to make sure that the ordered
    // block of code runs in the specified loop order only
}
