#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define CACHE_CAPACITY 4
#define THRESHOLD 5

typedef struct Node {
    char *sayfa_adresi;
    int istek_sayisi;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct CacheBuffer {
    Node *head;
    Node *tail;
    int size;
} CacheBuffer;

CacheBuffer* createCacheBuffer() {
    CacheBuffer *cache = (CacheBuffer*)malloc(sizeof(CacheBuffer));
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
    return cache;
}

Node* createNode(char *address) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->sayfa_adresi = strdup(address);
    newNode->istek_sayisi = 1;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
// Cache buffer'a yeni bir d���m ekleme fonksiyonu
void addToCacheBuffer(CacheBuffer *cache, char *address) {
    Node *newNode = createNode(address);
    if (cache->size == 0) {
        cache->head = newNode;
        cache->tail = newNode;
    } else {
        newNode->next = cache->head;
        cache->head->prev = newNode;
        cache->head = newNode;
    }
    cache->size++;

    if (cache->size > CACHE_CAPACITY) {
        Node *temp = cache->tail;
        cache->tail = cache->tail->prev;
        cache->tail->next = NULL;
        free(temp->sayfa_adresi);
        free(temp);
        cache->size--;
    }
}
// Cache buffer'daki bir d���m� g�ncellemek i�in kullan�lan fonksiyon
void updateCacheBuffer(CacheBuffer *cache, Node *node) {
    node->istek_sayisi++;
	//�stek say�s� thresholdtan b�y�k de�ilse her update sonras� en ba�a atanmas�n 
    if (node != cache->head && node->istek_sayisi > THRESHOLD) {
    	
        if (node == cache->tail) {
            cache->tail = node->prev;
        }
        node->prev->next = node->next;
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        node->next = cache->head;
        node->prev = NULL;
        cache->head->prev = node;
        cache->head = node;
        
        printf("%s sayfa adresi, threshold de�erinin a��lmas� nedeniyle cache bufferin head ta��nd�.\n", node->sayfa_adresi);
    }
}
// Cache buffer'dan bir d���m� kald�rmak i�in kullan�lan fonksiyon
void removeFromCacheBuffer(CacheBuffer *cache, Node *node) {
    if (node == cache->head) {
        cache->head = node->next;
    }
    if (node == cache->tail) {
        cache->tail = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    free(node->sayfa_adresi);
    free(node);
    cache->size--;
}
// Cache buffer'� temizleme:Her ekleme yap�ld�ktan sonra temizlemek isteyip istemedi�imizi sorar.
void clearCacheBuffer(CacheBuffer *cache) {
    Node *current = cache->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current->sayfa_adresi);
        free(current);
        current = next;
    }
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
}
// Cache buffer'� listelemek i�in kullan�lan fonksiyon
void printCacheBuffer(CacheBuffer *cache) {
    printf("Cache Buffer:\n");
    Node *current = cache->head;
    while (current != NULL) {
        printf("Sayfa Adresi: %s\t�stek Sayisi: %d\n", current->sayfa_adresi, current->istek_sayisi);
        current = current->next;
    }
}
// Dosyadan sayfa adreslerini okuyup cache'e ekleme
void readPagesFromFile(CacheBuffer *cache, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya a��lam�yor!.\n");
        return;
    }

    char sayfa_adresi[100];
    while (fgets(sayfa_adresi, sizeof(sayfa_adresi), file) != NULL) {
       
        if (sayfa_adresi[strlen(sayfa_adresi) - 1] == '\n') {
            sayfa_adresi[strlen(sayfa_adresi) - 1] = '\0';
        }

        Node *current = cache->head;
        int found = 0;
        while (current != NULL && !found) {
            if (strcmp(current->sayfa_adresi, sayfa_adresi) == 0) {
                updateCacheBuffer(cache, current);
                found = 1;
            }
            current = current->next;
        }

        if (!found) {
            addToCacheBuffer(cache, sayfa_adresi);
        }
    }

    fclose(file);
}

int main() {
	setlocale(LC_ALL,"Turkish");
	
    CacheBuffer *cache = createCacheBuffer();
    char sayfa_adresi[100];
    char choice;
    int exit_requested = 0;

    printf("Dosyadan okuma yapmak ister misiniz? (e/h): ");
    scanf(" %c", &choice);

    if (choice == 'e') {
        char filename[100];
        printf("Dosya ad�n� giriniz: ");
        scanf("%s", filename);
        readPagesFromFile(cache, filename);
    }

    while (!exit_requested) {
    printf("Sayfa adresini giriniz (��k�� yapmak i�in 'exit' yaz�n�z) :");
    scanf("%s", sayfa_adresi);

    if (strcmp(sayfa_adresi, "exit") == 0) {
        exit_requested = 1; 
    } else {
         // Adres cache buffer'da var m� yok mu onun kontrol�n� sa�l�yor
        Node *current = cache->head;
        int found = 0;
        while (current != NULL && !found) {
            if (strcmp(current->sayfa_adresi, sayfa_adresi) == 0) {
                updateCacheBuffer(cache, current);
                found = 1;
            }
            current = current->next;
        }

         // Bu k�s�mda e�er sayfa cache buffer'da bulunamad�ysa, cache buffer'a yeni bir ekleme yap�lmaktad�r.
        if (!found) {
            addToCacheBuffer(cache, sayfa_adresi);
        }
 
        printCacheBuffer(cache);
        printf("\n");

        printf("Cache`i temizlemek ister misiniz? (e/h): ");
        scanf(" %c", &choice);
        if (choice == 'e') {
            clearCacheBuffer(cache);
            printf("Cache temizlendi.\n\n");
        }
    }
}

    clearCacheBuffer(cache);
    free(cache);
    return 0;
}
