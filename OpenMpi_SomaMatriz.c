#include <mpi.h>
#include <stdio.h>
#include <string.h> 
#include <math.h>
#define n  2//dimensao da matriz

int main (int argc, char *argv[]) {
    int rank; int num_procs; int source, target; MPI_Status status;
    int tag = 0;
   // char msg[256];
     int msg[1];
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    //int n = 2;//dimensao da matriz
    int m1[n][n] = {{1,2},{3,4}};
    int m2[n][n] = {{1,2},{3,4}};
    int m3[n][n];
    int a = 1;
// 4-> 1 -> [0][0] 2 ->[0][1] 3->[1][0] 4->[1][1]
    if (rank != 0) {
        a=2;
       
        //sprintf(msg, "Processo #%d em execucao!", rank);
        int x = (rank-1)%n;
        int y = ceil((rank-1)/n);
        printf("%d - rank \n", rank);
        printf("Operacao: %d + %d \n",m1[x][y], m2[x][y]);
        msg[0]  = m1[x][y] + m2[x][y];
        target = 0; 

        MPI_Send(msg, 1, MPI_INT, target, tag, MPI_COMM_WORLD);
    } else {
      
        int x;
        int y;
        for (source = 1; source < num_procs; source++) {
            MPI_Recv(msg,2*sizeof(msg), MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
            printf("Processo -- %d \n", msg[0]);
            x = (source-1)%n;
            y = ceil((source-1)/n);
            m3[x][y] = msg[0];

        }
        
        for(int i =0; i<n ;i++){
            for(int j=0; j<n;j++){
                printf("%d ", m3[i][j]);
            }
            printf("\n");
        }

        printf("a %d", a);

    }
    
    MPI_Finalize();
    
    return 0;
}
