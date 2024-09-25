#include <stdio.h>
#define MAX 15

void MaxHeapify(int* data, int heapSize, int index);
void build_maxHeap(int* data, int begin , int end);

int main(){
	int data[MAX];
	int sayac,i;
	
	srand(time(NULL));
	for(i=0 ; i<MAX ; i++){
		data[i] =1+rand()%100;
		//printf("%d - " , data[i]);
	}
	
	build_maxHeap(data , 0 , MAX-1);
	
	for(i=0 ; i<MAX ; i++){
		printf("%d\t" , data[i]);
		
	}
	
	
}

void MaxHeapify(int* data, int heapSize, int index) {
	int left = 2*index + 1;                          // Üçgen kurulur
	int right = 2*index + 2;
	int largest = 0;
	int temp;
	int i;
	

	if (left < heapSize && data[left] > data[index])
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[right] > data[largest])
		largest = right;

	if (largest != index)                                                      //en büyük sayý üçgenin üstüne gelir
	{
		temp = data[index];
		data[index] = data[largest];
		data[largest] = temp;
		
	

		MaxHeapify(data, heapSize, largest);
	}
}

void build_maxHeap(int* data, int begin , int end) {
	int heapSize = end-begin+1;
	int p , i , j , temp;

	for (p = (heapSize-1 ) / 2 ; p >= 0 ; p--)                             //Döngü tamamlandýðýnda herhangi bir sayý kendisinden büyük bir sayýnýn üstünde bulunmaz.
		MaxHeapify(data, heapSize, p);
		
}
