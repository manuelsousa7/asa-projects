#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<vector<int> > G;
vector<int> ts;
vector<bool> visited;
vector<bool> cycleStack;

bool hasCycle = false, uniqueTopSort = true;
int zeroEdges  = 0;

int N, L;

void dfs(int u) {
	visited[u] = true;
	cycleStack[u] = true;
	for (vector <int>::iterator v = G[u].begin(); v != G[u].end(); v++) {
		if (!visited[*v]) {
			dfs(*v);
		} else if (cycleStack[*v]) {
			hasCycle = true;
			return;
		}
	}
	cycleStack[u] = false;
	ts.push_back(u);
}

int main() {
	scanf("%d %d", &N, &L);

	G = vector<vector<int> >(N + 1, vector<int>());
	visited = vector<bool>(N + 1, false);
	cycleStack = vector<bool>(N + 1, false);

	for (int i = 0; i < L; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		G[x - 1].push_back(y - 1);
	}
	for (int u = 0; u < N; u++)
		if (!visited[u])
			dfs(u);

	if (hasCycle) {
		printf("Incoerente\n");
	} else {
		for (vector <int>::reverse_iterator v = ts.rbegin(); v + 1 != ts.rend(); v++) {
			if (find(G[*v].begin(), G[*v].end(), *(v + 1)) == G[*v].end()) {
				uniqueTopSort = false;
			}
		}
		if (uniqueTopSort) {
			for (vector <int>::reverse_iterator v = ts.rbegin(); v != ts.rend(); v++)
				cout << *v + 1 << (v + 1 == ts.rend() ? "\n" : " ");
		} else {
			printf("Insuficiente\n");
		}
	}
	return 0;
}