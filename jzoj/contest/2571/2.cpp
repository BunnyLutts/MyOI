#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXN 1000
#define MAXM 1000

using namespace std;

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static int coin[MAXN+1][MAXM+1], price[MAXN+1], f[MAXM+1][MAXN+1], g[MAXM+1][MAXN+1];
  int n, p, m;
  scanf("%d %d %d", &n, &m, &p);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      scanf("%d", &coin[j][i]);
    }
  }
  for (int i=1; i<=n; i++) {
    scanf("%d", price+i);
  }
  
  int maxp=1;
  for (int i=1; i<=m; i++) {
    for (int j=1; j<=n; j++) {
      f[i][j] = -INF;
    }
  }
  for (int i=1; i<=n; i++) {
    f[0][i] = 0, g[0][i] = p;
  }
  for (int i=1; i<=m; i++) {
    for (int j=1; j<=n; j++) {
      int last=(j+n-2)%n+1;
      if (g[i-1][last]<p) {
	if (f[i][j]<f[i-1][last]+coin[i][last] || (f[i][j]==f[i-1][last] && g[i-1][last]+1<g[i][j])) {
	  f[i][j] = f[i-1][last]+coin[i][last];
	  g[i][j] = g[i-1][last]+1;
	}
      }

      if (f[i][j]<=f[i-1][maxp]+coin[i][last]-price[last]) {
	f[i][j] = f[i-1][maxp]+coin[i][last]-price[last];
	g[i][j] = 1;
      }
    }

    for (int j=1; j<=n; j++) {
      if (f[i][j]>f[i][maxp]) {
	maxp = j;
      }
    }
  }

  printf("%d\n", f[m][maxp]);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
