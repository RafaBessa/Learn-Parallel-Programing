#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <vector> 
using namespace std;

#define TAMMATRIZ 2

typedef struct blocosoma {
    int posx;
    int posy;
    vector<int> valx;
    vector<int> valy;
    int* mat;
} blocosoma;

void* TMultMatriz(void* threadid){
    blocosoma* Op;
    Op = (blocosoma*) threadid;
    int x = 0;
    
    for(int i=0; i < (Op->valx.size());i++){
        x+=Op->valx[i]*Op->valy[i];   
    }
    //encontrar a posicao na matriz
    int pos = 0;
    pos +=(Op->posx * (TAMMATRIZ)) + Op->posy; 
    //calculando valor de memoria para a casa da matriz
    //  cout<<"-"<<pos<<"p\n";
    *((Op->mat) + (pos)) = x;
    //  printf("%d\n",x);
    pthread_exit(NULL);
}

int MultMatriz(int m1[][TAMMATRIZ],int m2[][TAMMATRIZ],int mr[][TAMMATRIZ]){
    
    pthread_t threads[TAMMATRIZ*TAMMATRIZ];
    int rc;
    blocosoma* t;
    
    int numT=0;
    for(int i=0;i<TAMMATRIZ;i++){
     for(int j=0;j<TAMMATRIZ;j++){
            t = new blocosoma;
            for(int y=0;y<TAMMATRIZ;y++){
                //pegar linha x
                t->valx.push_back(m1[i][y]);
                //pegar coluna y
                t->valy.push_back(m1[y][j]);
            }
            t->posx = i;
            t->posy = j;
            t->mat = &mr[0][0];
            rc = pthread_create(& threads[numT], NULL, TMultMatriz, (void * ) t);
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
      cout<<"Mult:"<<endl;
        cout<<"Matriz 1 ="<<endl;
    for(int i = 0;i<TAMMATRIZ;i++ ){
        for(int j = 0;j<TAMMATRIZ;j++ ){
            cout<<m1[i][j]<< "  ";
        }
        cout<<endl;
    }
    
    cout<<"Matriz 2 ="<<endl;
    for(int i = 0;i<TAMMATRIZ;i++ ){
        for(int j = 0;j<TAMMATRIZ;j++ ){
            cout<<m2[i][j]<< "  ";
        }
        cout<<endl;
    }    
    cout<<"sua matriz resultado eh"<<endl;
    for(int i = 0;i<TAMMATRIZ;i++ ){
        for(int j = 0;j<TAMMATRIZ;j++ ){
            cout<<mr[i][j]<< "  ";
        }
        cout<<endl;
    }
    pthread_exit(NULL);
      
      
}


int main(){
   
    int m1[TAMMATRIZ][TAMMATRIZ];
    int m2[TAMMATRIZ][TAMMATRIZ];
    int mr[TAMMATRIZ][TAMMATRIZ];
    
   // int t;
    m1[0][0] = 1;
    m1[0][1] =3;
    m1[1][0] = 5;
    m1[1][1] = 2;
    m2[0][0] = 1;
    m2[0][1] = 7;
    m2[1][0] = 12;
    m2[1][1] = 1;
    
    MultMatriz( m1,m2,mr);
    return 0;
}
