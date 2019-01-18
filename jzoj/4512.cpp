#define DEBUG
#include <cstdio>
#include <cmath>
#define INF 0x7fffffff
#define EPS 0.00005
#define MAXN 2510
#define MAXK 2510
#define MAXP 10000

using namespace std;

struct Graph {
  int n=0, m=0, ind[MAXN+1], to[MAXN], link[MAXN], dfn[MAXN+1], son[MAXN+1], map[MAXN+1];

  void addSide(int fa, int s) {
    m++;
    to[m] = s;
    link[m] = ind[fa];
    ind[fa] = m;
  }

  void build(int o) {
    dfn[o] = n++;
    son[dfn[o]]=dfn[o], map[dfn[o]] = o;
    for (int i=ind[o]; i; i=link[i]) {
      build(to[i]);
      son[dfn[o]] = son[dfn[to[i]]];
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
    double val=(double)p[g->map[i]]-z*s[g->map[i]];
    f[i][0] = f[g->son[i]+1][0];
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
  printf("%.3lf", nearbyint(ans*1000)/1000);

  fcloseall();
  return 0;
}
