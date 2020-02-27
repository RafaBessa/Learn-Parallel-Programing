//gcc -fopenmp -o soma  SomaMatrixMp.c -lm
#include <stdio.h>
#include <omp.h>
#include <math.h>
#define n  2//dimensao da matriz

int main(int argc, char* argv[])
{
    int m1[n][n] = {{1,2},{3,4}};
    int m2[n][n] = {{1,2},{3,4}};
    int m3[n][n];
    
 //m 0 -> tt-1
 // x = num % total
 // y = floor (num / total)    
    #pragma omp parallel num_threads(n*n)
    {
        int num = omp_get_thread_num();
        int total = omp_get_num_threads();
        int x = num % n;        
        int y = (int) (floor( num / n));
        printf("%d %d\n", x,y);
        m3[x][y] = m1[x][y] + m2[x][y];
       //printf("Hello, world. %d %d\n",x,tt);
    }

    int i=0;
    int j=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d ",m3[i][j]);
        }
        printf("\n");
    }

    return 0;
}