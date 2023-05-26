#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100
#define INFINITY 99999

typedef struct {
    int cost;
    int parent;
    bool visited;
} Node;

// Inisialisasi graf dengan bobot yang diambil dari user
void initializeGraph(int graph[MAX_NODES][MAX_NODES], int numNodes) {
    int i, j;
    for (i = 1; i <= numNodes; i++) {
        for (j = 1; j <= numNodes; j++) {
            printf("Masukkan bobot dari node %d ke node %d: ", i, j);
            scanf("%d", &graph[i][j]);
        }
    }
}

// Menggunakan algoritma Dijkstra untuk mencari jarak terpendek dari startNode ke semua node lainnya
void dijkstra(int graph[MAX_NODES][MAX_NODES], int numNodes, int startNode, int endNode) {
    Node nodes[MAX_NODES];
    int i, j, current;

    // Inisialisasi node
    for (i = 1; i <= numNodes; i++) {
        nodes[i].cost = INFINITY;
        nodes[i].parent = -1;
        nodes[i].visited = false;
    }

    // Node awal memiliki cost 0
    nodes[startNode].cost = 0;
    current = startNode;

    while (!nodes[current].visited) {
        // Menandai node saat ini sebagai dikunjungi
        nodes[current].visited = true;

        // Update cost dan parent dari semua node yang terhubung dengan node saat ini
        for (i = 1; i <= numNodes; i++) {
            if (graph[current][i] != 0 && !nodes[i].visited) {
                if (nodes[current].cost + graph[current][i] < nodes[i].cost) {
                    nodes[i].cost = nodes[current].cost + graph[current][i];
                    nodes[i].parent = current;
                }
            }
        }

        // Mencari node dengan cost terkecil yang belum dikunjungi
        int minCost = INFINITY;
        for (i = 1; i <= numNodes; i++) {
            if (!nodes[i].visited && nodes[i].cost < minCost) {
                minCost = nodes[i].cost;
                current = i;
            }
        }
    }

    // Menampilkan hasil jarak terpendek dari startNode ke semua node
    printf("Node\tJarak\t\tPath\n");
    for (i = 1; i <= numNodes; i++) {
        printf("%d\t%d\t\t", i, nodes[i].cost);
        j = i;

        // Mencetak path dari node awal ke node saat ini
        while (j != startNode) {
            printf("%d <- ", j);
            j = nodes[j].parent;
        }
        printf("%d\n", startNode);
    }

    // Menampilkan path dari node awal ke node akhir
    printf("\nJalur dari node %d ke node %d:\n", startNode, endNode);
    printf("%d <- ", endNode);
    j = nodes[endNode].parent;
    while (j != startNode) {
        printf("%d <- ", j);
        j = nodes[j].parent;
    }
    printf("%d\n", startNode);
}


int main() {
    int graph[MAX_NODES][MAX_NODES];
    int numNodes, startNode, endNode;

    printf("Masukkan jumlah node: ");
    scanf("%d", &numNodes);

    initializeGraph(graph, numNodes);


    int i, j;
    printf("\nMetrik Beban:\n");
    for (i = 1; i <= numNodes; i++) {
        for (j = 1; j <= numNodes; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }


    printf("Masukkan node awal (1-%d): ", numNodes);
    scanf("%d", &startNode);

    printf("Masukkan node akhir: ");
    scanf("%d", &endNode);

    dijkstra(graph, numNodes, startNode, endNode);

    return 0;
}
