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
         
       int *mat1 = &m1[0][0];
       int *mat2 = &m2[0][0];
         
      //sprintf(msg, "Processo #%d em execucao!", rank);
     //  int x = (rank-1)%n;
        //  int y = ceil((rank-1)/n);
        printf("%d - rank \n", rank);
        //Pegar linha e coluna. multiplicar e somar // 
        //  
          /*for(int i =0; i<n*n;i+=n){
            for(int j =0; j<n;j++){
                    printf("%d \n",*(mat1+i+j));
                    
            }    
          }*/
          printf("%d", rank/2);
          
              
          int linha = floor((rank-1)/n) ;
          
          int coluna = (n - (rank%n))-1;
          msg[0] =0;
          for(int i=0; i<n;i++){
              msg[0] += (* (mat1+(linha*n)+i)) * (*((mat2+coluna)+i*n)); 
             
                  printf("Em %d -- linha = %d, coluna = %d, i = %d, msg = %d",rank, linha,coluna,i,msg[0]);
              
          }

          printf("%d\n",msg[0]);

          //rank 1 - linha 0, rank 2 - linha 0, rank 3 linha 1, rank 4 linha 1
          //1 - coluna 0, 2 coluna 1, 3 coluna 0, 4 coluna 1 -> (n - rank%n)-1
        
        
      //  msg[0]  = (* (mat1 + rank-1)) + (* (mat2 + rank-1));
        target = 0; 

        MPI_Send(msg, 1, MPI_INT, target, tag, MPI_COMM_WORLD);
    } else {
        int x;
        int y;
        int *mat3 = &m3[0][0];
        for (source = 1; source < num_procs; source++) {
            MPI_Recv(msg,2*sizeof(msg), MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
            printf("Processo %d -- %d \n",source, msg[0]);
         /*   x = (source-1)%n;
            y = floor((source-1)/n);
            m3[x][y] = msg[0];
            */
            *(mat3+(source-1)) = msg[0];
        }
        for(int i =0; i<n ;i++){
            for(int j=0; j<n;j++){
                printf("%d ", m3[i][j]);
            }
            printf("\n");
        }

      //  printf("a %d", (*(&m1 + 3)));

    }
    
    MPI_Finalize();
    
    return 0;
}
