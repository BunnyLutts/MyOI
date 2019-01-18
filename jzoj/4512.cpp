#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define EPS 0.0001
#define MAXN 2500
#define MAXK 2500
#define MAXP 10000

using namespace std;

struct Graph {
  int n=0, m=0, ind[MAXN+1], to[MAXN], link[MAXN], dfn[MAXN+1], son[MAXN+1];

  void addSide(int fa, int s) {
    m++;
    to[m] = s;
    link[m] = ind[fa];
    ind[fa] = m;
  }

  void build(int o) {
    son[o] = dfn[o] = n++;
    for (int i=ind[o]; i; i=link[i]) {
      build(to[i]);
      son[o] = son[to[i]];
    }
  }
};

double max(double x, double y) {
  return x>y ? x : y;
}

bool solve(double z, int *p, int *s, Graph *g, int n, int k) {
  static double f[MAXN+2][MAXK+1];
  for (int i=0; i<=n+1; i++) {
    for (int j=1; j<=k; j++) {
      f[i][j] = -INF;
    }
  }
  for (int i=n; i>=0; i--) {
    double val=(double)p[g->dfn[i]]-z*s[g->dfn[i]];
    for (int j=1; j<=k; j++) {
      f[i][j] = max(f[i+1][j-1]+val, f[g->son[i]+1][j]);
    }
  }
  return f[0][k]>=0;
}

int main() {
#ifdef DEBUG
  freopen("4512.in", "r", stdin);
  freopen("4512.out", "w", stdout);
#endif

  static Graph g;
  static int s[MAXN+1], p[MAXN+1];
  int k, n;
  scanf("%d %d", &k, &n);
  k++;
  for (int i=1; i<=n; i++) {
    int r;
    scanf("%d %d %d", s+i, p+i, &r);
    g.addSide(r, i);
  }
  g.build(0);

  double ans=-1;
  for (double l=0, r=MAXP, mid; l<=r; ) {
    mid = (l+r)/2;
    if (solve(mid, p, s, &g, n, k)) {
      ans = mid;
      l = mid+EPS;
    } else {
      r = mid-EPS;
    }
  }
  printf("%.3lf", ans);

  fcloseall();
  return 0;
}
