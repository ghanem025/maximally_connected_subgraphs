#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 999999
int counter = 0;
int max = 0;


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

// void DFS(struct Graph* graph, int startVertex, int* visited) {
    
//     int stack[MAX_SIZE], top = -1;
//     stack[++top] = startVertex;
//     visited[startVertex] = 1;
    
    
//     while (top != -1) {
//         int currentVertex = stack[top--];
//         struct node* adjList = graph->adjList[currentVertex];
//         counter++;
//         while (adjList != NULL) {
//             int adjVertex = adjList->vertex;
//             if (!visited[adjVertex]) {
//                 stack[++top] = adjVertex;
//                 visited[adjVertex] = 1;
//             }
//             adjList = adjList->next;
//         }
//     }
// }


void BFS(struct Graph* graph, int startVertex, int* visited) {
    int queue[max];
    int front = 0, rear = 0;
    visited[startVertex] = 1;
    queue[rear++] = startVertex;
    while (front != rear) {
        int curr = queue[front++];
        struct node* adjList = graph->adjList[curr];
        counter++;
        while (adjList != NULL) {
            int adjVertex = adjList->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            adjList = adjList->next;
        }
    }
}

int countMaximallyConnectedSubgraphs(struct Graph* graph) {
    int numSubgraphs = 0;

    // Step 1: perform DFS on the original graph to obtain a topological ordering of the vertices
    int* visited = (int*)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < graph->num_vertices; i++) {
        struct node* temp = graph->adjList[i];
        if (!visited[i] && temp!=NULL) {
            BFS(graph, i, visited);
            numSubgraphs++;
            printf("The total vertices for this maximally connected subgraph is %d\n", counter);
            counter=0;
        }
    }
    return numSubgraphs;
}

int main() {

    // Parse input file to construct graph
    FILE* fp;
    FILE* fp2;
    char const* filename = "graph.txt";
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }
    int src, dest;
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

    struct Graph* graph = createGraph(max+1);
    fp2 = fopen(filename, "r");
    if (fp2 == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }
    // printf("the max is %d", max+1);
    while (fscanf(fp2, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }

    int count = countMaximallyConnectedSubgraphs(graph);

    printf("there are %d maximally connected subgraphs\n", count);

    return 0;
}

