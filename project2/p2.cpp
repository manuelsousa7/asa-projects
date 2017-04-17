#include <bits/stdc++.h>

using namespace std;

#define NVERTICES 10010
vector< pair<int, int> > G[NVERTICES];
set< pair<int, int> > heap;
int d[NVERTICES], parent[NVERTICES], totalweight;
unordered_map<int, int> airports;

void add(int v, int p, int cost) {
	if (cost < d[v]) {
		parent[v] = p;
		heap.erase(pair<int, int>(d[v], v));
		d[v] = cost;
		heap.insert(pair<int, int>(d[v], v));
	}
}

void prim(int root) {
	memset(d, 0x3f, sizeof(d)); // 0x3f3f3f3f > 1.000.000.000
	memset(parent, -1, sizeof(parent));
	totalweight = 0;
	add(root, -1, 0);
	while (!heap.empty()) {
		pair<int, int> cur = *heap.begin();
		totalweight += d[cur.second];
		d[cur.second] = 0; //vertex in MST
		heap.erase(heap.begin()); //pop closest vertex
		for (unsigned int i = 0; i < G[cur.second].size(); i++) //for each neighbour
			add(G[cur.second][i].second, cur.second, G[cur.second][i].first); // add or refresh distance
	}
}


int main() {
	int N, A, E;
	scanf("%d", &N);
	scanf("%d", &A);
	for (int i = 0; i < A; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		airports[a] = b;
	}
	scanf("%d", &E);
	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		G[a - 1].push_back(pair<int, int>(c, b - 1));
		G[b - 1].push_back(pair<int, int>(c, a - 1));
	}
	prim(0);
	cout << totalweight << endl;
	return 0;
}


