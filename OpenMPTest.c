#include<stdio.h>
#include<stdlib.h>
#include<omp.h>



int main()
{
    static long num_steps = 100000;
    double step, pi;
    double A[1000];
    double exec_time;
    exec_time = omp_get_wtime();
    printf("Time before : %lf\n", exec_time);
    double sum = 0.0;
    #pragma omp parallel num_threads(10000)
    {
    int ID = omp_get_thread_num();
    printf("ID %d\n", ID);
    // printf("World %d\n", ID);

    int i; double x;
    step = 1.0/(double) num_steps;
    for(i=0;i<num_steps;i++)
    {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    //foobar();
    }
    pi = step*sum;
    printf("PI Value: %lf\n", pi);
    printf("Time after : %lf\n", exec_time);
    return 0;
}

//vagrant box add hashicorp/precise64