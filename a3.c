#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000000


// Node structure for adjacency list
typedef struct node {
    int vertex;
    struct node* next;
} node;

// Graph structure for adjacency list
typedef struct Graph {
    int num_vertices;
    int* visited;
    node** adjList;
} Graph;


int main() {
    // Parse input file to construct graph
    FILE* fp;
    fp = fopen("graph.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }

    int src, dest;

    while (fscanf(fp, "%d %d", &src, &dest) != EOF) {
         printf("node %d ",src);
         printf("is going to node %d\n", dest);
    }

    fclose(fp);

    return 0;
}

