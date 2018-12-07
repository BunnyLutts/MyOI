#define DEBUG
#include <cstdio>
#include <algorithm>
#define INF 0x7ffffff
#define MAXN 100000

using namespace std;

int n, m, ind[MAXN+1], to[MAXN], link[MAXN], size[MAXN+1], maxt[MAXN+1], mint[MAXN+1];
bool book[MAXN+1];

void addSide(int u, int v) {
  m++;
  to[m] = v;
  link[m] = ind[u];
  ind[u] = m;
  book[v] = true;
}

int getRoot() {
  for (int i=1; i<=n; i++) {
    if (!book[i]) {
      return i;
    }
  }
  throw -1;
}

void build(int o) {
  size[o] = 1, maxt[o] = o, mint[o] = o;
  for (int i=ind[o]; i; i=link[i]) {
    build(to[i]);
    size[o] += size[to[i]];
    maxt[o] = max(maxt[o], maxt[to[i]]);
    mint[o] = min(mint[o], mint[to[i]]);
  }
}

int getAns() {
  int ret=0;
  for (int i=1; i<=n; i++) {
    if (maxt[i]-mint[i]+1==size[i]) {
      ret++;
    }
  }
  return ret;
}

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i=1; i<n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    addSide(u, v);
  }

  build(getRoot());
  printf("%d", getAns());

  fclose(stdin);
  fclose(stdout);
  return 0;
}
