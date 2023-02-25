#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex; // this will be our source node
    struct node* next; // this will be our destination node
} node;

struct node* createNode(int v){
    struct node* new_node = (struct node*)malloc(sizeof(struct node)); // intialize new node 
    // initializing varibales in struct
    new_node -> vertex = v;
    new_node -> next = NULL;
    return new_node;
}

typedef struct Graph {
    int num_vertices;
    int* visited;
    node** adjList;
} Graph;

void addEdge( struct Graph* graph, int src, int dest){
    struct node* new_node = createNode(dest); // create a new node
    new_node -> next = graph->adjList[src];
    graph->adjList[src] = new_node;
}


struct Graph* createGraph(int num_vertices){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); // initialize
    graph->num_vertices = num_vertices; // assigne vertices to graph struct
    graph->adjList = (struct node**)calloc(num_vertices ,sizeof(struct node*));
    for (int i = 0; i < num_vertices; i++){
        graph->adjList[i] = NULL;
    }
    return graph;
}

// free the memory we allocated for the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        struct node* temp = graph->adjList[i];
        while (temp != NULL) {
            struct node* prev = temp;
            temp = temp->next;
            free(prev); // freeing node
        }
    }
    free(graph->adjList);
    free(graph);
}

// print out the graph
void printGraph(struct Graph* graph, int num_vertices)
{
    for (int i = 0; i < num_vertices; i++) {
        struct node* temp = graph->adjList[i];
        while (temp != NULL) {
            printf("Adjacency list of vertex %d\nhead", i);
            printf(" -> %d", temp->vertex);
            temp = temp->next;
            printf("\n");
        }
    }
}

int main() {

    int num_vertices = 999999;
    struct Graph* graph = createGraph(num_vertices);
    // Parse input file to construct graph
    FILE* fp;
    fp = fopen("graph.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }

    int src, dest;

    while (fscanf(fp, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }

    fclose(fp);

    printGraph(graph, num_vertices);
    freeGraph(graph);

    return 0;
}

