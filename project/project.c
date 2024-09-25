#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Node {
    char name;
    int id;
} Node;

typedef struct Graph {
    int numVertices;
    Edge* adjLists[MAX];
    bool visited[MAX];
    Node nodes[MAX];
} Graph;

typedef struct Polygon {
    int nodes[MAX];
    int nodeCount;
    int perimeter;
} Polygon;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest, int weight);
void DFS(Graph* graph, int vertex, int start, int length, Polygon* polygons, int* polygonCount, int* path, int* totalShapes);
bool inPath(int* path, int length, int vertex);
int calculatePerimeter(Graph* graph, int* path, int length);
void printPolygons(Graph* graph, Polygon* polygons, int polygonCount);
int findNodeId(Graph* graph, char name);
void readGraphFromFile(Graph** graph, const char* filename);
void inputGraphManually(Graph** graph);

int main() {
    int choice;
    Graph* graph = NULL;
    //Kullanýcýnýn seçimine göre, graf ya manuel olarak girilir ya da bir dosyadan okunur. Geçersiz bir seçim yapýlýrsa, program hata mesajý verir ve sonlanýr.

    printf("Bir secenek secin:\n");
    printf("1. El ile graf bilgilerini giriniz: \n");
    printf("2. Graf bilgilerini dosyadan okuyunuz: \n");
    scanf("%d", &choice);

    if (choice == 1) {
        inputGraphManually(&graph);
    } else if (choice == 2) {
        readGraphFromFile(&graph, "Sample.txt");
    } else {
        printf("Invalid choice\n");
        return 1;
    }

    Polygon polygons[MAX];
    int polygonCount = 0;
    int totalShapes = 0;
    
    // `polygons` dizisi çokgenleri saklamak için kullanýlýr. Her bir düðüm için `DFS` fonksiyonu çaðrýlarak grafýn tüm yollarý taranýr ve çokgenler aranýr.
    
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        int path[MAX] = {0};
        DFS(graph, i, i, 0, polygons, &polygonCount, path, &totalShapes);
    }
	//Bulunan toplam þekil sayýsý yazdýrýlýr ve daha sonra bulunan çokgenler ekrana basýlýr
	printf("Toplam Sekil Sayisi: %d\n", totalShapes);
    printPolygons(graph, polygons, polygonCount);
    

    return 0;
}
//Bu fonksiyon, belirtilen sayýda düðüm içeren yeni bir graf oluþturur. 
//Her bir düðüm için kenar listesi baþlatýlýr (NULL) ve ziyaret edilme durumu `false` ayarlanýr
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}
//Bu fonksiyon, grafýn belirtilen kaynak (`src`) düðümünden hedef (`dest`) düðüme bir kenar ekler. 
//Kenarýn aðýrlýðý (`weight`) belirlenir.

void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->adjLists[src];
    graph->adjLists[src] = newEdge;
}

//`visited` dizisi, ziyaret edilen düðümleri iþaretler. 
//Fonksiyon, baþlangýç düðümüne geri dönüldüðünde ve yolda en az 3 düðüm olduðunda bir poligon bulunduðunu tespit eder.
void DFS(Graph* graph, int vertex, int start, int length, Polygon* polygons, int* polygonCount, int* path, int* totalShapes) {
    graph->visited[vertex] = true;
    path[length] = vertex;
    Edge* edge;
    int i;
    int foundPolygon = 0;
    for (edge = graph->adjLists[vertex]; edge != NULL; edge = edge->next) {
        if (edge->dest == start && length >= 2) {
            int isNewPolygon = 1;
            for (i = 0; i < *polygonCount; i++) {
                if (polygons[i].nodeCount == length + 1 && inPath(polygons[i].nodes, polygons[i].nodeCount, vertex)) {
                    isNewPolygon = 0;
                }
            }
            if (isNewPolygon) {
                Polygon polygon;
                polygon.nodeCount = length + 1;
                for (i = 0; i <= length; i++) {
                    polygon.nodes[i] = path[i];
                }
                polygon.nodes[length + 1] = start;
                polygon.perimeter = calculatePerimeter(graph, path, length + 1);
                polygons[*polygonCount] = polygon;
                (*polygonCount)++;
                (*totalShapes)++;
                foundPolygon = 1;
            }
        } else if (!graph->visited[edge->dest]) {
            DFS(graph, edge->dest, start, length + 1, polygons, polygonCount, path, totalShapes);
        }
    }
    graph->visited[vertex] = false;
    if (foundPolygon)
        return;
}
//Bu fonksiyon, belirtilen düðümün halihazýrda olup olmadýðýný kontrol eder.
bool inPath(int* path, int length, int vertex) {
    int i;
    for (i = 0; i < length; i++) {
        if (path[i] == vertex) {
            return true;
        }
    }
    return false;
}
//Bu fonksiyon, bir çokgenin çevresini hesaplar. Her kenarýn aðýrlýðý toplanarak toplam çevre hesaplanýr.
int calculatePerimeter(Graph* graph, int* path, int length) {
    int perimeter = 0;
    int i;
    for (i = 0; i < length; i++) {
        int src = path[i];
        int dest = path[(i + 1) % length];
        Edge* edge;
        for (edge = graph->adjLists[src]; edge != NULL; edge = edge->next) {
            if (edge->dest == dest) {
                perimeter += edge->weight;
                break;
            }
        }
    }
    return perimeter;
}

int findNodeId(Graph* graph, char name) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        if (graph->nodes[i].name == name) {
            return graph->nodes[i].id;
        }
    }
    return -1;
}

//Bu fonksiyon, öncelikle poligonlarýn sayýlarýný ve boyutlarýný hesaplar. 
//Daha sonra, poligonlarý boyutlarýna göre sýralar ve bu poligonlarý kullanýcýya sunar. 
//Her poligon için düðümlerin adlarýný ve çevrelerini yazdýrýr.
void printPolygons(Graph* graph, Polygon* polygons, int polygonCount) {
    Polygon sortedPolygons[MAX];
    int sortedPolygonCount = 0;

    int polygonSizes[MAX] = {0};
    int maxPolygonSize = 0;

    int i, j;
    for (i = 0; i < polygonCount; i++) {
        if (polygons[i].nodeCount > maxPolygonSize) {
            maxPolygonSize = polygons[i].nodeCount;
        }
        polygonSizes[polygons[i].nodeCount]++;
    }
	printf("Cokgenlerin sayilari:\n");
    for (i = 3; i <= maxPolygonSize; i++) {
        if (polygonSizes[i] > 0) {
            printf("%d-gen: %d\n", i, polygonSizes[i]);
        }
        
    }

    for (i = 3; i <= maxPolygonSize; i++) {
        for (j = 0; j < polygonCount; j++) {
            if (polygons[j].nodeCount == i) {
                sortedPolygons[sortedPolygonCount++] = polygons[j];
            }
        }
    }

    for (i = 0; i < sortedPolygonCount; i++) {
        printf("%d. Cokgen (%d-gen): ", i + 1, sortedPolygons[i].nodeCount);
        int k;
        for (k = 0; k < sortedPolygons[i].nodeCount; k++) {
            printf("%c-", graph->nodes[sortedPolygons[i].nodes[k]].name);
        }
        printf("%c ", graph->nodes[sortedPolygons[i].nodes[0]].name);
        printf("Cevre: %d\n", sortedPolygons[i].perimeter);
    }
}
//Bu fonksiyon, dosyadan graf verilerini okur, düðüm ve kenar bilgilerini alýr ve graf yapýsýný buna göre kurar. 
void readGraphFromFile(Graph** graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya Acilamadi!.\n");
        exit(1);
    }

    int N = 0;
    int src, dest, weight;
    char srcName, destName;

    while (fscanf(file, " %c %c %d", &srcName, &destName, &weight) != EOF) {
        src = srcName - 'A';
        dest = destName - 'A';
        if (src >= N) N = src + 1;
        if (dest >= N) N = dest + 1;
    }
    rewind(file);

    *graph = createGraph(N);

    int i;
    for (i = 0; i < N; i++) {
        (*graph)->nodes[i].name = 'A' + i;
        (*graph)->nodes[i].id = i;
    }

    while (fscanf(file, " %c %c %d", &srcName, &destName, &weight) != EOF) {
        src = srcName - 'A';
        dest = destName - 'A';
        addEdge(*graph, src, dest, weight);
        addEdge(*graph, dest, src, weight);
    }

    fclose(file);
}

void inputGraphManually(Graph** graph) {
    int N, M;
    char nodeType;
    printf("Node ve edge sayilarini giriniz (node -arada bosluk- edge) :\n");
    scanf("%d %d", &N, &M);

    *graph = createGraph(N);
//Düðüm için sayý veya harf kullanmak isteyebiliriz.
    printf("Nodelar icin harf kullanmak isterseniz (L) Sayi kullanmak isterseniz (N) yaziniz: ");
    scanf(" %c", &nodeType);

    int i;
    printf("Nodelari giriniz: \n");
    for (i = 0; i < N; i++) {
        char name;
        int id = i;
        if (nodeType == 'L' || nodeType == 'l') {
            scanf(" %c", &name);
        } else {
            name = '0' + i;
        }
        (*graph)->nodes[i].name = name;
        (*graph)->nodes[i].id = id;
    }

    printf("Kenar bilgilerini giriniz (src dest weight):\n");
    for (i = 0; i < M; i++) {
        char srcName, destName;
        int weight;
        scanf(" %c %c %d", &srcName, &destName, &weight);
        int src = findNodeId(*graph, srcName);
        int dest = findNodeId(*graph, destName);
        addEdge(*graph, src, dest, weight);
        addEdge(*graph, dest, src, weight);
    }
}

