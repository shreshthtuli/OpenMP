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

    printf("Sections for work sharing\n");
    int x = 0, y = 0, z = 0;
    #pragma omp parallel sections
    {
        #pragma omp section
            x++;
        #pragma omp section
            y++;
        #pragma omp section
            z++;
    } // Implicit barrier here
    printf("x = %d, y = %d, z = %d\n", x, y, z);

    // Assignment of code blocks to threads is implementationdependent

    // When for and sections are too cumbersome, the task construct can be
    // used. This is only supported in OpenMP 3.0 and later. Example code:

    // struct node { node *left, *right; };
    // extern void process(node* );
    // void traverse(node* p)
    // {
    //     if (p->left)
    //         #pragma omp task // p is firstprivate by default
    //         traverse(p->left);
    //     if (p->right)
    //         #pragma omp task // p is firstprivate by default
    //         traverse(p->right);
    //     process(p);
    // }

    // Task synchronization: either by #pragma omp barrier or by #pragma omp taskwait
    // taskwait: explicit wait on the completion of child tasks
    // depend (OUT:x) for dependency

    // The flush directive can be used to ensure that the value observed in one
    // thread is also the value observed by other threads

    /* presumption: int a = 0, b = 0; */

    // Example:
                        
    // /* First thread */                /* Second thread */
    // b = 1;                            a = 1;
    // #pragma omp flush(a,b)            #pragma omp flush(a,b)
    // if(a == 0)                        if(b == 0)
    // {                                 {
    //   /* Critical section */            /* Critical section */
    // }                         
}
