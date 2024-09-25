#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAKS_KENAR 100
#define MAX 20

typedef struct _kenar{
	int ilk;
	int son;
	int maliyet;
}KENAR;

typedef struct{
	int item[MAX];
	int top;
}STACK;

KENAR kenar[MAKS_KENAR],tmp;
int Gveri[MAKS_KENAR][MAKS_KENAR];


void Guncelle(int N);
void GrafiDolasDFS(int dugum , int *visited , int N , int son , int *flag , STACK *s);
void push(int x, STACK* s);
void pop(STACK* s, int *x);
void initStack(STACK* s);
int isEmpty(STACK *s);
int isFull(STACK* s);


int main(){
	
	FILE *fp;
	int t;
	int a,b,c;
	int kenar_sayisi;
	int i,j;
	
	fp = fopen("Sample_MST.txt","r");
	if (fp == NULL) {
        printf("no such file.");
        return 0;
    }
	
	t=0;
	
	while( fscanf(fp,"%d %d %d", &a, &b, &c) != EOF ){
		
		kenar[t].maliyet = a;
		kenar[t].ilk = b;
		kenar[t].son = c;
		t++;
	}
	
	kenar_sayisi = t;
	
	for(i=0 ; i<kenar_sayisi+1 ; i++)
		for(j=0 ; j<kenar_sayisi+1 ; j++)
			Gveri[i][j] = 0;
			
	for(i=0 ; i<kenar_sayisi ; i++){
		Gveri[kenar[i].ilk][kenar[i].son] = kenar[i].maliyet;
		Gveri[kenar[i].son][kenar[i].ilk] = kenar[i].maliyet;
	}
		
	
	Guncelle(kenar_sayisi);
	
	fclose(fp);
	
}

void Guncelle(int N){
	
	int a,b,i,j;
	int ilk,son,maliyet;
	int *visited;
	int flag = 0, max, vertex1,vertex2;
	int *flag_ptr = &flag;
	
	printf("Eklenecek kenarin ilk dugumunu giriniz :"); scanf("%d" ,&ilk);
	printf("Eklenecek kenarin son dugumunu giriniz :"); scanf("%d" ,&son);
	printf("Eklenecek kenarin maliyetini giriniz :"); scanf("%d" ,&maliyet);
	
	visited = (int*)calloc(N+1,sizeof(int));
	
	STACK* s=(STACK*)malloc(sizeof(STACK));
	initStack(s);
	
	GrafiDolasDFS(ilk,visited,N,son,flag_ptr,s);
	
	pop(s,&a);                                                        //stackteki dugum numaralari arasindaki kenarlardan en maliyetlisini bulma
	peek(s,&b);
	max = Gveri[a][b];
	vertex1 = a;
	vertex2 = b;
	while(!isEmpty(s)){
		pop(s,&a);
		peek(s,&b);
		if(max<Gveri[a][b]){
			max = Gveri[a][b];
			vertex1 = a;
			vertex2 = b;
		}
	}
	printf("\n");
	
	if(max > maliyet){
		
		printf("%d %d kenari %d %d kenariyla guncellenmistir.\n\n",vertex1,vertex2,ilk,son);
		i=0;
		while( (kenar[i].ilk != vertex1 || kenar[i].son != vertex2) && (kenar[i].ilk != vertex2 || kenar[i].son != vertex1) ){
			i++;
		}
		
		kenar[i].ilk = ilk;
		kenar[i].son = son;
		kenar[i].maliyet = maliyet;
	}else{
		printf("Guncelleme gerekmiyor.\n\n");
	}
	
	
	for(i=0 ; i<N-1 ; i++)                                              //sort islemi
		for(j=0 ; j<N-i-1 ; j++)
			if(kenar[j].maliyet > kenar[j+1].maliyet){
				tmp = kenar[j];
				kenar[j] = kenar[j+1];
				kenar[j+1] = tmp;
			}
	
	printf("Maliyet   Ilk  Son\n");                                     //print kismi
	for(i=0 ; i<N ; i++){
		printf(" %2d      %2d    %2d\n" , kenar[i].maliyet , kenar[i].ilk , kenar[i].son);
	}
	
}



void GrafiDolasDFS(int dugum , int *visited , int N , int son , int *flag , STACK *s){
	int i,a;
	
	visited[dugum] = 1;
	
	
	if (*flag == 0) {                             //bulunmadigi durumda push et
		push(dugum,s);
	}
		
	for(i=1 ; i<N+1 ; i++){
		if( Gveri[dugum][i] != 0 && visited[i] == 0)
			GrafiDolasDFS(i,visited,N,son,flag,s);
	}
	
	if( dugum!=son && *flag == 0 ){                 //yanlis rota oldugundan pop et
		pop(s,&dugum);
	}else{
		*flag = 1;                              //bulundu
	}


	return;
}

void push(int x, STACK* s){
	
	if(isFull(s)){
		return ;
	}else{
		s->item[s->top] = x;
		s->top++;
		return ;
	}
}

void pop(STACK* s, int *x){
	
	if(isEmpty(s)){
		return ;
	}else{
		s->top--;
		*x = s->item[s->top];
		return ;
	}
}

void initStack(STACK* s){

	s->top = 0;
}

int isEmpty(STACK *s){
	
	if(s->top == 0){
		return 1;
	}else{
		return 0;
	}
}

int isFull(STACK* s){
	
	if(s->top == MAX){
		return 1;
	}else{
		return 0;
	}
}

int peek(STACK* s, int *x){
	
	int adr;
	
	if(isEmpty(s)){
		return 0;
	}else{
		adr = s->top-1;
		*x = s->item[adr];
		return 1;
	}
}



