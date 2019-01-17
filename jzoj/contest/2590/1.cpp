#define DEBUG
#include <cstdio>
#define MAXN 2500
#define MAXM 5000
#define INF 0x7fffffff
#define MODS 1000000007

using namespace std;

struct Graph {
  int n, m, ind[MAXN+1], to[MAXM*2+1], link[MAXM*2+1], val[MAXM*2+1];

  void addSide(int x, int y, int v) {
    m++;
    to[m] = y;
    val[m] = v;
    link[m] = ind[x];
    ind[x] = m;
  }

  void spfa(int s, int k, int *dis) {
    static int que[MAXN+1];
    static bool book[MAXN+1];
    for (int i=1; i<=n; i++) {
      dis[i] = INF;
    }
    dis[s] = 0;
    que[1] = s;
    book[1] = k;
    for (int h=0, t=1; h!=t; ) {
      h = h%n+1;
      int x=que[h];
      book[x] = false;
      for (int i=ind[x]; i; i=link[i]) {
	int y=to[i];
	if (dis[y]>dis[x]+val[i]+k) {
	  dis[y] = dis[x]+val[i]+k;
	  if (!book[y]) {
	    book[y] = true;
	    t = t%n+1;
	    que[t] = y;
	  }
	}
      }
    }
  }
};

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  static Graph g;
  int n, m, t;
  scanf("%d %d %d", &n, &m, &t);
  g.n = n;
  for (int i=1; i<=m; i++) {
    int u, v, l;
    scanf("%d %d %d", &u, &v, &l);
    g.addSide(u, v, l);
    g.addSide(v, u, l);
  }

  static int ans[MAXN+1];
  for (int i=0; i<=t; i++) {
    g.spfa(1, i, ans);
    for (int j=1; j<=n; j++) {
      ans[0] = (ans[0]+ans[j])%MODS;
    }
  }

  printf("%d", ans[0]);

  fcloseall();
  return 0;
}
