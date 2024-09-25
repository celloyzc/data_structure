#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct{
	int item[MAX];
	int top;
}STACK;

int main(){
	
}

int push(int x, STACK* s){
	
	if(isFull(s)){
		return 0;
	}else{
		s->item[s->top] = x;
		s->top++;
		return 1;
	}
}

int pop(STACK* s, int *x){
	
	if(isEmpty(s)){
		return 0;
	}else{
		s->top--;
		*x = s->item[s->top];
		return 1;
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
