// MIT License

// Copyright (c) 2019 Shreshth Tuli

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    int num, tid;
    printf("Part 1 barrier\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region and private when declared inside
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
        #pragma omp single nowait// implicit barrier overridden
            num = omp_get_num_threads();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

    // Unless you use the threadprivate clause, the only important difference between single,
    // nowait and master is that if you have multiple master blocks in a parallel section, you
    // are guaranteed that they are executed by the same thread every time, and hence, the values 
    // of private (thread-local) variables are the same.

    // single with copyprivate(<var name>) broadcasts thread private var value to others

    printf("Part 5 single with copyprivate(<var name>) broadcasts thread private var value to others\n");
    num = 0, tid = 0;
    #pragma omp parallel private(tid) // Default is shared when declared outside parallel region
    {
        tid = omp_get_thread_num();
        #pragma omp single copyprivate(tid)
            num = omp_get_num_threads();
        printf("hello-world %d of %d\n", tid, num);
    } // Implicit barrier here

}
