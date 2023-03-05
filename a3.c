#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 999999
int counter = 1;

int stack[MAX_SIZE], top;

typedef struct node {
    int vertex; // this will be our source node
    bool visited;
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
    // struct node* new_node = createNode(dest); // create a new node
    // new_node -> next = graph->adjList[src];
    // // printf("\na new edge has been added: %d\n", new_node->vertex);
    // graph->adjList[src] = new_node;

    struct node* new_node = createNode(dest);
    new_node -> next = graph->adjList[src];
    graph->adjList[src] = new_node;

    // Add the reverse edge as well
    new_node = createNode(src);
    new_node -> next = graph->adjList[dest];
    graph->adjList[dest] = new_node;
}

struct Graph* createGraph(int num_vertices){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); // initialize
    if (!graph){
        printf("Error: Memory allocation failed");
        return NULL;
    }
    graph->num_vertices = num_vertices; // assigne vertices to graph struct
    graph->adjList = (struct node**)malloc(num_vertices * sizeof(struct node*));
    for (int i = 0; i < num_vertices; i++){
        graph->adjList[i] = NULL;
    }
    return graph;
}

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


void DFS(struct Graph* g, int v, bool visited[]) {
    visited[v] = true;
    struct node* temp = g->adjList[v];
    while (temp) {
        int adjv = temp->vertex;
        if (!visited[adjv]) { // checks if the dest vertex was visited, if it wasn't we call DFS again
            counter++;
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
        if (!visited[i]) { // we check if a node is connected to another node, if it is we call DFS and increase counter
            count++;
            DFS(g, i, visited);
            //printf("The are %d vertices in this maximally connected subgraph\n", counter);
            
        }
        //counter=0;
    }
    return count;
}

int main() {

    // Parse input file to construct graph
    FILE* fp;
    FILE* fp2;
    fp = fopen("graph.txt", "r");
    if (fp == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }

    int src, dest;
    int max;
    while (fscanf(fp, "%d %d", &src, &dest) != EOF) {
        if(max < src || max < dest){
            if(src < dest){
                max = dest;
            }
            else
                max = src;
        }
    }
    fclose(fp);

    struct Graph* graph = createGraph(max);
    fp2 = fopen("graph.txt", "r");
    if (fp2 == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }
    // printf("the max is %d", max+1);
    while (fscanf(fp2, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }

    printGraph(graph);
    printf("OTHER GRAPH\n");

    int count = countMaximallyConnectedSubgraphs(graph);

    printf("there are %d maximally connected subgraphs\n", count);

    return 0;
}

