#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <vector> 
using namespace std;

#define TAMMATRIZ 5

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
    bool x = false;
    
    for(int i=0; i < (Op->valx.size());i++){
    
        x = x||(Op->valx[i] && Op->valy[i]);   
    
        
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
     cout<<endl<<endl;
    cout<<"Matriz 2 ="<<endl;
    for(int i = 0;i<TAMMATRIZ;i++ ){
        for(int j = 0;j<TAMMATRIZ;j++ ){
            cout<<m2[i][j]<< "  ";
        }
        cout<<endl;
    }    
     cout<<endl;
    cout<<"sua matriz resultado eh"<<endl;
    for(int i = 0;i<TAMMATRIZ;i++ ){
        for(int j = 0;j<TAMMATRIZ;j++ ){
            cout<<mr[i][j]<< "  ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    //  cout<<"OPAA"<<endl;
    //pthread_exit(NULL);
   // cout<<"OPAA"<<endl;
      
      return 0;
}


void FechamentoTransitivo(int adj[][TAMMATRIZ],int path[][TAMMATRIZ]){
    
    int newprod[TAMMATRIZ][TAMMATRIZ],adjprod[TAMMATRIZ][TAMMATRIZ],DistanciaMinima[TAMMATRIZ][TAMMATRIZ];
    
    for(int i = 0; i<TAMMATRIZ; i++){//inicializa as matrizes
        for(int j = 0; j<TAMMATRIZ; j++){
            adjprod[i][j]  =  path[i][j] = adj[i][j];
            if(adj[i][j] == 1){
                DistanciaMinima[i][j] = 1;    
            }
            else if(i == j){
                DistanciaMinima[i][j] = 0;
            }
            else
            DistanciaMinima[i][j] = -1;
            
        }
    }
    
    for(int i=0; i<TAMMATRIZ; i++){
        MultMatriz(adjprod,adj,newprod);
          
        for(int j=0; j<TAMMATRIZ; j++){
            for(int k=0; k<TAMMATRIZ; k++){
                path[j][k] = path[j][k]||newprod[j][k];
                if(path[j][k]!=0 && DistanciaMinima[j][k] < 0){
                    DistanciaMinima[j][k] = i+2;
                }
                
            }
        }
        for(int j=0; j<TAMMATRIZ; j++){
            for(int k=0; k<TAMMATRIZ; k++){
              adjprod[j][k] = newprod[j][k];
            }
        }
       
        cout<<"PATH - "<<i<<endl;
        
        for(int x = 0;x<TAMMATRIZ;x++ ){
        for(int y = 0;y<TAMMATRIZ;y++ ){
            cout<<path[x][y]<< "  ";
        }
        cout<<endl;
        }
        cout<<endl<<endl;
    }
    
    
    cout<<"Distancia Minima - "<<endl;
    
    for(int x = 0;x<TAMMATRIZ;x++ ){    
    for(int y = 0;y<TAMMATRIZ;y++ ){
        cout<<DistanciaMinima[x][y]<< "  ";
    }
    cout<<endl;
    }
    cout<<endl<<endl;
    
}

int main(){
   
    int m1[TAMMATRIZ][TAMMATRIZ];
    int path[TAMMATRIZ][TAMMATRIZ];
    //int mr[TAMMATRIZ][TAMMATRIZ];
    
   // int t;
    
   for(int i=0;i<TAMMATRIZ;i++){
       for(int j=0;j<TAMMATRIZ;j++){
           path[i][j]=0;
           m1[i][j]=0;
       }
   }
   
   
   m1[0][2] = 1;
   m1[0][3] = 1;
   m1[1][2] = 1;
   m1[2][3] = 1;
   m1[2][4] = 1;
   m1[3][4] = 1;
   m1[4][3] = 1;
   
   
   
   
   
   
   
    FechamentoTransitivo(m1,path);
   // MultMatriz( m1,m2,mr);
    return 0;
}
