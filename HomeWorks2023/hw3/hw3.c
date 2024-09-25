#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i ;
    int right = 2*i + 1;
    //`left` ve `right`, mevcut d���m�n sol ve sa� �ocuklar�n� i�aret eder.
    //E�er �ocuklardan biri mevcut d���mden b�y�kse, `largest` g�ncellenir.
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n) {
	int i;
    for ( i = n / 2 ; i >= 0; i--)
        maxHeapify(arr, n, i);
}
//Dizinin tamam�n� max-heap yap�s�na �evirir

int extractMax(int arr[], int* n) {
    if (*n == 0)
        return -1;// E�er kuyruk bo�sa, -1 d�ner.
    
    int max = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    maxHeapify(arr, *n, 0); // Yeniden max-heap �zelli�ini sa�lamak i�in maxHeapify �a��r�l�r.
    return max;// ��kar�lan en b�y�k eleman� d�nd�r�r.
}

int main() {
    int N, M;
    printf("Matrisin satir boyutunu giriniz (N): ");
    scanf("%d", &N);

    int capacities[N];
    int i,j;
    printf("Her bir kuyruk kapasitesini giriniz:(Yani Matrisin sutun boyutu) \n");
    for ( i = 0; i < N; i++) {
    	printf("%d. kuyruk kapasitesi: ",i+1);
        scanf("%d", &capacities[i]);
    }
    
    int maxCap = 0;
    for ( i = 0; i < N; i++) {
        if (capacities[i] > maxCap)
            maxCap = capacities[i];
    }
    
    M = maxCap;
    //Matrisin s�tun boyutuna maksimum kapasite de�erini at�yor.
    int matrix[N][M];
    srand(time(NULL));
    
    int K = N * M;
    int numbers[K];
    for (i = 0; i < K; i++) {
        numbers[i] = i;
    }
    //Rastgele say�lar �retir.
    for ( i = 0; i < K; i++) {
         j = rand() % (i + 1);
        swap(&numbers[i], &numbers[j]);
    }
    //Rastgele say�lar� kar��t�r�r.
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            if (j < capacities[i]) {
                matrix[i][j] = numbers[i * M + j];
            } else {
                matrix[i][j] = -1;
            }
        }
    }
    //�lk olu�an matrisi yazd�r�r.
    printf("Baslangic Matrisi:\n");
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    //Her kuyruk i�in max-heap olu�turur ve Max-heap �zelli�ine g�re d�zenlenmi� matrisi yazd�r�r
    for ( i = 0; i < N; i++) {
        buildMaxHeap(matrix[i], capacities[i]);
    }
    
    printf("Max-Heap Matrisi:\n");
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    

    int emptyQueues[N], emptyCount = 0; // Bo�alan kuyruklar� saklamak i�in dizi ve saya�.
    int adim = 0; // ��lem ad�mlar�n� saymak i�in saya�.

    while (emptyCount < N) {
        int maxElement = -1;
        int maxQueue = -1;

        for ( i = 0; i < N; i++) {
            if (capacities[i] > 0 && matrix[i][0] > maxElement) {
                maxElement = matrix[i][0];// Mevcut en b�y�k eleman� bul.
                maxQueue = i;// Hangi kuyruktan geldi�ini kaydet.
            }
        }

        if (maxQueue == -1) return;// E�er hi� kuyruk kalmad�ysa d�ng�den ��k.

        printf("Secilen eleman: %d\n", maxElement);
        extractMax(matrix[maxQueue], &capacities[maxQueue]);

        if (capacities[maxQueue] == 0) {
            emptyQueues[emptyCount++] = maxQueue;// E�er kuyruk bo�ald�ysa, dizide saklar.
            printf("Kuyruk %d bosaldi.\n", maxQueue);// Hangi kuyru�un bo�ald� bilgisini yazd�r�r.
        }

        printf("Matrisin yeni hali:\n");
        for ( i = 0; i < N; i++) {
            for ( j = 0; j < M; j++) {
                if (j < capacities[i])
                    printf("%d ", matrix[i][j]);
                else
                    printf("-1 "); // Kapasite dolduysa -1 yazd�r�r.
            }
            printf("\n");
        }

        adim++;
    }

    printf("Bosalan kuyruklar: ");// Bo�alan kuyruklar� listele.
    for ( i = 0; i < emptyCount; i++) {
        printf("%d ", emptyQueues[i]);
    }
    printf("\n");

    
    return 0;
}

