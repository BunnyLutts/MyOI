#define DEBUG
#include <cstdio>
#define MAXN 2500
#define MAXK 2500

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
    dfn[o] = n++;
    for (int i=ind[o]; i; i=link[i]) {
      build(to[i]);
    }
    son[o] = n-1;
  }
};

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  static Graph g;
  static int f[MAXN+2][MAXK+1][2], s[MAXN+1], p[MAXN+1];
  int k, n;
  scanf("%d %d", &k, &n);
  k++;
  for (int i=1; i<=n; i++) {
    int r;
    scanf("%d %d %d", s+i, p+i, &r);
    g.addSide(r, i);
  }
  g.build(0);

  double ans=0;
  for (int i=n; i>=0; i--) {
    for (int j=1; j<=k; j++) {
      int x, y=0;
      double v;
      f[i][j][0] = f[i+1][j-1][0]+p[g.dfn[i]];
      f[i][j][1] = f[i+1][j-1][1]+s[g.dfn[i]];
      v = (double)f[i][j][0]/f[i][j][1];
      if (i==0 && j==k) {
	ans = v;
      }
      x = f[g.son[i]+1][j][0];
      y = f[g.son[i]+1][j][1];
      if (y!=0 && (double)x/y>v) {
	f[i][j][0] = x, f[i][j][1]=y;
      }
    }
  }

  printf("%.3lf", ans);

  fcloseall();
  return 0;
}
