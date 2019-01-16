#define DEBUG
#include <cstdio>
#define MAXN 200000
#define MAXM 400000
#define MAXK 18

struct Graph {
  int n, m, ind[MAXN+1], to[2*MAXM+1], link[2*MAXM+1], f[MAXN+1][MAXK+1], dep[MAXN+1];

  void addSide(int u, int v) {
    m++;
    to[m] = v;
    link[m] = ind[u];
    ind[u] = m;
  }

  void tarjin() {
  }

  void makeDep(int o, int fa) {
    dep[o] = dep[fa]+1;
    for (int i=ind[o]; i; i=link[i]) {
      if (to[i]!=fa) {
	makeDep(to[i], o);
	f[to[i]][0] = o;
      }
    }
  }

  void build() {
    makeDep(1, 0);
    for (int j=1; j<=MAXK; j++) {
      for (int i=1; i<=n; i++) {
	f[i][j] = f[f[i][j-1]][j-1];
      }
    }
  }

  int lca(int u, int v) {
    int ret;
    if (dep[u]<dep[v]) {
      ret = u, u = v, v = ret;
    }
    ret=0;
    for (int i=MAXK; i>=0; i--) {
      if (dep[f[u][i]]>=dep[v]) {
	ret += 1<<i;
	u = f[u][i];
      }
    }
    if (u==v) {
      return ret;
    }
    for (int i=MAXK; i>=0; i--) {
      if (f[u][i]!=f[v][i]) {
	ret += 1<<(i+1);
	u = f[u][i], v = f[v][i];
      }
    }
    return ret;
  }
};

void copy(Graph *s, Graph *t) {
  *t = *s;
}

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static Graph g, tree;
  int n, m, q;
  scanf("%d %d %d", &n, &m, &q);
  g.n = n;
  for (int i=1; i<=m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g.addSide(u, v);
  }
  g.tarjin();
  copy(&g, &tree);
  tree.build();

  long long ans=0;
  for (int i=1; i<=q; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    long long t=tree.lca(x, y)+1;
    ans += t*(t-1);
  }
  printf("%lld", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
