#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct node{
	int data;
	struct node *next,*lower;
}NODE;

void addNode(NODE **head, int data);
void PrintList(NODE *head);

int main(){	
	int N , seviye , i , a , sayi;
	int* random;
	
	NODE** head=NULL;
	NODE* tmp=NULL;
	
	printf("Listenin eleman sayisini giriniz :");
	scanf("%d",&N);
	
	seviye = ceil(log2(N)) + 2;
	//printf("%d", seviye);
	
	head = (NODE**)malloc(seviye*sizeof(NODE*));
	
	for(i=0 ; i<N ; i++){
		printf("%d. elemani giriniz :" , i+1);
		scanf("%d",&a);
		addNode(&head[0],a);
		
	}
	
	
	
	for(i=0 ; i<seviye ; i++){
		addNode(&tmp,-(seviye-i));
	}
	
	sayi = (N+1)/2;
	random = (int*)malloc(sayi*sizeof(int));
	makingRandomArray(random,N);
	
	for(i=0 ; i<sayi ; i++){
		printf("%d",random[i]);
	}

	//PrintList(head[0]);
	//PrintList(tmp);

	
}void makingRandomArray(int random[],int N){
	
	int sayi,i,j,yok,a;
	
	sayi = (N+1)/2;
	
	srand(time(NULL));
	
	random[0]=rand()%N;
	
	for(i=1; i<sayi; i++){
		yok=1;                            //yok=1 ---> sayi yok
		a=rand()%N; 
		for(j=0;j<i;j++){
			if(random[j]==a){	
				yok=0;
			}
		}
		if(yok==1){
			random[i]=a;	
		}
		else{
			i--;	
		}
	}

	
}

NODE* getNode(int data){
	NODE *newNode=(NODE*) malloc(1*sizeof(NODE));
	newNode->data=data;
	newNode->next=NULL;	
	return newNode;
}

void addNode(NODE **head, int data){
	NODE *tmp;
	NODE *newNode=getNode(data);
	
	if(*head==NULL){
		*head=newNode;
	}
	else{
		tmp = *head;
		while(tmp->next!=NULL){
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
	
}

void PrintList(NODE *head){
	NODE *tmp=head;
	while(tmp!=NULL){
		printf("%d ",tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

void PrintList2(){
	
}

void SearchElement(){
	
}

void InsertElement(){
	
}

void DeleteElement(){
	
}
