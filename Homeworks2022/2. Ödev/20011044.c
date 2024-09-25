#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX 64

typedef struct{
	char item[MAX];
	int top;
}STACK;

void decimaltoBinary(long long n);
void initStack(STACK* s);
void push(char x, STACK* s);

int main(){
	
	long long n;
	int a;
	
	do{
		
		printf("Menu: \n1-Decimal to Binary \n2-Cikis \n");
		scanf("%d",&a);
		
		if(a==1){
			printf("10'luk sistemde bir tam sayi giriniz: ");
			scanf("%lld", &n);
			printf("\n");
			printf("%lld = ", n);
			decimaltoBinary(n);
		}
		
	}while(a!=2);

return 0;
}

void decimaltoBinary(long long n){
	
	STACK* s=(STACK*)malloc(sizeof(STACK));
	int a,msb,i,k;
	
	if( n > 0 ){
		a = ceil(log2(n+1));                                     // Pozitif tam sayilar icin gereken en az bit sayisi. Orn: 2^9 --> 10
	}else if(n < 0){
		a = log2(-n) + 1;                                        // Negatif tam sayilar icin gereken en az bit sayisi. Orn:2^-7 --> 8
	}else{
		a = 1;                                                   // 0 Sayisi icin gereken bit sayisi 1'dir.
	}
	
	if( (a%8) == 0){
		msb = a-1;                                               // Gereken en az bit sayisi 8 ve katlarindan biri degilse
	}else{                                                       // kendisinden buyuk en kucuk 8'in kati kadar yer acar.
		msb = (a/8)+1;                                           // 8 --> 8 , 9 --> 16 , 15 --> 16
		msb *= 8;
		msb--;                                                   // msb : en yuksek bitin indisi. Orn: 8 bitli bir sayida msb=7
	}
	
	char str[msb+1];                                             // Gereken bit sayisi kadar yer string'te açilir.

	for(i=msb ; i>=0 ; i--){
		
		if((i%4)==3){
			printf(" ");                                         // Kolay okunmasi icin her 4 bitte bir bosluk koyulmustur.
		}
		
		k = n >> i;                                              // Sirayla her bitteki sayi shift right islemiyle 0. bite getirilir.

		if(k & 1){                                               // 0. Bitteki degere gore string'e aktarilir.
			str[msb-i]='1';
			printf("1");
		}else{
			str[msb-i]='0';
			printf("0");
		}
			
	}
	
	printf("\n");
	
	initStack(s);
	
	for(i=0;i<=msb;i++){
		if(str[i]=='1'){
			push(str[i],s);                                      // String'te her 1 degeri okundugunda Stack'e push edilir.
		}
	}
	
	int yari;
	yari = (msb+1)/2;
	
	if( (s->top) == yari ){
		printf("0 ve 1'ler esit sayidadir.");
	}else if( (s->top) > yari ){
		printf("1'ler fazladir. Ek %d adet 0 gereklidir.",2*s->top-(msb+1));  // 2*s->top-(msb+1) --> 1'lerin 0'lardan farki
	}else{
		printf("0'lar fazladir. Ek %d adet 1 gereklidir.",(msb+1)-2*s->top);  // (msb+1)-2*s->top --> 0'larin 1'lerden farki
	}

	printf("\n----------------------------------------------\n");

}

void push(char x, STACK* s){
	
	if(isFull(s)){
		return;
	}else{
		s->item[s->top] = x;
		s->top++;
		return;
	}
}

void pop(STACK* s, char *x){
	
	if(isEmpty(s)){
		return;
	}else{
		s->top--;
		*x = s->item[s->top];
		return;
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
