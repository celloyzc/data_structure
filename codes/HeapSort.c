#include <stdio.h>
#define MAX 100

void HeapSort(int* data, int  , int count);
void MaxHeapify(int* data, int heapSize, int index , int begin);

int main(){
	int data[MAX];
	int sayac,i;
	
	srand(time(NULL));
	for(i=0 ; i<MAX ; i++){
		data[i] =1+rand()%100;
		//printf("%d - " , data[i]);
	}
	
	HeapSort(data , 0 , MAX-1);
	
	for(i=0 ; i<MAX ; i++){
		printf("%d\t" , data[i]);
	}
	
}

void MaxHeapify(int* data, int heapSize, int index , int begin) {
	int left = 2*index + 1;                          // Üçgen kurulur
	int right = 2*index + 2;
	int largest = 0;
	int temp;
	int i;
	

	if (left < heapSize && data[begin+left] > data[begin+index])
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[begin+right] > data[begin+largest])
		largest = right;

	if (largest != index)                                                      //en büyük sayý üçgenin üstüne gelir
	{
		temp = data[begin+index];
		data[begin+index] = data[begin+largest];
		data[begin+largest] = temp;
		
	

		MaxHeapify(data, heapSize, largest , begin);
	}
}

void HeapSort(int* data, int begin , int end) {
	int heapSize = end-begin+1;
	int p , i , j , temp;

	for (p = (heapSize-1 ) / 2 ; p >= 0 ; p--)                             //Döngü tamamlandýðýnda herhangi bir sayý kendisinden büyük bir sayýnýn üstünde bulunmaz.
		MaxHeapify(data, heapSize, p,0);

	for (i = end-begin ; i > 0 ; i--)
	{
		
		temp = data[i];
		data[i] = data[0];
		data[0] = temp;
		
		heapSize--;
		MaxHeapify(data, heapSize, 0 , begin);
	}
	
}
