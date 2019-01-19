#define DEBUG
#include <cstdio>
#define MAXN 20000
#define MAXLOGN 15

using namespace std;

int max(int a, int b) {
  return a>b ? a : b;
}

class Graph {
public:
  int n, m, ind[MAXN+1], to[MAXN*2-1], val[MAXN*2-1], link[MAXN*2-1], dep[MAXN+1], f[MAXN+1][MAXLOGN+1][2];

  void init(int n) {
    this->n = n;
    m=0;
    for (int i=1; i<=n; i++) {
      ind[i] = 0;
    }
  }

  void addSide(int u, int v, int l) {
    m++;
    to[m] = v;
    val[m] = l;
    link[m] = ind[u];
    ind[u] = m;
  }

  void makeDep(int o, int fa) {
    dep[o] = dep[fa]+1;
    for (int i=ind[o]; i; i=link[i]) {
      if (to[i]!=fa) {
	f[to[i]][0][0] = o;
	f[to[i]][0][1] = val[i];
	makeDep(to[i], o);
      }
    }
  } 

  void build() {
    makeDep(1, 0);

    for (int j=1; j<=MAXLOGN; j++) {
      for (int i=1; i<=n; i++) {
	int x=i, y=f[i][j-1][0];
	f[i][j][0] = f[y][j-1][0];
	f[i][j][1] = max(f[x][j-1][1], f[y][j-1][1]);
      }
    }
  }

  int lca(int u, int v) {
    int ret;
    if (dep[u]<dep[v]) {
      ret=u, u=v, v=ret;
    }
    ret = 0;
    for (int i=MAXLOGN; i>=0; i--) {
      if (dep[f[u][i][0]]>=dep[v]) {
	ret = max(ret, f[u][i][1]);
	u = f[u][i][0];
      }
    }
    if (u==v) {
      return ret;
    }
    for (int i=MAXLOGN; i>=0; i--) {
      if (f[u][i][0]!=f[v][i][0]) {
	ret = max(ret, max(f[u][i][1], f[v][i][1]));
	u = f[u][i][0], v = f[v][i][0];
      }
    }
    return max(ret, max(f[u][0][1], f[v][0][1]));
  }
};

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    static Graph g;
    int n, ans=0;
    scanf("%d", &n);
    g.init(n);
    for (int i=1; i<n; i++) {
      int u, v, l;
      scanf("%d %d %d", &u, &v, &l);
      g.addSide(u, v, l);
      g.addSide(v, u, l);
      ans += l;
    }
    g.build();
    for (int i=1; i<=n-1; i++) {
      for (int j=i+1; j<=n; j++) {
	if (g.f[i][0][0]!=j && g.f[j][0][0]!=i) {
	  ans += g.lca(i, j)+1;
	}
      }
    }
    printf("%d\n", ans);
  }

  fcloseall();
  return 0;
}
