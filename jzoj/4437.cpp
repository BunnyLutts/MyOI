#define DEBUG
#include <cstdio>
#define MAXN 1000

using namespace std;

struct Set {
  int fa, v, tot[2];
};

int max(int a, int b) {
  return a>b ? a : b;
}

void initSet(Set *set, int n) {
  for (int i=1; i<=n; i++) {
    set[i].fa = i;
    set[i].v = 0;
    set[i].tot[0] = 1, set[i].tot[1] = 0;
  }
}

int getFa(Set *set, int o) {
  int f=set[o].fa, v=set[o].v;
  if (f!=o) {
    set[f].tot[v] += set[o].tot[0];
    set[f].tot[!v] += set[o].tot[1];
    set[o].tot[0] = set[o].tot[1] = 0;
    set[o].fa = getFa(set, f);
    set[o].v = set[f].v^v;
  }
  return set[o].fa;
}

bool merge(Set *set, int x, int y) {
  if (getFa(set, x)!=getFa(set, y)) {
    int t=getFa(set, x);
    set[t].fa = y;
    set[t].v = !set[x].v;
    return true;
  } else {
    return set[x].v!=set[y].v;
  }
}

int main() {
#ifdef DEBUG
  freopen("4437.in", "r", stdin);
  freopen("4437.out", "w", stdout);
#endif

  static int a[MAXN+1][MAXN+1];
  static bool f[MAXN+1][MAXN+1];
  static Set set[MAXN+1];
  static bool book[MAXN+1];
  int t, n, sum, size;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    scanf("%d", &n);
    bool flag=true;
    initSet(set, n);
    sum = 0;
    for (int i=1; i<=n; i++) {
      book[i] = false;
      for (int j=1; j<=n; j++) {
	f[i][j] = false;
	scanf("%d", &a[i][j]);
	sum += a[i][j];
	if (a[i][j]) {
	  if (!merge(set, i, j)) {
	    flag = false;
	  }
	}
      }
    }
    if (!flag) {
      printf("-1\n");
      continue;
    }
    for (int i=1; i<=n; i++) {
      getFa(set, i);
    }

    f[0][0] = true;
    size=0;
    for (int i=1; i<=n; i++) {
      int o=getFa(set, i);
      if (!book[o]) {
	book[o] = true;
	size++;
	for (int j=0; j<=n; j++) {
	  if (j>=set[o].tot[0]) {
	    f[size][j] = f[size][j] || f[size-1][j-set[o].tot[0]];
	  }
	  if (j>=set[o].tot[1]) {
	    f[size][j] = f[size][j] || f[size-1][j-set[o].tot[1]];
	  }
	}
      }
    }

    int ans=0;
    for (int i=1; i<=n; i++) {
      if (f[size][i]) {
	ans = max(ans, i*(n-i));
      }
    }
    printf("%d\n", 2*ans-sum);
  }

  fcloseall();
  return 0;
}
