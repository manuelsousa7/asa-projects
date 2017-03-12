#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef vector <int>::reverse_iterator vri;
typedef vector <int>::iterator vi;

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
	for (vi v = G[u].begin(); v != G[u].end(); v++) {
		if (!visited[*v]) {
			dfs(*v);
		} else if (cycleStack[*v]) {
			hasCycle = true;
			return;
		}
	}

	if (!ts.empty() && find(G[u].begin(), G[u].end(), ts.back()) == G[u].end()) {
		uniqueTopSort = false;
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
		if (uniqueTopSort) {
			for (vri v = ts.rbegin(); v != ts.rend(); v++)
				cout << *v + 1 << (v + 1 == ts.rend() ? "\n" : " ");
		} else {
			printf("Insuficiente\n");
		}
	}
	return 0;
}