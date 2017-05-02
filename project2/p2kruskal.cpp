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

class UnionFind {
private:
  vi p, rank, setSize;
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
  }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) {
    if (!isSameSet(i, j)) {
      numSets--;
      int x = findSet(i), y = findSet(j);
      if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
      else                   {
        p[x] = y; setSize[y] += setSize[x];
        if (rank[x] == rank[y]) rank[y]++;
      }
    }
  }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};


bool compara(const pair<int, pii >& a, const pair<int, pii >& b) {
  if (a.first == b.first) {
    return max(b.s.f, b.s.s) > max(a.s.f, a.s.s);
  }
  return a.first < b.first;
}

pair<int, pii > kruskal(int N, int E, vector< pair<int, pii> > &EdgeList) {
  sort(EdgeList.begin(), EdgeList.end(), compara);
  pii nAnE(0, 0);
  int mst_cost = 0;
  UnionFind UF(N);
  for (int i = 0; i < E; i++) {
    pair<int, pii> front = EdgeList[i];
    if (!UF.isSameSet(front.second.first, front.second.second)) {
      mst_cost += front.first;
      if (front.s.f == SKY || front.s.s == SKY)
        nAnE.f += 1;
      else
        nAnE.s += 1;
      UF.unionSet(front.second.first, front.second.second);
    }
  }
  return mp(mst_cost, nAnE);
}

int main() {
  int A, E;
  bool flagA = false;
  pair<int, pii > yesA(INF, mp(0, 0));
  pair<int, pii > noA(INF, mp(0, 0));
  vector< pair<int, pii> > EdgeList;
  vector< pair<int, pii> > EdgeList2;
  scanf("%d", &N);
  scanf("%d", &A);

  SKY = N;


  for (int i = 0; i < A; i++) {
    int a, c;
    scanf("%d %d", &a, &c);
    EdgeList.push_back(make_pair(c, mp(a - 1, SKY)));
  }

  scanf("%d", &E);

  for (int i = 0; i < E; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    EdgeList.push_back(make_pair(c, mp(a - 1, b - 1)));
    EdgeList2.push_back(make_pair(c, mp(a - 1, b - 1)));
  }
  if (A > 0) {
    if (!connected(N + 1, A + E)) {
      printf("Insuficiente\n");
      return 0;
    }

    yesA = kruskal(N + 1, A + E, EdgeList);
    flagA = true;


  }

  if (E > 0) {
    if (!connected(N, E)) {
      if (flagA) {
        printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
        return 0;
      }
    } else {
      noA = kruskal(N, E, EdgeList2);

      if (!flagA) {
        printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);
        return 0;
      }
    }
  }

  if ( (A == 0 && E == 0) || (yesA.f == INF && noA.f == INF))
    printf("Insuficiente\n");
  else if (yesA.f >= noA.f)
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);
  else if (yesA.f < noA.f)
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
  return 0;
}