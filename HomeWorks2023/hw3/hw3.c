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
    //`left` ve `right`, mevcut düðümün sol ve sað çocuklarýný iþaret eder.
    //Eðer çocuklardan biri mevcut düðümden büyükse, `largest` güncellenir.
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
//Dizinin tamamýný max-heap yapýsýna çevirir

int extractMax(int arr[], int* n) {
    if (*n == 0)
        return -1;// Eðer kuyruk boþsa, -1 döner.
    
    int max = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    maxHeapify(arr, *n, 0); // Yeniden max-heap özelliðini saðlamak için maxHeapify çaðýrýlýr.
    return max;// Çýkarýlan en büyük elemaný döndürür.
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
    //Matrisin sütun boyutuna maksimum kapasite deðerini atýyor.
    int matrix[N][M];
    srand(time(NULL));
    
    int K = N * M;
    int numbers[K];
    for (i = 0; i < K; i++) {
        numbers[i] = i;
    }
    //Rastgele sayýlar üretir.
    for ( i = 0; i < K; i++) {
         j = rand() % (i + 1);
        swap(&numbers[i], &numbers[j]);
    }
    //Rastgele sayýlarý karýþtýrýr.
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            if (j < capacities[i]) {
                matrix[i][j] = numbers[i * M + j];
            } else {
                matrix[i][j] = -1;
            }
        }
    }
    //Ýlk oluþan matrisi yazdýrýr.
    printf("Baslangic Matrisi:\n");
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    //Her kuyruk için max-heap oluþturur ve Max-heap özelliðine göre düzenlenmiþ matrisi yazdýrýr
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
    

    int emptyQueues[N], emptyCount = 0; // Boþalan kuyruklarý saklamak için dizi ve sayaç.
    int adim = 0; // Ýþlem adýmlarýný saymak için sayaç.

    while (emptyCount < N) {
        int maxElement = -1;
        int maxQueue = -1;

        for ( i = 0; i < N; i++) {
            if (capacities[i] > 0 && matrix[i][0] > maxElement) {
                maxElement = matrix[i][0];// Mevcut en büyük elemaný bul.
                maxQueue = i;// Hangi kuyruktan geldiðini kaydet.
            }
        }

        if (maxQueue == -1) return;// Eðer hiç kuyruk kalmadýysa döngüden çýk.

        printf("Secilen eleman: %d\n", maxElement);
        extractMax(matrix[maxQueue], &capacities[maxQueue]);

        if (capacities[maxQueue] == 0) {
            emptyQueues[emptyCount++] = maxQueue;// Eðer kuyruk boþaldýysa, dizide saklar.
            printf("Kuyruk %d bosaldi.\n", maxQueue);// Hangi kuyruðun boþaldý bilgisini yazdýrýr.
        }

        printf("Matrisin yeni hali:\n");
        for ( i = 0; i < N; i++) {
            for ( j = 0; j < M; j++) {
                if (j < capacities[i])
                    printf("%d ", matrix[i][j]);
                else
                    printf("-1 "); // Kapasite dolduysa -1 yazdýrýr.
            }
            printf("\n");
        }

        adim++;
    }

    printf("Bosalan kuyruklar: ");// Boþalan kuyruklarý listele.
    for ( i = 0; i < emptyCount; i++) {
        printf("%d ", emptyQueues[i]);
    }
    printf("\n");

    
    return 0;
}

