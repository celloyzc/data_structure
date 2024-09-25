#include <stdio.h>
#include <string.h>

#define N 10
#define EBAS 9999

int GRAF[N][N];
int EKM[N];
char ROTA[N][N] = {NULL};

void Dijkstra();

void Dijkstra() {
	char *ptr,ELEALINDI[N]={0};
	int i,j,ead,ek;
  
	EKM[0]=0;
	for(i=1;i<N;i++){
  		EKM[i] = EBAS;
	}
	ead=0;
  
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
  			if(!ELEALINDI[j])
  				if(GRAF[ead][j] != -1)
  					if(EKM[j] > GRAF[ead][j] + EKM[ead]){
  						EKM[j] = GRAF[ead][j] + EKM[ead];
  						strcpy(ROTA[j],ROTA[ead]);
  						ptr = ROTA[j];
  						while(*ptr != NULL)
  							ptr++;
  						*ptr = 'A' + ead;
  						
					}
		}
		ek = EBAS;
		for(j=0;j<N;j++){
			if(!ELEALINDI[j])
				if(EKM[j] < ek){
					ek = EKM[j];
					ead = j;
				}
		}
		ELEALINDI[ead] = 1;
	}

  
}
int main() {
	
	int graph[N][N] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 14, 10, 0, 2, 0, 0},
                       {0, 0, 0, 0, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}};
  
  return 0;
}
