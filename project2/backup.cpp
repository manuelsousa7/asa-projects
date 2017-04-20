#include <bits/stdc++.h>

using namespace std;

//Complexidade: O(E log V)
//Dados iniciais: pair<distancia, vertice> na lista de adjacencia
//Dados finais:
//  d[v] -> distancia da aresta que liga a MST ao vertice v
//  parent[v] -> vertice a que esta ligado o vertice v
//  totalweight -> peso total da arvore


int N;
vector<vector<pair<int, int> > > G;
set< pair<int, int> > heap;
int SKY = -1;

int  totalweight;
vector<int> parent;
vector<int> d;
vector<bool> visited;


void dfs(int v) { //You can run DFS on any arbitrary node
  visited[v] = true;
  for (vector<pair<int, int> >::iterator it = G[v].begin(); it != G[v].end(); it++) {
    if (!visited[(*it).second]) {
      dfs((*it).second);
    }
  }
}


bool connected(int N) {
  visited = vector<bool>(N + 1, false);
  dfs(0);
  for (int u = 0; u < N; u++) {
    if (!visited[u]) {
      return false;
    }
  }
  return true;
}

int na = 0, ne = 0;

void add(int cost, int v, int p) {
  if (cost < d[v]) {
    parent[v] = p;
    heap.erase(pair<int, int>(d[v], v));
    d[v] = cost;
    heap.insert(pair<int, int>(d[v], v));
  }
}

void prim() {
  d = vector<int>(N + 1, 0x3f);
  parent = vector<int>(N + 1, -1);
  totalweight = 0;
  add(0, 0, -1);
  while (!heap.empty()) {
    pair<int, int> cur = *heap.begin();
    totalweight += d[cur.second];
    d[cur.second] = 0;
    if (cur.second == SKY || parent[cur.second] == SKY) {
      na++;
    } else if (parent[cur.second] != -1) {
      ne++;
    }
    heap.erase(heap.begin());
    for (unsigned int i = 0; i < G[cur.second].size(); i++)
      add(G[cur.second][i].first, G[cur.second][i].second, cur.second);
  }
}

int main() {
  int A, E;
  scanf("%d", &N);
  scanf("%d", &A);
  SKY = N;
  G = vector<vector<pair<int,int> > >(N + 1, vector<pair<int,int> > ());
 for (int i = 0; i < A; i++) {
    int a, c;
    scanf("%d %d", &a, &c);
    G[SKY].push_back(pair<int, int>(c, a - 1));
    G[a - 1].push_back(pair<int, int>(c, SKY));
  }
  scanf("%d", &E);
  for (int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    G[a - 1].push_back(pair<int, int>(c, b - 1));
    G[b - 1].push_back(pair<int, int>(c, a - 1));
  }

  prim();
  int total;
  int c = 0;
  if (!connected(N)) {
    c++;
  } else {
    total = totalweight;
  }
  totalweight = 0;
  pair<int,int> nane = make_pair(na,ne);
  na = ne = 0;
  for (int i = 0; i < G[SKY].size(); i++) {
    G[G[SKY][i].second].erase(G[G[SKY][i].second].begin());
  }
  G[SKY].clear();

  if (!connected(N)) {
    if (c == 1) {
      cout << "Insuficiente." << endl;
      return 0;
    } else {
      cout << total << endl << nane.first << " " << nane.second << endl;
      return 0;
    }
  }
  prim();

  if (totalweight > total) {
    cout << min(total, totalweight) << endl << nane.first << " " << nane.second << endl;
  } else if (totalweight < total) {
    cout << min(total, totalweight) << endl << na << " " << ne << endl;
  } else {
    if (na <= nane.first) {
      cout << min(total, totalweight) << endl << na  << " " << ne << endl;
    } else {
      cout << min(total, totalweight) << endl << nane.first  << " " << nane.second << endl;
    }
  }

  return 0;
}