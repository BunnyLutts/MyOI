#define DEBUG
#include <cstdio>
#define MAXN 20

int max(int a, int b) {
  return a>b ? a : b;
}

int calc(int b[MAXN+1][MAXN+1], int a[MAXN+1][MAXN+1], int n) {
  int ret=0;
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      if (!(a[i][j]||!b[i][j])) {
	ret++;
      }
    }
  }
  return ret;
}

int solve(int o, int n, int a[MAXN+1][MAXN+1]) {
  static int x[MAXN+1][MAXN+1], y[MAXN+1];
  int ret=-1;
  if (o<=n) {
    y[o]=0;
    ret=max(solve(o+1, n, a), ret);
    y[o]=1;
    ret=max(solve(o+1, n, a), ret);
  } else {
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=n; j++) {
	x[i][j] = y[i]^y[j];
      }
    }
    ret = !calc(a, x, n) ? calc(x, a, n) : -1;
  }
  return ret;
}

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static int a[MAXN+1][MAXN+1];
  int t, n;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=n; j++) {
	scanf("%d", &a[i][j]);
      }
    }

    printf("%d\n", solve(1, n, a));
  }

  fcloseall();
  return 0;
}
