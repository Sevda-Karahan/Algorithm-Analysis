#include <stdio.h>
#include <stdlib.h>

// Maksimum düğüm sayısı
#define MAX_NODES 100

// Komşuluk matrisini dosyadan okuyan fonksiyon
int readAdjacencyMatrix(int adjacencyMatrix[MAX_NODES][MAX_NODES], int *numNodes, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı.");
        return -1;
    }

    fscanf(file, "%d", numNodes); // Düğüm sayısını oku
    // Matrisi oku
    int i, j;
    for (i = 0; i < *numNodes; i++) {
        for (j = 0; j < *numNodes; j++) {
            fscanf(file, "%d", &adjacencyMatrix[i][j]);
        }
    }

    fclose(file);
    return 0;
}

void BFS(int adjacencyMatrix[MAX_NODES][MAX_NODES], int numNodes, int sourceNode, int targetNode, int edgeMatrix[MAX_NODES][MAX_NODES]) {
    int visited[MAX_NODES] = {0}; // Ziyaret edilen düğümleri takip etmek için dizi oluşturuldu, başlangıçta hepsi ziyaret edilmedi.
    int queue[MAX_NODES]; // BFS sırasında kullanılacak kuyruk oluşturuldu
    int front = -1, rear = -1; // Kuyruğun başı ve sonu tutacak indisler, başlangıçta boş bir kuyruk olduğu için -1 olarak ayarlandı.
    int parent[MAX_NODES]; // Gezilen düğümlerin ebeveynlerini saklamak için dizi oluşturuldu.

    visited[sourceNode] = 1; // Başlangıç düğümü ziyaret edildi olarak işaretlendi.
    queue[++rear] = sourceNode; // Başlangıç düğümü kuyruğa eklendi.
    parent[sourceNode] = -1; // Başlangıç düğümü için ebeveyn atanmadı (-1 olarak ayarlandı).

    // Kuyruk dolu olduğu sürece BFS devam eder.
    while (front != rear) {
        int currentNode = queue[++front]; // Kuyruğun başındaki düğüm alındı.
		int j;
        // Tüm düğümler kontrol edilir.
        for (j = 0; j < numNodes; j++) {
            // Eğer düğüm komşu ise ve daha önce ziyaret edilmediyse:
            if (adjacencyMatrix[currentNode][j] != 0 && !visited[j]) {
                visited[j] = 1; // Düğüm ziyaret edildi olarak işaretlendi.
                queue[++rear] = j; // Düğüm kuyruğa eklendi.
                parent[j] = currentNode; // Ebeveyn düğümü kaydedildi.

                // Eğer hedef düğüme ulaşıldıysa, en kısa yolu bulmak için ebeveynleri takip ederek edgeMatrix'i güncelle.
                if (j == targetNode) {
                    int current = targetNode;
                    while (parent[current] != -1) {
                        edgeMatrix[parent[current]][current] += 1; // Kenarın varlığını işaretlemek için edgeMatrix güncellendi.
                        edgeMatrix[current][parent[current]] += 1; // Yönsüz graf için diğer yöne de işlem uygulandı.
                        current = parent[current]; // Bir önceki düğüme geçildi.
                    }
                    return; // İşlem tamamlandı, fonksiyon sonlandırıldı.
                }
            }
        }
    }
}

// matrisi ekrana yazdıran fonksiyon
void printMatrix(int Matrix[MAX_NODES][MAX_NODES], int numNodes) {
    int i, j;
    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}

// En yüksek değere sahip kenarı bulan fonksiyon
void findMaxEdge(int edgeMatrix[MAX_NODES][MAX_NODES], int numNodes, int *maxRow, int *maxCol) {
    int max = 0;

	int i, j;
    for (i = 0; i < numNodes; i++) {
        for (j = i + 1; j < numNodes; j++) {
            if (edgeMatrix[i][j] > max) {
                max = edgeMatrix[i][j];
                *maxRow = i;
                *maxCol = j;
            }
        }
    }
}

// Kenarı silen fonksiyon
void removeEdge(int edgeMatrix[MAX_NODES][MAX_NODES], int adjacencyMatrix[MAX_NODES][MAX_NODES], int row, int col) {
    edgeMatrix[row][col] = 0;
    edgeMatrix[col][row] = 0;
    adjacencyMatrix[row][col] = 0;
    adjacencyMatrix[col][row] = 0;
}

// DFS kullanarak toplulukları bulan yardımcı fonksiyon
void DFSWithCount(int adjacencyMatrix[MAX_NODES][MAX_NODES], int numNodes, int currentNode, int visited[MAX_NODES], int *memberCount) {
    visited[currentNode] = 1;
    printf("%d ", currentNode); // Düğümü ekrana bastır
	(*memberCount)++; // Her ziyaret edilen düğüm, üye sayısını arttırır
    int i;
    for (i = 0; i < numNodes; i++) {
        if (adjacencyMatrix[currentNode][i] != 0 && !visited[i]) {
            DFSWithCount(adjacencyMatrix, numNodes, i, visited, memberCount);
        }
    }
}

// Toplulukları bulan ana fonksiyon
void findCommunitiesWithSize(int adjacencyMatrix[MAX_NODES][MAX_NODES], int numNodes) {
    int visited[MAX_NODES] = {0};

    printf("\nTopluluklar ve Uye Sayilari:\n");
    int i;
    for (i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            int memberCount = 0; // Topluluktaki üye sayısını tutacak değişken
            printf("Topluluk %d: ", i);
            DFSWithCount(adjacencyMatrix, numNodes, i, visited, &memberCount);
            printf(" - Uye Sayisi: %d\n", memberCount);
        }
    }
}

// edgeMatrix'i sıfırlayan fonksiyon
void resetEdgeMatrix(int edgeMatrix[MAX_NODES][MAX_NODES], int numNodes) {
	int i, j;
    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            edgeMatrix[i][j] = 0;
        }
    }
}


int main() {
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    int edgeMatrix[MAX_NODES][MAX_NODES] = {0};
    int numNodes;

    if (readAdjacencyMatrix(adjacencyMatrix, &numNodes, "input.txt") == -1) {
        return -1;
    }

	int iter=0;
	while(iter<2) { // 2 iterasyon
		printf("\n****************************************************************************************\n");
		int i, j;
		for (i = 0; i < numNodes; i++) {
	        for (j = i + 1; j < numNodes; j++) {
	            BFS(adjacencyMatrix, numNodes, i, j, edgeMatrix);
	        }
	    }
	    
	    printf("\nGrafin komsuluk matrisi\n");
	    printMatrix(adjacencyMatrix, numNodes);
	    printf("\nAra kesici deger (edge betweenness) matrisi\n");
	    printMatrix(edgeMatrix, numNodes);
		
		int maxRow, maxCol;
	    findMaxEdge(edgeMatrix, numNodes, &maxRow, &maxCol);
	    printf("En yuksek ara kesici kenar: %d - %d\n", maxRow, maxCol);
	
		// En yüksek ara kesici kenarı sil
	    removeEdge(edgeMatrix, adjacencyMatrix, maxRow, maxCol);
		
		printf("En yuksek ara kesici kenar kaldirildiktan sonra\n");
		printf("\nGrafin komsuluk matrisi\n");
	    printMatrix(adjacencyMatrix, numNodes);
	    printf("\nAra kesici deger (edge betweenness) matrisi\n");
	    printMatrix(edgeMatrix, numNodes);
	    
	    findCommunitiesWithSize(adjacencyMatrix, numNodes);
	    
	    resetEdgeMatrix(edgeMatrix, numNodes);
	    iter++;
	}
    
    return 0;
}
