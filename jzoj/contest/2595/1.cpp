#define DEBUG
#include <cstdio>
#define MAXM 100000

int calc(int x, int n, int a, int b, int p, int *s, int m) {
  int ret=0;
  for (int i=0; i<m; i++) {
    ret += s[i]!=((a*(x+i)%n+b)%n>=p);
  }
  return ret;
}

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  static int s[MAXM+1];
  int n, a, b, p, m, q;
  scanf("%d %d %d %d %d", &n, &a, &b, &p, &m);
  for (int i=0; i<m; i++) {
    scanf("%1d", s+i);
  }
  scanf("%d", &q);
  for (int i=1; i<=q; i++) {
    int x;
    char c[7];
    scanf(" %s %d", c, &x);
    if (c[0]=='Q') {
      printf("%d\n", calc(x, n, a, b, p, s, m));
    } else {
      s[x] = !s[x];
    }
  }

  fcloseall();
  return 0;
}
