#define DEBUG
#include <cstdio>
#define INF 0x7ffffffffffff
#define MAXN 3000

using namespace std;

long long min(long long a, long long b) {
  return a<b ? a : b;
}

int main() {
#ifdef DEBUG
  freopen("4517.in", "r", stdin);
  freopen("4517.out", "w", stdout);
#endif

  static long long a[MAXN+1], f[MAXN+1], g[MAXN+1][MAXN+1], suf[MAXN+1];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%lld", a+i);
    suf[i] = suf[i-1]+a[i];
    f[i] = INF;
  }
  for (int t=1; t<=n; t++) {
    for (int i=1; i+t-1<=n; i++) {
      if (t>1) {
	int j=i+t-1;
	g[i][j] = min(g[i+1][j]+(suf[j]-suf[i])*2, g[i+1][j]+suf[j]-suf[i]+a[i]*(j-i)*3);
      }
    }
  }
  for (int i=1; i<=n; i++) {
    f[i] = g[1][i]+(suf[n]-suf[i])*((i-1)*4+1);
    for (int j=1; j<i; j++) {
      f[i] = min(f[j]+g[j+1][i]+(suf[n]-suf[i])*((i-j-1)*4+1)+suf[n]-suf[j], f[i]);
    }
  }
  printf("%lld\n", f[n]);

  fcloseall();
  return 0;
}
