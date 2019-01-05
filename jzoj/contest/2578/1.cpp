#define DEBUG
#include <cstdio>
#define MAXN 500000
#define MAXM 500000

using namespace std;

struct Graph {
  int n, m, s, ind[MAXN+1], to[MAXM+1], link[MAXM+1];
  long long val[MAXN+1];
  bool flag[MAXN+1];
  
  void addSide(int u, int v) {
    m++;
    to[m] = v;
    link[m] = ind[u];
    ind[u] = m;
  }

  void tarjin() {
  }
};

long long max(long long a, long long b) {
  return a>b ? a : b;
}

void copy(Graph *s, Graph *t) {
  *t = *s;
} 

long long solve(Graph *g) {
  static int que[MAXN+1];
  static long long ans[MAXN+1];
  static bool book[MAXN+1];
  for (int i=1; i<=g->n; i++) {
    ans[i] = 0;
  }
  que[1] = g->s;
  book[g->s] = true;
  ans[g->s] = g->val[g->s];
  ans[0] = 0;
  for (int h=0, t=1; h!=t; ) {
    h = h%g->n+1;
    book[que[h]] = false;
    int x=que[h];
    if (g->flag[x]) {
      ans[0] = max(ans[0], ans[x]);
    }
    for (int i=g->ind[x]; i; i=g->link[i]) {
      int y = g->to[i];
      if (ans[y]<ans[x]+g->val[y]) {
	ans[y] = ans[x]+g->val[y];
	if (!book[y]) {
	  t = t%g->n+1;
	  que[t] = y;
	  book[y] = true;
	}
      }
    }
  }
  return ans[0];
}

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  static Graph input, g;
  int n, m;
  scanf("%d %d", &n, &m);
  input.n = n;
  for (int i=1; i<=m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    input.addSide(u, v);
  }
  for (int i=1; i<=n; i++) {
    scanf("%lld", &input.val[i]);
  }
  int p;
  scanf("%d %d", &input.s, &p);
  for (int i=1; i<=n; i++) {
    int t;
    scanf("%d", &t);
    input.flag[t] = true;
  } 

  input.tarjin();
  copy(&input, &g);

  printf("%lld", solve(&g));

  fclose(stdin);
  fclose(stdout);
  return 0;
}
