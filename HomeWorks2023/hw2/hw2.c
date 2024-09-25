#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50
#define MAX_DICT_SIZE 100000

// Stack yap�s� ve fonksiyonlar�
typedef struct {
    char words[MAX_WORD_LEN][MAX_WORD_LEN];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

void push(Stack *stack, char *word) {
    strcpy(stack->words[++stack->top], word);
}

// Queue yap�s� ve fonksiyonlar�
typedef struct {
    Stack stacks[MAX_DICT_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *queue) {
    queue->front = -1;
    queue->rear = -1;
}

void enqueue(Queue *queue, Stack *stack) {
    queue->stacks[++queue->rear] = *stack;
    if (queue->front == -1) {
        queue->front = 0;
    }
}

Stack dequeue(Queue *queue) {
    return queue->stacks[queue->front++];
}

int isEmpty(Queue *queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

// Helper fonksiyonlar
int isOneCharDiff(char *word1, char *word2) {
    int diffCount = 0;
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int i;
    
    if (len1 != len2) {
        return 0; // Kelimelerin uzunluklar� e�it de�ilse, bir karakter fark� yoktur
    }

    for (i = 0; i < len1; i++) {
        if (word1[i] != word2[i]) {
            diffCount++;
        }
    }
    return (diffCount == 1);
}

// Kelime merdiveni bulma fonksiyonu
void findWordLadder(char *startWord, char *endWord, char **dictionary, int dictSize) {
    Queue queue;
    initQueue(&queue);
    Stack initialStack;
    initStack(&initialStack);
    push(&initialStack, startWord);

    int *visited = (int*)calloc(dictSize, sizeof(int)); // Ziyaret edilen kelimeleri tutmak i�in dizi olu�tur
    visited[0] = 1; // Ba�lang�� kelimesini ziyaret etti�imizi i�aretle

    while (!isEmpty(&queue)) {
        Stack currentStack = dequeue(&queue);
        char *currentWord = currentStack.words[currentStack.top];
        int i;

        if (strcmp(currentWord, endWord) == 0) {
            // Hedef kelimeye ula��ld�, kelime merdivenini yazd�r
            printf("Kelime merdiveni:\n");
            for (i = 0; i <= currentStack.top; i++) {
                printf("%s -> ", currentStack.words[i]);
            }
            printf("\n");
            free(visited); // Belle�i serbest b�rak
            return;
        }

        // Tek harf fark� olan kelimeleri bul ve stack'e ekle
        for ( i = 0; i < dictSize; i++) {
            if (visited[i] == 0 && isOneCharDiff(currentWord, dictionary[i])) {
                visited[i] = 1; // Kelimeyi ziyaret etti�imizi i�aretle
                Stack newStack = currentStack;
                push(&newStack, dictionary[i]);
                enqueue(&queue, &newStack);
            }
        }
    }

    // Hedef kelimeye ula��lamad�
    printf("Hedef kelimeye ula��lamad�.\n");
    free(visited); // Belle�i serbest b�rak
}


int main() {
    // S�zl�k dosyas�n� oku
    FILE *file = fopen("dictionary.txt", "r");
    if (file == NULL) {
        printf("S�zl�k dosyas� bulunamad�!\n");
        return 1;
    }

    char *dictionary[MAX_DICT_SIZE];
    char word[MAX_WORD_LEN];
    int dictSize = 0;
    int i;

    // S�zl�k dosyas�ndan kelimeleri oku ve diziye ekle
    while (fgets(word, MAX_WORD_LEN, file) != NULL) {
        word[strcspn(word, "\n")] = 0; // Sat�r sonu karakterini kald�r
        dictionary[dictSize] = strdup(word);
        dictSize++;
    }

    fclose(file);

    char startWord[MAX_WORD_LEN];
    char endWord[MAX_WORD_LEN];

    printf("Kaynak kelimeyi giriniz: ");
    scanf("%s", startWord);

    printf("Hedef kelimeyi giriniz: ");
    scanf("%s", endWord);

    // Kelime merdivenini bul ve yazd�r
    findWordLadder(startWord, endWord, dictionary, dictSize);

    // Bellek temizleme
    for ( i = 0; i < dictSize; i++) {
        free(dictionary[i]);
    }

    return 0;
}

