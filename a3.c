#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    // printf("\na new edge has been added: %d\n", new_node->vertex);
    graph->adjList[src] = new_node;
}


struct Graph* createGraph(int num_vertices){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); // initialize
    if (!graph){
        printf("Error: Memory allocation failed");
        return NULL;
    }
    graph->num_vertices = num_vertices; // assigne vertices to graph struct
    graph->adjList = (struct node**)calloc(num_vertices ,sizeof(struct node*));
    for (int i = 0; i < num_vertices; i++){
        graph->adjList[i] = NULL;
    }
    return graph;
}

// // free the memory we allocated for the graph
// void freeGraph(struct Graph* graph) {
//     for (int i = 0; i < graph->num_vertices; i++) {
//         struct node* temp = graph->adjList[i];
//         while (temp != NULL) {
//             struct node* prev = temp;
//             temp = temp->next;
//             free(prev); // freeing node
//         }
//     }
//     free(graph->adjList);
//     free(graph);
// }

// print out the graph
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        // printf("Adjacency list of vertex %d:\n", i);
        if (graph->adjList[i] != NULL) {
            struct node* temp = graph->adjList[i];
            while (temp != NULL) {
                printf("%d -> %d\n", i, temp->vertex);
                temp = temp->next;
            }
        }
    }
}

// DFS function 
void DFS(struct Graph* g, int v, bool visited[]) {
    visited[v] = true;
    struct node* temp = g->adjList[v];
    while (temp) {
        int adjv = temp->vertex;
        if (!visited[adjv]) { // checks if the dest vertex was visited, if it wasn't we call DFS again
            DFS(g, adjv, visited); // recursively call DFS
        }
        temp = temp->next; // temp is assigned to the next vertex
    }
}

int countMaximallyConnectedSubgraphs(struct Graph* g) {
    int numVertices = g->num_vertices;
    bool visited[numVertices]; 
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false; // set all vertices to not visited since we will visit them when we call DFS.
    }
    int count = 0;
    for (int i = 0; i < numVertices; i++) {
        struct node* temp = g->adjList[i]; // this helps us check if a node is connected to another node
        if (!visited[i] && temp != NULL) { // we check if a node is connected to another node, if it is we call DFS and increase counter
            count++;
            DFS(g, i, visited); // 
        }
    }
    return count;
}



int main() {

    int num_vertices = 33;
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

    printGraph(graph);
    int count = countMaximallyConnectedSubgraphs(graph);

    printf("there are %d maximally connected subgraphs\n", count);
    // freeGraph(graph);

    return 0;
}

