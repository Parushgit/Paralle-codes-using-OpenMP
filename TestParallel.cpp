#include <stdio.h>
#include <omp.h>

void prefix_sum(int a[], int s[], int n) {
    int *suma;
    #pragma omp parallel
    {
        const int ithread = omp_get_thread_num();
        const int nthreads = omp_get_num_threads();
        #pragma omp single
        {
            suma = new int[nthreads+1];
            suma[0] = 0;
        }
        int sum = 0;
        #pragma omp for schedule(static) nowait // do partial sum in parallel
        for(int i=0; i<n; i++) {
            sum += a[i];
            s[i] = sum;
        }
        suma[ithread+1] = sum;
        #pragma omp barrier
        int offset = 0;
        for(int i=0; i<(ithread+1); i++) {
            offset += suma[i];
        }

        #pragma omp for schedule(static) //run over array again in parallel for full sum
        for(int i=0; i<n; i++) {
            s[i] += offset;
        }
    }
    delete[] suma;
}

int main() {
    const int n = 100;
    int *a = new int[n];
    int *s = new int[n];
    for(int i=0; i<n; i++) {
        a[i] = i;
    }
    prefix_sum(a, s, n);
    for(int i=0; i<n; i++) {
        printf("%d ", s[i]);
    } printf("\n");

    for(int i=0; i<n; i++) {
        printf("%d ", i*(i+1)/2);
    } printf("\n");
}