#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WHITE 0
#define GREY 1
#define BLACK 2

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

int setSize[100], numSets, rank[100], p[100];

struct AdjListNode {
	int dest, cost;
	struct AdjListNode *next;
};

struct AdjList {
	struct AdjListNode *head;
	int color;
};

struct Graph {
	int V;
	struct AdjList *array;
};

struct Edge {
	int a, b, cost;
	struct Edge *next;
};

struct EdgeList {
	struct Edge *head;
	struct Edge *array;
};

struct Edge* newEdge(int a, int b, int cost) {

	struct Edge* newEdg = (struct Edge*) malloc(sizeof (struct Edge));
	newEdg->a = a;
	newEdg->b = b;
	newEdg->cost = cost;
	newEdg->next = NULL;
	return newEdg;
}

void addEdgeToEdgeList(struct EdgeList* edgeList, int a, int b, int cost) {

	struct Edge* newEdg = newEdge(a, b, cost);
	newEdg->next = edgeList->head;
	edgeList->head = newEdg;
}

struct AdjListNode* newAdjListNode(int dest, int cost) {

	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->cost = cost;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V) {

	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;

	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

	int i;
	for (i = 0; i < V; ++i)
		graph->array[i].head = NULL;
	return graph;
}

void addEdgeToGraph(struct Graph* graph, int src, int dest, int cost) {

	struct AdjListNode* newNode = newAdjListNode(dest, cost);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src, cost);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph) {

	int v;
	for (v = 1; v <= graph->V; ++v) {
		struct AdjListNode* node = graph->array[v].head;
		printf("\nLista de adjacencias do vertice %d\n head ", v);
		while (node) {
			printf("-> (%d,%c", node->dest, node->cost);
			node = node->next;
		}
		printf("\n");
	}
}

void inicializeVertexColorsWhite(struct Graph* graph, int V) {

	int v;
	for (v = 0; v < V; v++) {
		graph->array[v].color = WHITE;
	}
}

void DFSVisit(struct Graph* graph, int u) {
	graph->array[u].color = GREY;
	struct AdjListNode* node;
	for (node = graph->array[u].head; node != NULL; node = node->next)
		if (graph->array[node->dest].color == WHITE)
			DFSVisit(graph, node->dest);
}

bool isConnected(struct Graph* graph, int V) {
	inicializeVertexColorsWhite(graph, V);
	int v;
	for (v = 0; v < V; v++) {
		if (graph->array[v].color == WHITE)
			DFSVisit(graph, v);
	}
	for (v = 0; v < V; v++) {
		if (graph->array[v].color == WHITE)
			return false;
	}
	return true;
}

int kruskal(int N, int E, struct EdgeList* edgeList) {
	qsort(edgeList, E, sizeof(struct EdgeList), compare);
	int custo = 0;
	for (int i = 0; i < E; i++) {
		struct Edge * asd = edgeList->array[i];
		if (!isSameSet(asd->a, asd->b)) {
			custo += CUSTO DA ARESTA;
			// contar
			unionSet(asd->a , asd->b);
		}
	}
	return custo;
}

void UnionFind(int N) {
	memset(setSize, 1, N);
	memset(rank, 0, N);
	memset(p, 0, N);
	numSets = N;
	for (int i = 0; i < N; i++)
		p[i] = i;
}

int findSet(int i) {
	return (p[i] == i) ? i : (p[i] = findSet(p[i]));
}

bool isSameSet(int i, int j) {
	return findSet(i) == findSet(j);
}

void unionSet(int i, int j) {
	if (!isSameSet(i, j)) {
		numSets--;
		int x = findSet(i), y = findSet(j);
		if (rank[x] > rank[y]) {
			p[y] = x; setSize[x] += setSize[y];
		} else {
			p[x] = y; setSize[y] += setSize[x];
			if (rank[x] == rank[y])
				rank[y]++;
		}
	}
}

int numDisjointSets() {
	return numSets;
}

int sizeOfSet(int i) {
	return setSize[findSet(i)];
}

int compare(struct Edge* edge1, struct Edge* edge2) {
	//(const void * A, const void * B)
	if (edge1->cost == edge2->cost){
		return max(edge1->a, edge1->b) > max(edge2->a, edge2->b);
	}
	return edge1->cost < edge2->cost;
}


int main() {
	int i, E, N, A, a, b, c;
	struct AdjListNode* node;
	struct Graph* gE;
	struct Graph* gEA;

	scanf("%d", &N);
	scanf("%d", &A);

	gEA = createGraph(N + 1);
	gE = createGraph(N);

	for (i = 0; i < A; i++) {
		scanf("%d %d", &a, &c);
		addEdgeToGraph(gEA, a - 1, N + 1 , c - 1);
		addEdgeToGraph(gEA, N + 1, a - 1 , c - 1);
	}

	scanf("%d", &E);

	for (i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);

		addEdgeToGraph(gEA, a - 1, b - 1 , c - 1);
		addEdgeToGraph(gEA,  b - 1, a - 1 , c - 1);

		addEdgeToGraph(gE, a - 1, b - 1 , c - 1);
		addEdgeToGraph(gE,  b - 1, a - 1 , c - 1);
	}
	printGraph(gEA);
	printGraph(gE);
	return 0;
}
