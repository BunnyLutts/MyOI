#define DEBUG
#include <cstdio>
#define MODS 1000000007
#define MAXN 80
#define MAXM 3000

using namespace std;

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.bf.out", "w", stdout);
#endif

  static long long f[MAXN+1][MAXM+1];
  int n, m;
  scanf("%d %d", &n, &m);

  f[1][0] = 1;
  for (int i=1; i<=n; i++) {
    long long sum=f[i-1][0];
    for (int j=1; j<=m; j++) {
      f[i][j] = (sum+f[i][j-1]*i%MODS)%MODS;
      sum = (sum+f[i-1][j])%MODS;
    }
  }
  printf("%lld", f[n][m]);

  fcloseall();
  return 0;
}
