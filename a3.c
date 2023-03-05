#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 999999
int counter = 1;

int stack[MAX_SIZE], top;

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


void push(int x){
    if (top >= MAX_SIZE - 1){
        printf("\n\tSTACK is over flow\n");
    }
    else{
        top++;
        stack[top] = x;
    }
}

void pop(){
    if (top <= -1){
        printf("\n\t Stack is under flow\n");
    }
    else{
        top--;
    }
}

void reverse_graph(struct Graph* graph, int src, int dest){
    struct node* new_node = createNode(src);
    new_node->next = graph->adjList[dest];
    graph->adjList[dest] = new_node;
}

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
    graph->adjList = (struct node**)malloc(num_vertices * sizeof(struct node*));
    for (int i = 0; i < num_vertices; i++){
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Fuction to fill the stack
void set_fill_order(struct Graph *graph, int v, bool visited[], int *stack){
    visited[v] = true;
    int i = 0;
    struct node* temp = graph->adjList[v];
    while (temp){

        counter++;
        if (!visited[temp->vertex])
        {
            set_fill_order(graph, temp->vertex, visited, stack);
        }
        temp = temp->next;
    }
    push(v);
}

// // A recursive function to print DFS starting from v
// void DFS(struct Graph* g, int v, bool visited[]) {
//     visited[v] = true;
//     struct node* temp = g->adjList[v];
//     while (temp != NULL) {
//         int adjv = temp->vertex;
//         if (!visited[adjv]) { // checks if the dest vertex was visited, if it wasn't we call DFS again
//             DFS(g, adjv, visited); // recursively call DFS
//         }
//         temp = temp->next; // temp is assigned to the next vertex
//     }
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


void DFS(struct Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    struct node* adjList =  graph->adjList[vertex];
    while (adjList != NULL) {
        counter++;
        int adjVertex = adjList->vertex;
        // printf("WE ARE SEARCHING %d\n", adjVertex);
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited);
        }
        adjList = adjList->next;
    }
}

int countMaximallyConnectedSubgraphs(struct Graph* graph, struct Graph* reversedGraph) {
    int numSubgraphs = 0;

    // Step 1: perform DFS on the original graph to obtain a topological ordering of the vertices
    int* visited = (int*)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < graph->num_vertices; i++) {
        struct node* temp = graph->adjList[i];
        if (!visited[i] & temp!=NULL) {
            DFS(graph, i, visited);
            numSubgraphs++;
        }
    }

    //Step 2: perform DFS on the reversed graph to obtain a topological ordering of the vertices
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }
    for (int i = 0; i < graph->num_vertices; i++) {
        struct node* temp = reversedGraph->adjList[i];
        if (!visited[i]) {
            DFS(reversedGraph, i, visited);
            numSubgraphs++;
        }
    }
    // freeGraph(reversedGraph);

    free(visited);

    // Step 3: return the number of maximally connected subgraphs
    return numSubgraphs;
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



// DFS function 


// int countMaximallyConnectedSubgraphs(struct Graph* g) {
//     int num_vertices = g->num_vertices;
//     bool visited[num_vertices]; 
//     for (int i = 0; i < num_vertices; i++) {
//         visited[i] = false; // set all vertices to not visited since we will visit them when we call DFS.
//     }
//     int count = 0;
//     for (int i = 0; i < num_vertices; i++) {
//         struct node* temp = g->adjList[i]; // this helps us check if a node is connected to another node
//         if (!visited[i] && temp != NULL) { // we check if a node is connected to another node, if it is we call DFS and increase counter
//             count++;
//             counter++;
//             printf("maximally connected subgraph and the root vertext is %d: has ", temp->vertex);
//             DFS(g, i, visited);
            
//             printf("%d vertices\n", counter);
            
//         }
//         counter = 0;
//     }
//     return count;
// }


int main() {
    top = -1;

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

    struct Graph* graph = createGraph(max+1);
    struct Graph* reversedGraph = createGraph(max+1);
    fp2 = fopen("graph.txt", "r");
    if (fp2 == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }
    // printf("the max is %d", max+1);
    while (fscanf(fp2, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
        addEdge(reversedGraph, dest, src);
    }

    printGraph(graph);
    printf("OTHER GRAPH\n");
    printGraph(reversedGraph);

    int count = countMaximallyConnectedSubgraphs(graph, reversedGraph);
    printf("there are %d maximally connected subgraphs\n", count - max);
    return 0;
}

