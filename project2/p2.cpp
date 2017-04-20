#include <bits/stdc++.h>

using namespace std;

#define s second
#define f first
#define mp make_pair
#define pb push_back
#define INF numeric_limits<int>::max()

typedef pair<int, int> pii;

int N, SKY = -1;
vector<vector<pii > > G;
set<pii > heap;
vector<int> parent;
vector<int> d;
vector<bool> visited;

void dfs(int v) {
  visited[v] = true;
  for (vector<pair<int, int> >::iterator it = G[v].begin(); it != G[v].end(); it++)
    if (!visited[it->s])
      dfs(it->s);
}

bool connected(int N) {
  visited = vector<bool>(N + 2, false);
  dfs(0);
  for (int u = 0; u < N; u++)
    if (!visited[u])
      return false;
  return true;
}

void add(int cost, int v, int p) {
  if (cost < d[v] || (cost == d[v] && parent[v] == SKY)) {
    parent[v] = p;
    heap.erase(pair<int, int>(d[v], v));
    d[v] = cost;
    heap.insert(pair<int, int>(d[v], v));
  }
}

pair<int, pii > prim() {
  int na = 0, ne = 0, totalweight = 0;
  d = vector<int>(N + 1, INF);
  parent = vector<int>(N + 1, -1);
  add(0, 0, -1);
  while (!heap.empty()) {
    pii cur = *heap.begin();
    totalweight += d[cur.s];
    d[cur.s] = 0;
    if (cur.s == SKY || parent[cur.s] == SKY)
      na++;
    else if (parent[cur.s] != -1)
      ne++;

    heap.erase(heap.begin());
    for (unsigned int i = 0; i < G[cur.s].size(); i++)
      add(G[cur.s][i].f, G[cur.s][i].s, cur.s);
  }
  return mp(totalweight, mp(na, ne));
}

int main() {
  int A, E;

  scanf("%d", &N);
  scanf("%d", &A);

  SKY = N;
  G = vector<vector<pii > >(N + 1, vector<pii > ());

  for (int i = 0; i < A; i++) {
    int a, c;
    scanf("%d %d", &a, &c);
    G[SKY].pb(pii(c, a - 1));
    G[a - 1].pb(pii(c, SKY));
  }

  scanf("%d", &E);

  for (int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    G[a - 1].pb(pii(c, b - 1));
    G[b - 1].pb(pii(c, a - 1));
  }

  if (!connected(N + 1) && A > 0) {
    cout << "Insuficiente" << endl;
    return 0;
  }

  pair<int, pii > yesA = prim();

  //clear airports
  for (unsigned int i = 0; i < G[SKY].size(); i++)
    G[G[SKY][i].s].erase(G[G[SKY][i].s].begin());

  G[SKY].clear();

  if (!connected(N)) {
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
    return 0;
  }

  pair<int, pii > noA = prim();

  if (yesA.f > noA.f)
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);
  else if (yesA.f < noA.f)
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
  else
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);


  return 0;
}