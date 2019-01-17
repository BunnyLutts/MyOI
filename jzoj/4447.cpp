#define DEBUG
#include <cstdio>
#include <cmath>
#include <cassert>
#define MODS 1000000007
#define INF 0x7ffffff
#define MAXN 2500
#define MAXM 5000

using namespace std;

typedef unsigned long long ull;

int min(int a, int b) {
  return a<b ? a : b;
}

struct Line {
  int k, a;
};

struct Graph {
  int n, m=0, ind[MAXN+1], to[MAXM*2], val[MAXM*2], link[MAXM*2];
  
  void addSide(int u, int v, int l) {
    m++;
    to[m] = v;
    val[m] = l;
    link[m] = ind[u];
    ind[u] = m;
  }

  void dp(int s, int f[MAXN+1][MAXM+1]) {
    for (int i=1; i<=n; i++) {
      for (int j=0; j<=m/2; j++) {
	f[i][j] = INF;
      }
    }
    f[s][0] = 0;
    for (int j=0; j<m/2; j++) {
      for (int i=1; i<=n; i++) {
	for (int k=ind[i]; k; k=link[k]) {
	  f[to[k]][j+1] = min(f[i][j]+val[k], f[to[k]][j+1]);
	}
      }
    }
  }
};

double calcX(const Line *a, const Line *b) {
  assert(b->k!=a->k);
  return (double)(a->a-b->a)/(b->k-a->k);
}

ull calcY(const Line *a, long long x) {
  return a->k*x+a->a;
}

bool isDown(const Line *a, const Line *b, const Line *c) {
  if (b->k==c->k) {
    return b->a<=c->a;
  } else {
    double x, y;
    x = calcX(a, b), y = a->k*x+a->a;
    if (x*c->k+c->a==y) {
      return b->k<=c->k;
    } else if (x*c->k+c->a>y) {
      return true;
    }
  }
  return false;
}

int main() {
#ifdef DEBUG
  freopen("4447.in", "r", stdin);
  freopen("4447.out", "w", stdout);
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

  static int f[MAXN+1][MAXM+1];
  g.dp(1, f);
  static Line que[MAXM+1];
  ull ans=0;
  for (int i=1; i<=n; i++) {
    int head=1, tail=0;
    Line temp;
    for (int j=m; j>=0; j--) {
      if (f[i][j]<INF) {
	temp.a = f[i][j];
	temp.k = j;
	for (; (head+1<=tail && isDown(&que[tail-1], &temp, &que[tail])) || (head<=tail && que[tail].a>=temp.a && que[tail].k>=temp.k); tail--);
	que[++tail] = temp;
      }
    }
    for (int j=head; j<=tail; j++) {
      int x1=0, x2=t;
      if (j>head) {
	x1 = floor(calcX(&que[j-1], &que[j]))+1;
      }
      if (j<tail) {
	x2 = min(x2, floor(calcX(&que[j], &que[j+1])));
      }
      ans = (((calcY(que+j, x1)%MODS+calcY(que+j, x2)%MODS)%MODS*(x2-x1+1LL)%MODS*500000004LL%MODS)+ans)%MODS;
      if (j<tail && floor(calcX(que+j, que+j+1))>=t) {
	break;
      }
    }
  }

  printf("%llu", ans);

  fcloseall();
  return 0;
}
