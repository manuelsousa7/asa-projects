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
priority_queue<pair<int, pii> > pq;
vi taken;
vector<bool> visited;

void dfs(int v) {
  visited[v] = true;
  for (vpii::iterator it = G[v].begin(); it != G[v].end(); it++)
    if (!visited[it->s])
      dfs(it->s);
}

bool connected(int N, int E) {
  if (E < N - 1)
    return false;
  visited = vector<bool>(N, false);
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
    if (!taken[v.s]) {
      pq.push(mp(-v.first, pii(min(-v.s, -vtx), -v.s)));
    }
  }
}

pair<int, pii > prim(int N) {
  taken.assign(N, 0);
  pii nAnE(0, 0);
  process(0);
  int cost = 0, w, p, u;
  while (!pq.empty()) {
    pair<int, pii> front = pq.top();
    pq.pop();
    u = -front.s.s, w = -front.f, p = -front.s.f;
    if (!taken[u]) {
      if (p == SKY)
        nAnE.f += 1;
      else
        nAnE.s += 1;
      cost += w, process(u);
    }
  }
  return mp(cost, nAnE);
}

int main() {
  int A, E;
  bool flagA = false;
  pair<int, pii > yesA(INF, mp(0, 0));
  pair<int, pii > noA(INF, mp(0, 0));
  scanf("%d", &N);
  scanf("%d", &A);

  SKY = N;
  G = vector<vector<pii > >(N + 1, vector<pii >());

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
  if (A > 0) {
    if (!connected(N + 1, A + E)) {
      printf("Insuficiente\n");
      return 0;
    }

    yesA = prim(N + 1);
    flagA = true;


    for (unsigned int i = 0; i < G[SKY].size(); i++)
      G[G[SKY][i].s].erase(G[G[SKY][i].s].begin());

    G[SKY].clear();
  }

  if (E > 0) {
    if (!connected(N, E)) {
      if (flagA) {
        printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
        return 0;
      }
    } else {
      noA = prim(N);
    }
  }

  if (A == 0 && E == 0)
    printf("Insuficiente\n");
  else if (yesA.f >= noA.f)
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);
  else if (yesA.f < noA.f)
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
  return 0;
}