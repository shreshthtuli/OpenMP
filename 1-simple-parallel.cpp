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
