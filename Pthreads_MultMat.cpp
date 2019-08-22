#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <vector> 
using namespace std;

#define NumThreads 4

typedef struct blocosoma {
    int posx;
    int posy;
    vector<int> valx;
    vector<int> valy;
    int* mat;
} blocosoma;

void* somaM(void* threadid){
    blocosoma* Op;
    Op = (blocosoma*) threadid;
    int x = 0;
    
    for(int i=0; i < (Op->valx.size());i++){
        x+=Op->valx[i]*Op->valy[i];   
    }
    //encontrar a posicao na matriz
    int pos = 0;
    pos +=(Op->posx * (NumThreads/2)) + Op->posy; 
    //calculando valor de memoria para a casa da matriz
    //  cout<<"-"<<pos<<"p\n";
    *((Op->mat) + (pos)) = x;
    //  printf("%d\n",x);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NumThreads];
    int rc;
    int m1[NumThreads/2][NumThreads/2];
    int m2[NumThreads/2][NumThreads/2];
    int mr[NumThreads/2][NumThreads/2];
    blocosoma* t;
   // int t;
    m1[0][0] = 2;
    m1[0][1] = 7;
    m1[1][0] = 5;
    m1[1][1] = 2;
    m2[0][0] = 3;
    m2[0][1] = 3;
    m2[1][0] = 1;
    m2[1][1] = 2;
    
    int numT=0;
    vector<int> linhax;
    vector<int> colunay;
    
    
    for(int i=0;i<NumThreads/2;i++){
        
     for(int j=0;j<NumThreads/2;j++){
            t = new blocosoma;
          
            for(int y=0;y<NumThreads/2;y++){
                //pegar linha x
                t->valx.push_back(m1[i][y]);
                //pegar coluna y
                t->valy.push_back(m1[y][j]);
            }
            t->posx = i;
            t->posy = j;
            t->mat = &mr[0][0];
            rc = pthread_create(& threads[numT], NULL, somaM, (void * ) t);
                        //cout<<numT<<" = num T\n";

            numT++;
            if (rc) {
              cout << "ERROR:" << rc << '\n';
              return(-1);
            }
        }   
    }
    
    for(pthread_t t : threads){
        pthread_join(t,NULL);
    }
        
    cout<<"Matriz 1 ="<<endl;
    for(int i = 0;i<NumThreads/2;i++ ){
        for(int j = 0;j<NumThreads/2;j++ ){
            cout<<m1[i][j]<< "  ";
        }
        cout<<endl;
    }
    
    cout<<"Matriz 2 ="<<endl;
    for(int i = 0;i<NumThreads/2;i++ ){
        for(int j = 0;j<NumThreads/2;j++ ){
            cout<<m2[i][j]<< "  ";
        }
        cout<<endl;
    }    
    cout<<"sua matriz resultado eh"<<endl;
    for(int i = 0;i<NumThreads/2;i++ ){
        for(int j = 0;j<NumThreads/2;j++ ){
            cout<<mr[i][j]<< "  ";
        }
        cout<<endl;
    }
    pthread_exit(NULL);
        return 0;
}
