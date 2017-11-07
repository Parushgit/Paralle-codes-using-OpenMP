#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include<sys/time.h>

static long num_steps = 100000; double step;
#define NUM_THREADS 1
void main ()
{ 
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int i, nthreads; double pi, sum[NUM_THREADS];
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    //double exec_time;
    //exec_time = omp_get_wtime();
    //printf("Time before : %lf\n", exec_time);
    #pragma omp parallel
    {
    int i, id,nthrds;
    double x;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    if (id == 0) {
        nthreads = nthrds;
    }
    //printf("Thread value : %d\n", nthrds);
    for (i=id, sum[id]=0.0;i< num_steps; i=i+nthrds) {
    x = (i+0.5)*step;
    sum[id] += 4.0/(1.0+x*x);
    }
    }
    //printf("Time before : %lf\n", exec_time);
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
    end.tv_usec - start.tv_usec) / 1.e6;
    printf("Time before : %lf\n", delta);
    for(i=0, pi=0.0;i<nthreads;i++)pi += sum[i] * step;
    printf("The value of PI : %lf\n", pi);
}