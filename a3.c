#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int counter = 0;
int max = 999999;
int *num_nodes;


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


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}



void DFS(struct Graph* graph, int startVertex, int* visited) {
    int stack[max+1], top = -1;
    stack[++top] = startVertex;
    visited[startVertex] = 1;
    while (top != -1) {
        int currentVertex = stack[top--];
        struct node* adjList = graph->adjList[currentVertex];
        counter++;
        while (adjList != NULL) {
            int adjVertex = adjList->vertex;
            if (!visited[adjVertex]) {
                stack[++top] = adjVertex;
                visited[adjVertex] = 1;
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
            DFS(graph, i, visited);
            numSubgraphs++;
            // printf("The total vertices for maximally connected subgraph %d is: ", numSubgraphs);
            // printf("%d\n", counter);
            num_nodes = (int*)realloc(num_nodes, numSubgraphs * sizeof(int));
            num_nodes[numSubgraphs - 1] = counter;
            counter=0;
        }
    }
    return numSubgraphs;
}


// //Partition Function
// int partition(int arr[], int low, int high)
// {
// 	int pivot = arr[high];
// 	int i = (low - 1);
//     int j;
// 	for (j = low; j <= high - 1; j++) {
// 		if (arr[j] <= pivot) {
// 			i++;
// 			swap(&arr[i], &arr[j]);
// 		}
// 	}
// 	swap(&arr[i + 1], &arr[high]);  
// 	return (i + 1);
// }

// Quick Sort function
void quicksort(int Arr[], int low, int high)
{
	if (low < high) {
		// pi = Partition index
		int pi = partition(Arr, low, high);
		quicksort(Arr, low, pi - 1);
		quicksort(Arr, pi + 1, high);           
	}
}

void printArray(int arr[], int size)
{
    int i;
	for(i = 0; i < size; i++) {
		printf("%d \n",arr[i]);
	}
}
  


int main(int argc, char* argv[]) {
    // Parse input file to construct graph
    FILE* fp;
    FILE* fp2;
    char const* filename = "web-Google.txt";
    // fp = fopen(filename, "r");
    // if (fp == NULL) {
    //     printf("Error: could not open input file.\n");
    //     return 1;
    // }
    char c;
    int src, dest;

    // while (fscanf(fp, "%c", &c) == 1) {
    //     if (c == '#') {
    //         fscanf(fp, "%*[^\n]\n");
    //     } else {
    //         ungetc(c, fp);
    //         fscanf(fp, "%d %d", &src, &dest);
    //         if(max < src || max < dest){
    //             if(src < dest){
    //                 max = dest;
    //             }
    //             else
    //                 max = src;
    //         }
    //     }
    // }

    // fclose(fp);

    struct Graph* graph = createGraph(max);
    fp2 = fopen(filename, "r");
    if (fp2 == NULL) {
        printf("Error: could not open input file.\n");
        return 1;
    }
    char c2;
    while (fscanf(fp2, "%c", &c2) == 1) {
        if (c2 == '#') {
            fscanf(fp2, "%*[^\n]\n");
        } else {
            ungetc(c2, fp2);
            fscanf(fp2, "%d %d", &src, &dest);
            addEdge(graph, src, dest);
        }
    }

    int count = countMaximallyConnectedSubgraphs(graph);

    printf("there are %d maximally connected subgraphs\n", count);

    quicksort(num_nodes, 0, count-1);
    printArray(num_nodes, count-1);

    return 0;
}

