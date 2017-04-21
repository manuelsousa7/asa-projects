#include <bits/stdc++.h>

using namespace std;

#define FH_MAX_RANK 16
#define s second
#define f first
#define mp make_pair
#define pb push_back
#define INF numeric_limits<int>::max()

template <class T> class FibHeap;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
typedef vector<bool> vb;

int N, SKY = -1;
vector<vpii> G;
vi taken;
vb visited;
vi parent;

template <class T>

struct Node {
  T key;
  Node *l, *r, *p, *c;
  int rank;
  bool mark;
  Node(const T& x) {
    l = r = this;
    p = c = NULL;
    rank = 0;
    mark = false;
    key = x;
  }

private:
  void merge(Node<T>* o) {
    Node<T> *aux1, *aux2;
    aux1 = o->l;
    aux2 = this->r;
    o->l = this;
    this->r = o;
    aux2->l = aux1;
    aux1->r = aux2;
  }

  void add_child(Node<T> *o) {
    o->p = this;
    o->mark = false;
    if (this->c) {
      o->l = this->c;
      o->r = this->c->r;
      this->c->r->l = o;
      this->c->r = o;
    } else {
      o->l = o->r = o;
      this->c = o;
    }
    this->rank ++;
  }

  void add_bro(Node<T> *o) {
    o->p = this->p;
    o->l = this;
    o->r = this->r;
    this->r->l = o;
    this->r = o;
  }

  void clearInfo() {
    Node<T> * p = this;
    do {
      this->p = NULL;
      this->mark = false;
    } while (p != this);
  }
  friend class  FibHeap<T>;
};

template <class T>
class FibHeap {
public:
private:
  Node<T> * Hmin;
  size_t N;

  void consolidate() {
    Node<T>* Ranks[FH_MAX_RANK] = {NULL};
    for (int i = 0; i < FH_MAX_RANK; i++)
      Ranks[i] = NULL;
    Node<T> *h = Hmin, *prox, *aux = NULL;
    do {
      prox = h->r;
      while (Ranks[h->rank]) {
        aux = Ranks[h->rank];
        if (aux->key < h->key) {
          aux->add_child(h);
          Ranks[h->rank] = NULL;
          h = aux;
        } else {
          h->add_child(aux);
          Ranks[h->rank - 1] = NULL;
        }
      }
      Ranks[h->rank] = h;
      h = prox;
    } while (h != Hmin);

    Hmin = NULL;
    aux = NULL;
    for (size_t i = 0; i < FH_MAX_RANK; i++) {
      if (Ranks[i]) {
        if (Hmin != NULL) {
          Hmin->add_bro(Ranks[i]);
          if (Ranks[i]->key < Hmin->key) {
            Hmin = Ranks[i];
          }
        } else {
          Hmin = Ranks[i];
          Hmin->r = Hmin->l = Hmin;
          Hmin->p = NULL;
        }
      }
    }
  }

  void cut(Node<T> *x, Node<T> *y) {
    if (x != x->r) {
      x->r->l = x->l;
      x->l->r = x->r;
      y->c = x->r;
    } else {
      y->c = NULL;
    }
    y->rank--;
    Hmin->add_bro(x);
    x->mark = false;
  }


  void _delete_recursive(Node<T>* r) {
    if (r == NULL) return;
    Node<T> * aux = r;
    do {
      _delete_recursive(aux->c);
      aux = aux->r;
    } while (aux != r);
    delete r;
  }
public:
  FibHeap() {
    Hmin = NULL;
    N = 0;
  }
  ~FibHeap() {
    _delete_recursive(Hmin);
  }

  Node<T>* insert(const T& x) {
    Node<T>* n = new Node<T>(x);
    if (Hmin == NULL) {
      Hmin = n;
    }
    else {
      if (Hmin != NULL) {
        if (n->key < Hmin->key) {
          n->merge(this->Hmin);
          Hmin = n;
        } else {
          Hmin->merge(n);
        }
      }
    }
    N++;
    return n;
  }

  T top() {
    if (Hmin) {
      return Hmin->key;
    } else {
      return T();
    }
  }

  T pop() {
    T ret = top();
    Node<T> *aux = Hmin;
    if (Hmin != NULL) {
      if (Hmin->c != NULL) {
        Hmin->merge(Hmin->c);
        Hmin->c->clearInfo();
      }
      if (Hmin->l == Hmin) {
        Hmin = NULL;
      } else {
        Hmin->l->r = Hmin->r;
        Hmin->r->l = Hmin->l;
        Hmin = Hmin->r;
        consolidate();
      }
      N = N - 1;
    }
    delete aux;
    return ret;
  }

  bool empty() {
    return N == 0;
  }

  int size() {
    return N;
  }
};

FibHeap<pii > pq;

void dfs(int v) {
  visited[v] = true;
  for (vector<pair<int, int> >::iterator it = G[v].begin(); it != G[v].end(); it++)
    if (!visited[it->s])
      dfs(it->s);
}

bool connected(int N) {
  visited = vector<bool>(N, false);
  dfs(0);
  for (int u = 0; u < N; u++)
    if (!visited[u])
      return false;
  return true;
}


void process(int vtx) {
  taken[vtx] = 1;
  for (unsigned int j = 0; j < G[vtx].size(); j++) {
    pii v = G[vtx][j];
    if (!taken[v.s]) {
      pq.insert(pii(v.f, v.s)); //O(1+)
      parent[v.s] = vtx;
    }
  }
}

pair<int, pii > prim(int N) {
  taken.assign(N, 0);
  pii nAnE(0, 0);
  parent = vector<int>(N, -1);
  process(0);
  int cost = 0, w, u;
  while (!pq.empty()) {
    pii front = pq.top();
    pq.pop();
    u = front.s, w = front.f;
    if (!taken[u]) {
      if (parent[u] == SKY || u == SKY)
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
    if (!connected(N + 1)) {
      printf("Insuficiente\n");
      return 0;
    }

    yesA = prim(N + 1);

    for (unsigned int i = 0; i < G[SKY].size(); i++)
      G[G[SKY][i].s].erase(G[G[SKY][i].s].begin());

    G[SKY].clear();
  }

  if (E > 0) {
    if (!connected(N)) {
      printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
      return 0;
    }

    noA = prim(N);
  }

  if (A == 0 && E == 0)
    printf("0\n0 0\n");
  else if (yesA.f > noA.f)
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);
  else if (yesA.f < noA.f)
    printf("%d\n%d %d\n", yesA.f, yesA.s.f, yesA.s.s);
  else
    printf("%d\n%d %d\n", noA.f, noA.s.f, noA.s.s);

  return 0;
}