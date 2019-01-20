#define DEBUG
#include <cstdio>
#define MAXN 5000
#define INF 0x7ffffff
#define MODS 1000000007

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

class Graph {
public:
  int n, m=0, ind[MAXN+1], to[MAXN*2-1], link[MAXN*2-1], f[MAXN+1], leaf[MAXN+1];
  bool book[MAXN+1];
  
  void addSide(int u, int v) {
    m++;
    to[m] = v;
    link[m] = ind[u];
    ind[u] = m;
  }

  void findLeaf(int o, int fa) {
    book[o] = true;
    for (int i=ind[o]; i; i=link[i]) {
      if (to[i]!=fa) {
	findLeaf(to[i], o);
	book[o] = false;
      }
    }
    if (book[o]) {
      leaf[++leaf[0]] = o;
    }
  }

  int solve(int o, int fa, int player) {
    if (!book[o]) {
      f[o] = player ? INF : 0;
      for (int i=ind[o]; i; i=link[i]) {
	if (to[i]!=fa) {
	  f[o] = player ? min(f[o], solve(to[i], o, !player)) : max(f[o], solve(to[i], o, !player));
	}
      }
    }
    return f[o];
  }
};

long long solve(Graph *g, int o) {
  static bool book[MAXN+1];
  long long ret=0;
  if (o<=g->leaf[0]) {
    for (int i=1; i<=g->leaf[0]; i++) {
      if (!book[i]) {
	book[i] = true;
	g->f[g->leaf[o]] = i;
	ret = (ret+solve(g, o+1))%MODS;
	book[i] = false;
      }
    }
    return ret;
  } else {
    return g->solve(1, 0, 0)%MODS;
  }
}

int main() {
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);

  static Graph g;
  int n;
  scanf("%d", &n);
  for (int i=1; i<n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g.addSide(u, v);
    g.addSide(v, u);
  }
  g.findLeaf(1, 0);

  printf("%lld", solve(&g, 1));

  fcloseall();
  return 0;
}
