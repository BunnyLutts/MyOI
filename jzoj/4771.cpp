#define DEBUG
#include <cstdio>
#define MAXN 500000
#define MAXM 500000

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int getFa(int *set, int o) {
  if (set[o]!=o) {
    set[o] = getFa(set, set[o]);
  }
  return set[o];
}

void merge(int *set, int to, int from) {
  set[getFa(set, from)] = to;
}

void push(int *stack, int v) {
  stack[++stack[0]] = v;
}

int pop(int *stack) {
  return stack[stack[0]--];
}

struct Graph {
  int n, m, s, ind[MAXN+1], to[MAXM+1], link[MAXM+1], set[MAXN+1];
  long long val[MAXN+1];
  bool flag[MAXN+1];
  
  void init(int n) {
    for (int i=1; i<=n; i++) {
      set[i] = i;
    }
    this->n = n;
  }

  void addSide(int u, int v) {
    m++;
    to[m] = v;
    link[m] = ind[u];
    ind[u] = m;
  }

  void tarjin(int o) {
    static int dfn[MAXN+1], low[MAXN+1], stack[MAXN+1];
    static bool book[MAXN+1];
    low[o] = dfn[o] = ++dfn[0];
    book[o] = true;
    push(stack, o);
    for (int i=ind[o]; i; i=link[i]) {
      if (!book[to[i]]) {
	tarjin(to[i]);
      }
      low[i] = min(dfn[to[i]], low[i]);
    }
    if (low[o]==dfn[o]) {
      
    }
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

  static Graph g;
  int n, m;
  scanf("%d %d", &n, &m);
  g.n = n;
  for (int i=1; i<=m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g.addSide(u, v);
  }
  for (int i=1; i<=n; i++) {
    scanf("%lld", &g.val[i]);
  }
  int p;
  scanf("%d %d", &g.s, &p);
  for (int i=1; i<=n; i++) {
    int t;
    scanf("%d", &t);
    g.flag[t] = true;
  } 

  g.tarjin(int o)

  printf("%lld", solve(&g));

  fclose(stdin);
  fclose(stdout);
  return 0;
}
