#include <bits/stdc++.h>

using namespace std;




int main() {
  priority_queue < pair<int, pair<int, int> > > pq;
  pq.push(make_pair(-2, make_pair(-2, -4)));
  pq.push(make_pair(-2, make_pair(-1, -3)));
  pq.push(make_pair(-2, make_pair(-4, -1)));
  pq.push(make_pair(-2, make_pair(-2, -3)));
  pq.push(make_pair(-2, make_pair(-3, -4)));
  while (!pq.empty()) {
    pair<int, pair<int, int> > i = pq.top();
    pq.pop();
    printf("%d (%d,%d)\n", i.first, i.second.first, i.second.second);
  }
  return 0;
}