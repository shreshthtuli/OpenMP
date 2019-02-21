#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <string>

int main(){

    int fac = 1;
    printf("#pragma omp parallel for is for for loops\n");
    #pragma omp parallel for
    for(int n=2; n<=10; ++n)
        fac *= n; // This operation is done atomically on shared variable
    printf("Fact 10 is %d\n", fac);

    fac = 1;
    printf("(Faster) Reduction can be used to build private copy, parallelise, merge private copies. Usage <reduction(operator:list)>\n");
    #pragma omp parallel for reduction(*:fac)
    for(int n=2; n<=10; ++n)
        fac *= n;
    printf("Fact 10 is %d\n", fac);

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
}
