#include <bits/stdc++.h>

using namespace std;

#define s second
#define f first
#define mp make_pair
#define pb push_back
#define INF numeric_limits<int>::max()

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;

int N, SKY = -1;
vector<vpii > G;
priority_queue<pii > pq;
vi taken;
vector<bool> visited;
vector<int> parent;

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


void process(int vtx) {
  taken[vtx] = 1;
  for (int j = 0; j < (int)G[vtx].size(); j++) {
    pii v = G[vtx][j];
    if (!taken[v.second]) {
      pq.push(pii(-v.first, -v.second));
      parent[v.second] = vtx;
    }
  }
}

pair<int, pii > prim(int N) {
  taken.assign(N, 0);
  parent = vector<int>(N, -1);
  process(0);
  int mst_cost = 0, w, u, na = 0, ne = 0;
  while (!pq.empty()) {
    pii front = pq.top();
    pq.pop();
    u = -front.second, w = -front.first;
    if (!taken[u]) {
      if (parent[u] == SKY || u == SKY)
        na += 1 ;
      else
        ne += 1;
      mst_cost += w, process(u);
    }
  }
  return mp(mst_cost, mp(na, ne));
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

  pair<int, pii > yesA = prim(N + 1);

  //clear airports
  for (unsigned int i = 0; i < G[SKY].size(); i++)
    G[G[SKY][i].s].erase(G[G[SKY][i].s].begin());

  G[SKY].clear();

  if (!connected(N)) {
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
    return 0;
  }

  pair<int, pii > noA = prim(N);

  if (yesA.f > noA.f)
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);
  else if (yesA.f < noA.f)
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
  else
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);

  return 0;
}