#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef vector <int>::reverse_iterator vri;
typedef vector <int>::iterator vi;

vector<vector<int> > G; //grafo
vector<int> ts;//ordem topologica
vector<bool> visited;//vertices visitados
vector<bool> cycleStack;//ciclos no grafo

bool hasCycle = false;//Tem ciclos?
bool uniqueTopSort = true;//Tem uma ordenacao topologica unica?

int N, L;

/* dfs: Visita todos os vertices de um grafo, e deteta existencia de ciclos
 * Devolve: nada
 * Ordenacao topologica baseada em pesquisa em profundidade (DFS)
 */
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
	cycleStack[u] = false;
	ts.push_back(u);
}

int main() {
	/* Processa dados de entrada */
	scanf("%d %d", &N, &L);

	G = vector<vector<int> >(N + 1, vector<int>());
	visited = vector<bool>(N + 1, false);
	cycleStack = vector<bool>(N + 1, false);

	for (int i = 0; i < L; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		G[x - 1].push_back(y - 1);
	}

	/* Chama DFS em todos os vertices nao visitados */
	for (int u = 0; u < N; u++)
		if (!visited[u])
			dfs(u);

	/* Se tiver ciclos no grafo entao e Incoerente */
	if (hasCycle) {
		printf("Incoerente\n");
	} else {
		/* Verifica se dois vertices consecutivos na ordenacao topologica
		estao ligados entre si. Se nao estiverem entao nao existe uma ordem unica */
		for (vector <int>::reverse_iterator v = ts.rbegin(); v + 1 != ts.rend(); v++) {
			if (find(G[*v].begin(), G[*v].end(), *(v + 1)) == G[*v].end()) {
				uniqueTopSort = false;
				break;
			}
		}
		/* Se existir uma ordenacao topologica unica imprime os resultados,
		caso contrario nao e possivel imprimir uma ordem unica */
		if (uniqueTopSort) {
			for (vri v = ts.rbegin(); v != ts.rend(); v++)
				cout << *v + 1 << (v + 1 == ts.rend() ? "\n" : " ");
		} else {
			printf("Insuficiente\n");
		}
	}
	return 0;
}