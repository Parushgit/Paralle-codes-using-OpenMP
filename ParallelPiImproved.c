#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
static long num_steps = 100000; double step;

#define NUM_THREADS 2
void main()
{
    double pi=0.0; int t;
    struct timeval start, end;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    //double exec_time;
    gettimeofday(&start, NULL);
    //exec_time = omp_get_wtime();
   
    //printf("Time before : %lf\n", exec_time);
    #pragma omp parallel
    {
    int i,nthreads, id,nthrds;
    double x,sum;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    if (id == 0) {
        nthreads = nthrds;
    }
    //printf("Thread value : %d\n", nthrds);
    for (i=id, sum = 0.0;i< num_steps; i=i+nthrds) {
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
    }
    #pragma omp critical
    pi+=sum * step;
    }
    //printf("Time after : %lf\n", exec_time);
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
    end.tv_usec - start.tv_usec) / 1.e6;
    printf("Time before : %lf\n", delta);
    //for(i=0, pi=0.0;i<nthreads;i++)pi += sum[i] * step;
    printf("The value of PI : %lf\n", pi);
}