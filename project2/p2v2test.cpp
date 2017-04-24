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


int main() {
  int A;
  cin >> A;
  for (int i = 0 ; i < A ; i ++) {
    pq.push(pii(i,1));
  }
  cout << pq.size() << endl;
  return 0;
}